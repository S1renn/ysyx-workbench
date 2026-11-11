#include "Vtop.h"
#include "Vtop__Dpi.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "../csrc/define.h"

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <vector>

extern uint8_t pmem[MEM_SIZE];
Vtop* top_ptr = nullptr;
uint32_t* cpu_gpr = nullptr;
void difftest_skip_ref() {}
bool gpu_read(uint32_t, uint32_t*) { throw std::runtime_error("unexpected MMIO read"); }
bool gpu_write(uint32_t, uint32_t, uint8_t) { throw std::runtime_error("unexpected MMIO write"); }
extern "C" uint32_t keyboard_read() { throw std::runtime_error("unexpected keyboard read"); }

static bool stopped = false;
static unsigned calls = 0, returns = 0;
static unsigned fetches = 0, loads = 0, stores = 0;
static size_t image_size = 0;
static std::vector<uint32_t> fetched_pcs;
extern "C" void ebreak() { stopped = true; }
extern "C" void invalid_inst_trap(int, int) { throw std::runtime_error("invalid instruction"); }
extern "C" void log_ftrace(int, int, svBit is_ret) {
  if (is_ret) ++returns;
  else ++calls;
}
extern "C" int __real_pmem_read(int, char);
extern "C" int __wrap_pmem_read(int addr, char mask) {
  const uint32_t address = uint32_t(addr);
  if (address >= MEM_BASE && address < MEM_BASE + image_size) {
    ++fetches;
    fetched_pcs.push_back(address);
  } else {
    if (address != MEM_BASE + 0x1000 && address != MEM_BASE + 0x1004)
      throw std::runtime_error("unexpected LSU read address");
    ++loads;
  }
  if (uint8_t(mask) != 15) throw std::runtime_error("read is not a full word");
  return __real_pmem_read(addr, mask);
}
extern "C" void __real_pmem_write(int, int, char);
extern "C" void __wrap_pmem_write(int addr, int data, char mask) {
  ++stores;
  __real_pmem_write(addr, data, mask);
}

int main(int argc, char** argv) {
  try {
    if (argc != 3) throw std::runtime_error("usage: axi-check image.bin trace.vcd");
    std::ifstream file(argv[1], std::ios::binary);
    if (!file) throw std::runtime_error("cannot open image");
    std::vector<uint8_t> image{std::istreambuf_iterator<char>(file), {}};
    image_size = image.size();
    if (image.empty() || image_size >= 0x1000) throw std::runtime_error("invalid image size");
    std::copy(image.begin(), image.end(), pmem);

    VerilatedContext context;
    context.commandArgs(argc, argv);
    context.traceEverOn(true);
    Vtop top{&context};
    top_ptr = &top;
    VerilatedVcdC trace;
    top.trace(&trace, 99);
    trace.open(argv[2]);
    auto edge = [&](int level) {
      top.clk = level;
      top.eval();
      trace.dump(context.time());
      context.timeInc(1);
    };
    auto require = [](bool ok, const char* message) {
      if (!ok) throw std::runtime_error(message);
    };
    top.rst = 1;
    edge(0);
    for (int i = 0; i < 3; ++i) { edge(1); edge(0); }
    require(!fetches && !loads && !stores, "DPI access during reset");
    top.rst = 0;
    edge(0);  // Record reset release and ARVALID before the first handshake.
    unsigned retired = 0;
    for (unsigned cycle = 0; cycle < 10000 && !stopped; ++cycle) {
      const uint32_t old_pc = top.pc;
      const uint32_t old_inst = top.inst;
      const bool will_commit = top.commit;
      edge(1);
      if (will_commit) {
        require(fetched_pcs.size() == retired + 1, "fetch duplicated or instruction not fetched");
        require(fetched_pcs[retired] == old_pc, "instruction fetched from wrong PC");
        const size_t index = old_pc - MEM_BASE;
        require(index + 4 <= image.size(), "PC outside image");
        uint32_t expected_inst = 0;
        for (unsigned i = 0; i < 4; ++i) expected_inst |= uint32_t(image[index + i]) << (8 * i);
        require(old_inst == expected_inst, "IFU retired wrong instruction");
        ++retired;
      } else {
        require(top.pc == old_pc, "PC changed without commit");
        if (fetches == retired)
          require(top.inst == old_inst, "instruction changed before fetch response");
      }
      edge(0);
    }
    require(stopped, "timeout waiting for ebreak");
    require(top.x10 == 0 && top.x15 == 42, "load/store/branch/CSR self-check failed");
    require(fetches == retired + 1 && loads == 14 && stores == 6,
            "unexpected fetch/load/store count");
    require(calls == 1 && returns == 1, "ftrace repeated during a fetch wait");
    const uint8_t expected[] = {0x01, 0xa5, 0x34, 0x12, 0x00, 0xff, 0xff, 0xff};
    require(std::equal(expected, expected + sizeof(expected), pmem + 0x1000),
            "wrong final memory bytes");
    top.final();
    trace.close();
    std::printf("PASS: %u commits, %u fetches, %u loads, %u stores; branch/jal/ret/CSR\n",
                retired, fetches, loads, stores);
    std::printf("Waveform: %s\n", argv[2]);
    return 0;
  } catch (const std::exception& error) {
    std::fprintf(stderr, "FAIL: %s\n", error.what());
    return 1;
  }
}
