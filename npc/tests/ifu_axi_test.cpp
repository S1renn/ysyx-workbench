#include "VIFU.h"
#include "verilated.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>

int main() {
  VerilatedContext context;
  VIFU dut{&context};
  auto check = [&](bool ok, const char* message) {
    if (!ok) { std::fprintf(stderr, "FAIL: %s\n", message); std::exit(1); }
  };
  auto tick = [&]() {
    dut.clk = 0; dut.eval();
    dut.clk = 1; dut.eval();
    dut.clk = 0; dut.eval();
  };
  dut.rst = 1;
  dut.pc = 0x80000000u;
  dut.is_load = 0;
  dut.is_store = 0;
  dut.ls_done = 0;
  dut.mem_handshake = 0;
  dut.m_axi_arready = 0;
  dut.m_axi_rvalid = 0;
  dut.m_axi_rresp = 0;
  tick();
  check(!dut.m_axi_arvalid && !dut.m_axi_rready && !dut.commit, "activity during reset");
  dut.rst = 0;
  dut.eval();

  auto fetch = [&](uint32_t instruction) {
    const uint32_t old_inst = dut.ifu_rdata;
    for (int i = 0; i < 4; ++i) {
      check(dut.m_axi_arvalid && dut.m_axi_araddr == dut.pc &&
            !dut.m_axi_rready && !dut.inst_valid && !dut.commit &&
            dut.ifu_rdata == old_inst, "incorrect AR stall behavior");
      tick();
    }
    dut.m_axi_arready = 1;
    tick();
    dut.m_axi_arready = 0;
    dut.eval();
    for (int i = 0; i < 5; ++i) {
      // Invalid RDATA may change; IFU must not latch it before RVALID.
      dut.m_axi_rdata = 0xbad00000u + i;
      dut.eval();
      check(!dut.m_axi_arvalid && dut.m_axi_rready && !dut.inst_valid &&
            !dut.commit && dut.ifu_rdata == old_inst, "instruction captured before R handshake");
      tick();
    }
    dut.m_axi_rdata = instruction;
    dut.m_axi_rvalid = 1;
    tick();
    dut.m_axi_rvalid = 0;
    dut.eval();
    check(dut.inst_valid && dut.ifu_rdata == instruction &&
          !dut.m_axi_arvalid && !dut.m_axi_rready, "instruction not captured on R handshake");
  };

  fetch(0x00100513u);
  check(dut.commit && !dut.ls_req_valid, "ALU instruction not committed");
  tick();
  dut.pc += 4;
  dut.is_load = 1;
  dut.eval();
  fetch(0x00012583u);
  for (int i = 0; i < 3; ++i) {
    check(dut.ls_req_valid && !dut.commit, "LSU request not held until accepted");
    tick();
  }
  dut.mem_handshake = 1;
  tick();
  dut.mem_handshake = 0;
  dut.eval();
  for (int i = 0; i < 8; ++i) {
    check(!dut.ls_req_valid && dut.inst_valid && !dut.commit &&
          !dut.m_axi_arvalid && !dut.m_axi_rready,
          "fetch restarted or LSU request repeated before completion");
    tick();
  }
  dut.ls_done = 1;
  dut.eval();
  check(dut.commit, "LSU response did not commit instruction");
  tick();
  dut.ls_done = 0;
  dut.pc += 4;
  dut.eval();
  check(dut.m_axi_arvalid && !dut.commit, "next fetch did not start after LSU completion");

  // Reset while waiting for a fetch response suppresses the old transaction.
  dut.m_axi_arready = 1;
  tick();
  dut.m_axi_arready = 0;
  dut.rst = 1;
  dut.m_axi_rvalid = 1;
  dut.eval();
  check(!dut.m_axi_rready && !dut.commit, "stale response accepted during reset");
  tick();
  check(dut.ifu_rdata == 0, "instruction not cleared on reset");
  dut.rst = 0;
  dut.m_axi_rvalid = 0;
  dut.eval();
  check(dut.m_axi_arvalid && !dut.inst_valid, "reset did not restart address phase");
  dut.final();
  std::puts("PASS: IFU AR stalls, delayed R, LSU acceptance/completion, reset");
}
