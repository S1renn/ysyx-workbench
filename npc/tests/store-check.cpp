#include "Vtop.h"
#include "Vtop___024root.h"
#include "Vtop__Dpi.h"
#include "verilated.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <vector>

#include "../csrc/define.h"

// Link the real csrc/mem.cpp; device accesses are outside this RAM test.
extern uint8_t pmem[MEM_SIZE];
Vtop *top_ptr = nullptr;
uint32_t *cpu_gpr = nullptr;
void difftest_skip_ref() {}
bool gpu_read(uint32_t, uint32_t *) { throw std::runtime_error("unexpected MMIO read"); }
bool gpu_write(uint32_t, uint32_t, uint8_t) { throw std::runtime_error("unexpected MMIO write"); }
extern "C" uint32_t keyboard_read() { throw std::runtime_error("unexpected keyboard read"); }
extern "C" void log_ftrace(int, int, svBit) {}

static bool stopped = false;
extern "C" void ebreak() { stopped = true; }
extern "C" void invalid_inst_trap(int, int) {
  throw std::runtime_error("invalid instruction");
}

struct Write { uint32_t addr, data; uint8_t mask; };
static std::vector<Write> writes;
extern "C" void __real_pmem_write(int, int, char);
extern "C" void __wrap_pmem_write(int addr, int data, char mask) {
  writes.push_back({uint32_t(addr), uint32_t(data), uint8_t(mask)});
  __real_pmem_write(addr, data, mask);
}

static constexpr size_t checked_size = 0x2200;
static uint32_t word(const std::array<uint8_t, checked_size> &mem, uint32_t addr) {
  size_t i = addr - MEM_BASE;
  if (i + 4 > mem.size()) throw std::runtime_error("instruction address outside test memory");
  return uint32_t(mem[i]) | (uint32_t(mem[i + 1]) << 8) |
         (uint32_t(mem[i + 2]) << 16) | (uint32_t(mem[i + 3]) << 24);
}

int main(int argc, char **argv) {
  try {
    if (argc != 2) throw std::runtime_error("usage: store-check store.bin");
    std::ifstream file(argv[1], std::ios::binary);
    if (!file) throw std::runtime_error("cannot open test image");
    std::vector<uint8_t> image{std::istreambuf_iterator<char>(file), {}};
    if (image.empty() || image.size() >= 0x1000)
      throw std::runtime_error("test image must fit below the data region");
    for (size_t i = 0x1000; i < checked_size; ++i)
      pmem[i] = uint8_t(i * 37 + 0x5b);  // Distinct surrounding bytes expose bad masks.
    std::copy(image.begin(), image.end(), pmem);
    std::array<uint8_t, checked_size> expected;
    std::copy(pmem, pmem + checked_size, expected.begin());
    std::array<uint32_t, 32> regs{};

    VerilatedContext context;
    context.commandArgs(argc, argv);
    Vtop top{&context};
    top_ptr = &top;
    auto edge = [&](int level) {
      top.clk = level;
      top.eval();
      context.timeInc(1);
    };
    top.rst = 1;
    edge(0);
    for (int i = 0; i < 3; ++i) { edge(1); edge(0); }
    top.rst = 0;
    top.eval();
    if (!writes.empty()) throw std::runtime_error("memory write during reset");

    unsigned counts[3] = {};
    unsigned retired = 0;
    for (unsigned cycle = 0; cycle < 1000 && !stopped; ++cycle) {
      uint32_t pc = top.pc;
      uint32_t inst = word(expected, pc);
      writes.clear();
      edge(1);
      bool store = false;
      Write wanted{};
      if (top.pc != pc) {
        if (top.pc != pc + 4) throw std::runtime_error("unexpected PC transition");
        ++retired;
        unsigned op = inst & 0x7f, rd = (inst >> 7) & 31;
        unsigned rs1 = (inst >> 15) & 31, rs2 = (inst >> 20) & 31;
        unsigned f3 = (inst >> 12) & 7;
        if (op == 0x37) {
          if (rd) regs[rd] = inst & 0xfffff000;
        } else if (op == 0x13 && f3 == 0) {
          if (rd) regs[rd] = regs[rs1] + (int32_t(inst) >> 20);
        } else if (op == 0x23 && f3 <= 2) {
          store = true;
          unsigned bytes = 1u << f3;
          uint32_t raw_imm = ((inst >> 25) << 5) | ((inst >> 7) & 31);
          int32_t imm = int32_t(raw_imm ^ 0x800) - 0x800;
          uint32_t addr = regs[rs1] + imm;
          if (addr % bytes) throw std::runtime_error("fixture contains a misaligned store");
          if (addr < MEM_BASE + 0x1000 || addr + bytes > MEM_BASE + 0x2000)
            throw std::runtime_error("store outside test data region");
          for (unsigned j = 0; j < bytes; ++j)
            expected[addr - MEM_BASE + j] = uint8_t(regs[rs2] >> (j * 8));
          unsigned shift = addr & 3;
          wanted = {addr & ~3u, regs[rs2] << (shift * 8),
                    uint8_t(((1u << bytes) - 1) << shift)};
          ++counts[f3];
        } else {
          throw std::runtime_error("fixture uses an unsupported instruction");
        }
      }

      // Check the DPI transaction as well as actual memory, including untouched bytes.
      if (writes.size() != (store ? 1u : 0u)) {
        std::fprintf(stderr, "PC=0x%08x: expected %u writes, got %zu\n",
                     pc, unsigned(store), writes.size());
        throw std::runtime_error("unexpected number of memory writes");
      }
      if (store) {
        const auto &actual = writes[0];
        uint32_t mask = 0;
        for (unsigned j = 0; j < 4; ++j)
          if (wanted.mask & (1 << j)) mask |= 0xffu << (j * 8);
        if (actual.addr != wanted.addr || actual.mask != wanted.mask ||
            (actual.data & mask) != (wanted.data & mask)) {
          std::fprintf(stderr, "PC=0x%08x: store transaction mismatch\n", pc);
          throw std::runtime_error("wrong address, mask, or data");
        }
      }
      for (size_t i = 0; i < checked_size; ++i) {
        if (pmem[i] != expected[i]) {
          std::fprintf(stderr, "PC=0x%08x memory[0x%08x]: expected 0x%02x, got 0x%02x\n",
                       pc, unsigned(MEM_BASE + i), expected[i], pmem[i]);
          throw std::runtime_error("memory contents mismatch");
        }
      }
      for (unsigned i = 1; i < 32; ++i) {
        if (top.rootp->top__DOT__gpr__DOT__x[i] != regs[i]) {
          std::fprintf(stderr, "PC=0x%08x: x%u unexpectedly changed\n", pc, i);
          throw std::runtime_error("register contents mismatch");
        }
      }
      edge(0);
    }
    if (!stopped) throw std::runtime_error("timeout before ebreak");
    if (!counts[0] || !counts[1] || !counts[2])
      throw std::runtime_error("fixture must exercise sb, sh, and sw");
    top.final();
    std::printf("PASS: sb=%u sh=%u sw=%u (%u retired instructions)\n",
                counts[0], counts[1], counts[2], retired);
    std::puts("Checked RAM bytes, neighboring bytes, DPI address/data/mask, write count, and registers.");
    return 0;
  } catch (const std::exception &e) {
    std::fprintf(stderr, "FAIL: %s\n", e.what());
    return 1;
  }
}
