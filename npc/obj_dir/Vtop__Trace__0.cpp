// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vtop___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vtop___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY((vlSelf->__Vm_traceActivity[1U] 
                     | vlSelf->__Vm_traceActivity[3U]))) {
        bufp->chgIData(oldp+0,(vlSelf->top__DOT__dnpc),32);
        bufp->chgIData(oldp+1,(vlSelf->top__DOT__mem_wdata),32);
        bufp->chgCData(oldp+2,(vlSelf->top__DOT__wmask),4);
        bufp->chgCData(oldp+3,(vlSelf->top__DOT__rmask),4);
        bufp->chgIData(oldp+4,(vlSelf->top__DOT__ram__DOT__rdata_temp),32);
        bufp->chgIData(oldp+5,(vlSelf->top__DOT__mem_waddr),32);
        bufp->chgIData(oldp+6,(vlSelf->top__DOT__mem_raddr),32);
        bufp->chgIData(oldp+7,(vlSelf->top__DOT__gpr_wdata),32);
        bufp->chgIData(oldp+8,(vlSelf->top__DOT__mepc_wdata),32);
        bufp->chgIData(oldp+9,(vlSelf->top__DOT__mtvec_wdata),32);
        bufp->chgIData(oldp+10,(vlSelf->top__DOT__mstatus_wdata),32);
        bufp->chgIData(oldp+11,(vlSelf->top__DOT__mcause_wdata),32);
        bufp->chgIData(oldp+12,(vlSelf->top__DOT__inst_execute__DOT__snpc),32);
        bufp->chgIData(oldp+13,(vlSelf->top__DOT__inst_execute__DOT__alu_res),32);
        bufp->chgIData(oldp+14,(vlSelf->top__DOT__inst_execute__DOT__tmp),32);
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[2U])) {
        bufp->chgBit(oldp+15,(vlSelf->top__DOT__gpr_wen));
        bufp->chgBit(oldp+16,(vlSelf->top__DOT__gpr_ren));
        bufp->chgBit(oldp+17,(vlSelf->top__DOT__mem_wen));
        bufp->chgBit(oldp+18,(vlSelf->top__DOT__mem_ren));
        bufp->chgCData(oldp+19,(vlSelf->top__DOT__raddr1),5);
        bufp->chgCData(oldp+20,(vlSelf->top__DOT__raddr2),5);
        bufp->chgBit(oldp+21,(vlSelf->top__DOT__inst_valid));
        bufp->chgCData(oldp+22,((0x7fU & vlSelf->top__DOT__ram__DOT__inst_temp)),7);
        bufp->chgCData(oldp+23,((7U & (vlSelf->top__DOT__ram__DOT__inst_temp 
                                       >> 0xcU))),3);
        bufp->chgCData(oldp+24,(vlSelf->top__DOT__gpr_waddr),5);
        bufp->chgBit(oldp+25,(vlSelf->top__DOT__wen_mtvec));
        bufp->chgBit(oldp+26,(vlSelf->top__DOT__wen_mepc));
        bufp->chgBit(oldp+27,(vlSelf->top__DOT__wen_mcause));
        bufp->chgBit(oldp+28,(vlSelf->top__DOT__wen_mstatus));
        bufp->chgIData(oldp+29,(vlSelf->top__DOT__gpr__DOT__mtvec),32);
        bufp->chgIData(oldp+30,(vlSelf->top__DOT__gpr__DOT__mstatus),32);
        bufp->chgIData(oldp+31,(vlSelf->top__DOT__gpr__DOT__mcause),32);
        bufp->chgIData(oldp+32,(vlSelf->top__DOT__gpr__DOT__mepc),32);
        bufp->chgIData(oldp+33,(vlSelf->top__DOT__gpr__DOT__x[0]),32);
        bufp->chgIData(oldp+34,(vlSelf->top__DOT__gpr__DOT__x[1]),32);
        bufp->chgIData(oldp+35,(vlSelf->top__DOT__gpr__DOT__x[2]),32);
        bufp->chgIData(oldp+36,(vlSelf->top__DOT__gpr__DOT__x[3]),32);
        bufp->chgIData(oldp+37,(vlSelf->top__DOT__gpr__DOT__x[4]),32);
        bufp->chgIData(oldp+38,(vlSelf->top__DOT__gpr__DOT__x[5]),32);
        bufp->chgIData(oldp+39,(vlSelf->top__DOT__gpr__DOT__x[6]),32);
        bufp->chgIData(oldp+40,(vlSelf->top__DOT__gpr__DOT__x[7]),32);
        bufp->chgIData(oldp+41,(vlSelf->top__DOT__gpr__DOT__x[8]),32);
        bufp->chgIData(oldp+42,(vlSelf->top__DOT__gpr__DOT__x[9]),32);
        bufp->chgIData(oldp+43,(vlSelf->top__DOT__gpr__DOT__x[10]),32);
        bufp->chgIData(oldp+44,(vlSelf->top__DOT__gpr__DOT__x[11]),32);
        bufp->chgIData(oldp+45,(vlSelf->top__DOT__gpr__DOT__x[12]),32);
        bufp->chgIData(oldp+46,(vlSelf->top__DOT__gpr__DOT__x[13]),32);
        bufp->chgIData(oldp+47,(vlSelf->top__DOT__gpr__DOT__x[14]),32);
        bufp->chgIData(oldp+48,(vlSelf->top__DOT__gpr__DOT__x[15]),32);
        bufp->chgIData(oldp+49,(vlSelf->top__DOT__gpr__DOT__x[16]),32);
        bufp->chgIData(oldp+50,(vlSelf->top__DOT__gpr__DOT__x[17]),32);
        bufp->chgIData(oldp+51,(vlSelf->top__DOT__gpr__DOT__x[18]),32);
        bufp->chgIData(oldp+52,(vlSelf->top__DOT__gpr__DOT__x[19]),32);
        bufp->chgIData(oldp+53,(vlSelf->top__DOT__gpr__DOT__x[20]),32);
        bufp->chgIData(oldp+54,(vlSelf->top__DOT__gpr__DOT__x[21]),32);
        bufp->chgIData(oldp+55,(vlSelf->top__DOT__gpr__DOT__x[22]),32);
        bufp->chgIData(oldp+56,(vlSelf->top__DOT__gpr__DOT__x[23]),32);
        bufp->chgIData(oldp+57,(vlSelf->top__DOT__gpr__DOT__x[24]),32);
        bufp->chgIData(oldp+58,(vlSelf->top__DOT__gpr__DOT__x[25]),32);
        bufp->chgIData(oldp+59,(vlSelf->top__DOT__gpr__DOT__x[26]),32);
        bufp->chgIData(oldp+60,(vlSelf->top__DOT__gpr__DOT__x[27]),32);
        bufp->chgIData(oldp+61,(vlSelf->top__DOT__gpr__DOT__x[28]),32);
        bufp->chgIData(oldp+62,(vlSelf->top__DOT__gpr__DOT__x[29]),32);
        bufp->chgIData(oldp+63,(vlSelf->top__DOT__gpr__DOT__x[30]),32);
        bufp->chgIData(oldp+64,(vlSelf->top__DOT__gpr__DOT__x[31]),32);
        bufp->chgCData(oldp+65,(vlSelf->top__DOT__inst_decode__DOT__inst_type),3);
        bufp->chgIData(oldp+66,(vlSelf->top__DOT__ram__DOT__inst_temp),32);
    }
    bufp->chgBit(oldp+67,(vlSelf->clk));
    bufp->chgBit(oldp+68,(vlSelf->rst));
    bufp->chgIData(oldp+69,(vlSelf->pc),32);
    bufp->chgIData(oldp+70,(vlSelf->inst),32);
    bufp->chgIData(oldp+71,(vlSelf->x10),32);
    bufp->chgIData(oldp+72,(vlSelf->x15),32);
    bufp->chgIData(oldp+73,(vlSelf->rdata1),32);
    bufp->chgIData(oldp+74,(vlSelf->rdata2),32);
    bufp->chgIData(oldp+75,(vlSelf->imm),32);
    bufp->chgBit(oldp+76,(((IData)(vlSelf->rst) | (IData)(vlSelf->top__DOT__inst_valid))));
}

void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_cleanup\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[3U] = 0U;
}
