// Build from npc/:
// verilator --cc --exe --build --trace -Wall --top-module LSU_axi \
//   --Mdir /tmp/npc-lsu-axi-test vsrc/LSU_axi.v "$PWD/tests/lsu_axi_test.cpp"
// /tmp/npc-lsu-axi-test/VLSU_axi
#include "VLSU_axi.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <cstdint>
#include <cstdlib>
#include <iostream>

class Test {
 public:
  VerilatedContext context;
  VLSU_axi dut{&context};
  VerilatedVcdC trace;
  unsigned requests = 0, reads = 0, addresses = 0, writes = 0, completions = 0;
  bool sampled_done = false;
  uint32_t sampled_data = 0;
  unsigned sampled_resp = 0;

  Test() {
    context.traceEverOn(true);
    dut.trace(&trace, 99);
    trace.open("/tmp/npc-lsu-axi-test.vcd");
    reset();
  }
  ~Test() { dut.final(); trace.close(); }

  void check(bool condition, const char* message) {
    if (!condition) {
      std::cerr << "FAIL at time " << context.time() << ": " << message << '\n';
      std::exit(1);
    }
  }
  void eval() { dut.eval(); }
  void dump() { trace.dump(context.time()); context.timeInc(1); }
  void tick() {
    dut.clk = 0;
    eval();
    dump();
    sampled_done = dut.done;
    sampled_data = dut.load_data;
    sampled_resp = dut.resp;
    requests += dut.req_valid && dut.req_ready;
    reads += dut.o_m_lsu_axi_arvalid && dut.i_m_lsu_axi_arready;
    addresses += dut.o_m_lsu_axi_awvalid && dut.i_m_lsu_axi_awready;
    writes += dut.o_m_lsu_axi_wvalid && dut.i_m_lsu_axi_wready;
    completions += dut.done;
    dut.clk = 1;
    eval();
    dump();
    dut.clk = 0;
    eval();
    dump();
  }
  void quiet() {
    eval();
    check(!dut.o_m_lsu_axi_arvalid && !dut.o_m_lsu_axi_awvalid &&
          !dut.o_m_lsu_axi_wvalid && !dut.o_m_lsu_axi_rready &&
          !dut.o_m_lsu_axi_bready && !dut.done, "unexpected AXI activity");
  }
  void reset() {
    dut.req_valid = 0;
    dut.i_m_lsu_axi_arready = 0;
    dut.i_m_lsu_axi_rvalid = 0;
    dut.i_m_lsu_axi_rdata = 0;
    dut.i_m_lsu_axi_rresp = 0;
    dut.i_m_lsu_axi_awready = 0;
    dut.i_m_lsu_axi_wready = 0;
    dut.i_m_lsu_axi_bvalid = 0;
    dut.i_m_lsu_axi_bresp = 0;
    dut.rst = 1;
    quiet();
    check(!dut.req_ready, "request accepted during reset");
    tick();
    dut.rst = 0;
    eval();
    quiet();
    check(dut.req_ready, "not ready after reset");
  }
  void start(bool load, unsigned func, unsigned offset, uint32_t data = 0) {
    eval();
    check(dut.req_ready, "not ready for next request");
    dut.inst_type = load;
    dut.func3 = func;
    dut.addr = 0x80000100u + offset;
    dut.store_data = data;
    dut.req_valid = 1;
    tick();
    dut.req_valid = 0;
    // Change all CPU payload inputs: the accepted request must remain intact.
    dut.inst_type = !load;
    dut.func3 = 7;
    dut.addr = 0xdeadbeefu;
    dut.store_data = 0x13579bdfu;
    eval();
    check(!dut.req_ready && !dut.done, "request completed or reopened too early");
  }
  void finish_read(uint32_t data, uint32_t expected, unsigned response) {
    for (int i = 0; i < 3; ++i) {
      eval();
      check(dut.o_m_lsu_axi_rready && !dut.o_m_lsu_axi_arvalid && !dut.done,
            "read response wait is incorrect");
      tick();
    }
    dut.i_m_lsu_axi_rvalid = 1;
    dut.i_m_lsu_axi_rdata = data;
    dut.i_m_lsu_axi_rresp = response;
    eval();
    check(dut.done && dut.load_data == expected && dut.resp == response,
          "read result/response not valid on completion edge");
    tick();
    check(sampled_done && sampled_data == expected && sampled_resp == response,
          "CPU sampled wrong read result");
    dut.i_m_lsu_axi_rvalid = 0;
    quiet();
    check(dut.req_ready, "read did not release LSU");
  }
  void load(unsigned func, unsigned offset, unsigned response = 0) {
    const unsigned old_req = requests, old_ar = reads, old_done = completions;
    start(true, func, offset);
    // A second offered request must not overwrite an outstanding request.
    dut.req_valid = 1;
    for (int i = 0; i < 4; ++i) {
      eval();
      check(dut.o_m_lsu_axi_arvalid && dut.o_m_lsu_axi_araddr == 0x80000100u &&
            !dut.req_ready && !dut.done, "AR changed while stalled");
      tick();
    }
    dut.req_valid = 0;
    dut.i_m_lsu_axi_arready = 1;
    tick();
    dut.i_m_lsu_axi_arready = 0;
    const uint32_t data = 0x80ff7f01u;
    const unsigned bytes = 1u << (func & 3);
    const uint32_t mask = bytes == 4 ? 0xffffffffu : (1u << (bytes * 8)) - 1;
    uint32_t expected = (data >> (offset * 8)) & mask;
    if (func < 4 && bytes < 4 && (expected & (1u << (bytes * 8 - 1))))
      expected |= ~mask;
    finish_read(data, expected, response);
    check(requests == old_req + 1 && reads == old_ar + 1 && completions == old_done + 1,
          "read request duplicated or lost");
  }
  void store(unsigned func, unsigned offset, unsigned order, unsigned response = 0) {
    const unsigned old_req = requests, old_aw = addresses, old_w = writes;
    const unsigned old_done = completions;
    const uint32_t data = 0x89abcdefu;
    const unsigned bytes = 1u << func;
    const unsigned mask = ((1u << bytes) - 1) << offset;
    const uint32_t value_mask = bytes == 4 ? 0xffffffffu : (1u << (bytes * 8)) - 1;
    const uint32_t expected = (data & value_mask) << (offset * 8);
    start(false, func, offset, data);
    for (int i = 0; i < 3; ++i) {
      eval();
      check(dut.o_m_lsu_axi_awvalid && dut.o_m_lsu_axi_wvalid &&
            dut.o_m_lsu_axi_awaddr == 0x80000100u &&
            dut.o_m_lsu_axi_wdata == expected && dut.o_m_lsu_axi_wstrb == mask &&
            !dut.done, "write payload changed while stalled");
      tick();
    }
    // order: 0 = AW first, 1 = W first, 2 = simultaneous.
    dut.i_m_lsu_axi_awready = order != 1;
    dut.i_m_lsu_axi_wready = order != 0;
    tick();
    if (order != 2) {
      for (int i = 0; i < 3; ++i) {
        check(dut.o_m_lsu_axi_awvalid == (order == 1) &&
              dut.o_m_lsu_axi_wvalid == (order == 0) &&
              !dut.o_m_lsu_axi_bready && !dut.done &&
              dut.o_m_lsu_axi_awaddr == 0x80000100u &&
              dut.o_m_lsu_axi_wdata == expected && dut.o_m_lsu_axi_wstrb == mask,
              "completed write channel repeated or remaining payload lost");
        tick();
      }
      dut.i_m_lsu_axi_awready = 1;
      dut.i_m_lsu_axi_wready = 1;
      tick();
    }
    dut.i_m_lsu_axi_awready = 0;
    dut.i_m_lsu_axi_wready = 0;
    for (int i = 0; i < 3; ++i) {
      eval();
      check(dut.o_m_lsu_axi_bready && !dut.done &&
            !dut.o_m_lsu_axi_awvalid && !dut.o_m_lsu_axi_wvalid,
            "store completed before B response");
      tick();
    }
    dut.i_m_lsu_axi_bvalid = 1;
    dut.i_m_lsu_axi_bresp = response;
    eval();
    check(dut.done && dut.resp == response, "write response not forwarded");
    tick();
    check(sampled_done && sampled_resp == response, "CPU missed write completion");
    dut.i_m_lsu_axi_bvalid = 0;
    quiet();
    check(dut.req_ready && requests == old_req + 1 && addresses == old_aw + 1 &&
          writes == old_w + 1 && completions == old_done + 1,
          "write request duplicated or lost");
  }
};

int main() {
  Test t;
  for (int i = 0; i < 8; ++i) {
    t.dut.inst_type = i & 1;
    t.quiet();
    t.tick();
  }
  for (unsigned func : {0u, 1u, 2u, 4u, 5u}) {
    unsigned bytes = 1u << (func & 3);
    for (unsigned offset = 0; offset < 4; offset += bytes) t.load(func, offset);
  }
  for (unsigned func = 0; func < 3; ++func)
    for (unsigned offset = 0; offset < 4; offset += 1u << func)
      for (unsigned order = 0; order < 3; ++order) t.store(func, offset, order);
  t.load(2, 0, 2);
  t.load(2, 0, 3);
  t.store(2, 0, 0, 2);
  t.store(2, 0, 1, 3);

  // Reset aborts a transaction at each externally meaningful phase.
  t.start(true, 2, 0);  // stalled AR
  t.reset();
  t.start(true, 2, 0);
  t.dut.i_m_lsu_axi_arready = 1;
  t.tick();  // waiting R
  t.reset();
  for (unsigned order = 0; order < 4; ++order) {
    t.start(false, 2, 0);
    t.dut.i_m_lsu_axi_awready = (order & 1) != 0;
    t.dut.i_m_lsu_axi_wready = (order & 2) != 0;
    t.tick();  // neither / only AW / only W / both sent
    t.reset();
  }
  t.load(2, 0);
  t.store(2, 0, 2);
  std::cout << "PASS: loads/stores, stalls, independent AW/W, response codes, reset\n"
            << "Waveform: /tmp/npc-lsu-axi-test.vcd\n";
}
