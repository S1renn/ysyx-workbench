// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Prototypes for DPI import and export functions.
//
// Verilator includes this file in all generated .cpp files that use DPI functions.
// Manually include this file where DPI .c import functions are declared to ensure
// the C functions match the expectations of the DPI imports.

#ifndef VERILATED_VTOP__DPI_H_
#define VERILATED_VTOP__DPI_H_  // guard

#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif


    // DPI IMPORTS
    // DPI import at vsrc/EXU.v:49:32
    extern void ebreak();
    // DPI import at vsrc/EXU.v:50:32
    extern void invalid_inst_trap(int pc, int inst);
    // DPI import at vsrc/EXU.v:55:32
    extern void log_ftrace(int pc, int target, svBit is_ret);
    // DPI import at vsrc/MEM.v:29:32
    extern void pmem_read(int raddr, int* rdata, char rmask);
    // DPI import at vsrc/MEM.v:36:32
    extern void pmem_write(int waddr, int wdata, char wmask);
    // DPI import at vsrc/gpr.v:32:32
    extern void set_gpr_ptr(const svOpenArrayHandle a);

#ifdef __cplusplus
}
#endif

#endif  // guard
