// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop___024root.h"

void Vtop___024root____Vdpiimwrap_top__DOT__ram__DOT__pmem_read_TOP(IData/*31:0*/ raddr, IData/*31:0*/ &rdata, CData/*7:0*/ rmask);

VL_INLINE_OPT void Vtop___024root___act_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___act_sequent__TOP__0\n"); );
    // Body
    vlSelf->top__DOT__inst_execute__DOT__alu_res = 0U;
    vlSelf->top__DOT__gpr_wdata = 0U;
    vlSelf->top__DOT__mem_wdata = 0U;
    vlSelf->top__DOT__mem_waddr = 0U;
    vlSelf->top__DOT__mem_raddr = 0U;
    vlSelf->top__DOT__wmask = 0U;
    vlSelf->top__DOT__rmask = 0U;
    vlSelf->top__DOT__mstatus_wdata = 0U;
    vlSelf->top__DOT__mcause_wdata = 0U;
    vlSelf->top__DOT__inst_execute__DOT__snpc = ((IData)(4U) 
                                                 + vlSelf->pc);
    vlSelf->top__DOT__dnpc = vlSelf->top__DOT__inst_execute__DOT__snpc;
    if ((0x73U == vlSelf->inst)) {
        vlSelf->top__DOT__mepc_wdata = vlSelf->pc;
        vlSelf->top__DOT__dnpc = vlSelf->top__DOT__gpr__DOT__mtvec;
        vlSelf->top__DOT__mcause_wdata = 0xbU;
    }
    if ((0x30200073U == vlSelf->inst)) {
        vlSelf->top__DOT__dnpc = vlSelf->top__DOT__gpr__DOT__mepc;
    }
    if ((IData)((0x1073U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        if ((0x300U == vlSelf->imm)) {
            vlSelf->top__DOT__inst_execute__DOT__tmp 
                = vlSelf->top__DOT__gpr__DOT__mstatus;
            vlSelf->top__DOT__mstatus_wdata = vlSelf->rdata1;
        } else if ((0x305U == vlSelf->imm)) {
            vlSelf->top__DOT__inst_execute__DOT__tmp 
                = vlSelf->top__DOT__gpr__DOT__mtvec;
            vlSelf->top__DOT__mtvec_wdata = vlSelf->rdata1;
        } else if ((0x341U == vlSelf->imm)) {
            vlSelf->top__DOT__inst_execute__DOT__tmp 
                = vlSelf->top__DOT__gpr__DOT__mepc;
            vlSelf->top__DOT__mepc_wdata = vlSelf->rdata1;
        } else {
            vlSelf->top__DOT__inst_execute__DOT__tmp 
                = ((0x342U == vlSelf->imm) ? vlSelf->top__DOT__gpr__DOT__mcause
                    : 0U);
            vlSelf->top__DOT__mcause_wdata = vlSelf->rdata1;
        }
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = vlSelf->top__DOT__inst_execute__DOT__tmp;
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if ((IData)((0x2073U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        if ((0x300U == vlSelf->imm)) {
            vlSelf->top__DOT__inst_execute__DOT__tmp 
                = vlSelf->top__DOT__gpr__DOT__mstatus;
            vlSelf->top__DOT__mstatus_wdata = (vlSelf->rdata1 
                                               | vlSelf->top__DOT__inst_execute__DOT__tmp);
        } else if ((0x305U == vlSelf->imm)) {
            vlSelf->top__DOT__inst_execute__DOT__tmp 
                = vlSelf->top__DOT__gpr__DOT__mtvec;
            vlSelf->top__DOT__mtvec_wdata = (vlSelf->rdata1 
                                             | vlSelf->top__DOT__inst_execute__DOT__tmp);
        } else if ((0x341U == vlSelf->imm)) {
            vlSelf->top__DOT__inst_execute__DOT__tmp 
                = vlSelf->top__DOT__gpr__DOT__mepc;
            vlSelf->top__DOT__mepc_wdata = (vlSelf->rdata1 
                                            | vlSelf->top__DOT__inst_execute__DOT__tmp);
        } else if ((0x342U == vlSelf->imm)) {
            vlSelf->top__DOT__inst_execute__DOT__tmp 
                = vlSelf->top__DOT__gpr__DOT__mcause;
            vlSelf->top__DOT__mcause_wdata = (vlSelf->rdata1 
                                              | vlSelf->top__DOT__inst_execute__DOT__tmp);
        } else {
            vlSelf->top__DOT__inst_execute__DOT__tmp = 0U;
        }
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = vlSelf->top__DOT__inst_execute__DOT__tmp;
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if ((IData)((0x13U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (vlSelf->rdata1 + vlSelf->imm);
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if ((IData)((0x4013U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (vlSelf->rdata1 ^ vlSelf->imm);
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if (((IData)((0x33U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp))) 
         & (~ (vlSelf->inst >> 0x1eU)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (vlSelf->rdata1 + vlSelf->rdata2);
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if (((IData)((0x33U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp))) 
         & (vlSelf->inst >> 0x1eU))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (vlSelf->rdata1 - vlSelf->rdata2);
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if (((IData)((0x5013U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp))) 
         & (vlSelf->inst >> 0x1eU))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = VL_SHIFTRS_III(32,32,5, vlSelf->rdata1, 
                             (0x1fU & vlSelf->imm));
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if ((IData)((0x7013U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (vlSelf->rdata1 & vlSelf->imm);
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if ((IData)((0x6013U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (vlSelf->rdata1 | vlSelf->imm);
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if ((IData)((0x1033U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (vlSelf->rdata1 << (0x1fU & vlSelf->rdata2));
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if (((IData)((0x5033U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp))) 
         & (~ (vlSelf->inst >> 0x1eU)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (vlSelf->rdata1 >> (0x1fU & vlSelf->rdata2));
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if (((IData)((0x5033U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp))) 
         & (vlSelf->inst >> 0x1eU))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = VL_SHIFTRS_III(32,32,5, vlSelf->rdata1, 
                             (0x1fU & vlSelf->rdata2));
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if (((IData)((0x5013U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp))) 
         & (~ (vlSelf->inst >> 0x1eU)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (vlSelf->rdata1 >> (0x1fU & vlSelf->imm));
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if ((IData)((0x1013U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (vlSelf->rdata1 << (0x1fU & vlSelf->imm));
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if ((IData)((0x4033U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (vlSelf->rdata1 ^ vlSelf->rdata2);
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if ((IData)((0x6033U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (vlSelf->rdata1 | vlSelf->rdata2);
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if ((IData)((0x7033U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (vlSelf->rdata1 & vlSelf->rdata2);
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if ((IData)((0x3033U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = ((vlSelf->rdata1 < vlSelf->rdata2) ? 1U
                : 0U);
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if ((IData)((0x2033U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (VL_LTS_III(32, vlSelf->rdata1, vlSelf->rdata2)
                ? 1U : 0U);
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if ((IData)((0x3013U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = ((vlSelf->rdata1 < vlSelf->imm) ? 1U : 0U);
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if ((IData)((0x2013U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (VL_LTS_III(32, vlSelf->rdata1, vlSelf->imm)
                ? 1U : 0U);
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if ((IData)((0x63U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        if ((vlSelf->rdata1 == vlSelf->rdata2)) {
            vlSelf->top__DOT__dnpc = (vlSelf->pc + vlSelf->imm);
        }
    }
    if ((IData)((0x1063U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        if ((vlSelf->rdata1 != vlSelf->rdata2)) {
            vlSelf->top__DOT__dnpc = (vlSelf->pc + vlSelf->imm);
        }
    }
    if ((IData)((0x7063U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        if ((vlSelf->rdata1 >= vlSelf->rdata2)) {
            vlSelf->top__DOT__dnpc = (vlSelf->pc + vlSelf->imm);
        }
    }
    if ((IData)((0x5063U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        if (VL_GTES_III(32, vlSelf->rdata1, vlSelf->rdata2)) {
            vlSelf->top__DOT__dnpc = (vlSelf->pc + vlSelf->imm);
        }
    }
    if ((IData)((0x4063U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        if (VL_LTS_III(32, vlSelf->rdata1, vlSelf->rdata2)) {
            vlSelf->top__DOT__dnpc = (vlSelf->pc + vlSelf->imm);
        }
    }
    if ((IData)((0x6063U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        if ((vlSelf->rdata1 < vlSelf->rdata2)) {
            vlSelf->top__DOT__dnpc = (vlSelf->pc + vlSelf->imm);
        }
    }
    if ((0x17U == (0x7fU & vlSelf->top__DOT__ram__DOT__inst_temp))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (vlSelf->pc + vlSelf->imm);
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if ((0x37U == (0x7fU & vlSelf->top__DOT__ram__DOT__inst_temp))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = vlSelf->imm;
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
    }
    if ((0x6fU == (0x7fU & vlSelf->top__DOT__ram__DOT__inst_temp))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = vlSelf->top__DOT__inst_execute__DOT__snpc;
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
        vlSelf->top__DOT__dnpc = (vlSelf->pc + vlSelf->imm);
    }
    if ((IData)((0x67U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = vlSelf->top__DOT__inst_execute__DOT__snpc;
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
        vlSelf->top__DOT__dnpc = (0xfffffffeU & (vlSelf->rdata1 
                                                 + vlSelf->imm));
    }
    if ((IData)((0x2023U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (vlSelf->rdata1 + vlSelf->imm);
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__inst_execute__DOT__alu_res;
        vlSelf->top__DOT__mem_wdata = vlSelf->rdata2;
        vlSelf->top__DOT__wmask = 0xfU;
        vlSelf->top__DOT__mem_waddr = (0xfffffffcU 
                                       & vlSelf->top__DOT__inst_execute__DOT__alu_res);
    }
    if ((IData)((0x23U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (vlSelf->rdata1 + vlSelf->imm);
        vlSelf->top__DOT__mem_waddr = (0xfffffffcU 
                                       & vlSelf->top__DOT__inst_execute__DOT__alu_res);
        if ((2U & vlSelf->top__DOT__inst_execute__DOT__alu_res)) {
            if ((1U & vlSelf->top__DOT__inst_execute__DOT__alu_res)) {
                vlSelf->top__DOT__wmask = 8U;
                vlSelf->top__DOT__mem_wdata = (vlSelf->rdata2 
                                               << 0x18U);
            } else {
                vlSelf->top__DOT__wmask = 4U;
                vlSelf->top__DOT__mem_wdata = (0xff0000U 
                                               & (vlSelf->rdata2 
                                                  << 0x10U));
            }
        } else if ((1U & vlSelf->top__DOT__inst_execute__DOT__alu_res)) {
            vlSelf->top__DOT__wmask = 2U;
            vlSelf->top__DOT__mem_wdata = (0xff00U 
                                           & (vlSelf->rdata2 
                                              << 8U));
        } else {
            vlSelf->top__DOT__wmask = 1U;
            vlSelf->top__DOT__mem_wdata = (0xffU & vlSelf->rdata2);
        }
    }
    if ((IData)((0x1023U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (vlSelf->rdata1 + vlSelf->imm);
        vlSelf->top__DOT__mem_waddr = (0xfffffffcU 
                                       & vlSelf->top__DOT__inst_execute__DOT__alu_res);
        if ((0U == (3U & vlSelf->top__DOT__inst_execute__DOT__alu_res))) {
            vlSelf->top__DOT__wmask = 3U;
            vlSelf->top__DOT__mem_wdata = (0xffffU 
                                           & vlSelf->rdata2);
        } else if ((2U == (3U & vlSelf->top__DOT__inst_execute__DOT__alu_res))) {
            vlSelf->top__DOT__wmask = 0xcU;
            vlSelf->top__DOT__mem_wdata = (vlSelf->rdata2 
                                           << 0x10U);
        } else {
            vlSelf->top__DOT__wmask = 0U;
            vlSelf->top__DOT__mem_wdata = 0U;
        }
    }
    if ((IData)((0x2003U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (vlSelf->rdata1 + vlSelf->imm);
        vlSelf->top__DOT__rmask = 0xfU;
        vlSelf->top__DOT__mem_raddr = (0xfffffffcU 
                                       & vlSelf->top__DOT__inst_execute__DOT__alu_res);
        vlSelf->top__DOT__gpr_wdata = vlSelf->top__DOT__ram__DOT__rdata_temp;
    }
    if ((IData)((3U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (vlSelf->rdata1 + vlSelf->imm);
        vlSelf->top__DOT__mem_raddr = (0xfffffffcU 
                                       & vlSelf->top__DOT__inst_execute__DOT__alu_res);
        if ((2U & vlSelf->top__DOT__inst_execute__DOT__alu_res)) {
            if ((1U & vlSelf->top__DOT__inst_execute__DOT__alu_res)) {
                vlSelf->top__DOT__rmask = 8U;
                vlSelf->top__DOT__gpr_wdata = (((- (IData)(
                                                           (vlSelf->top__DOT__ram__DOT__rdata_temp 
                                                            >> 0x1fU))) 
                                                << 8U) 
                                               | (vlSelf->top__DOT__ram__DOT__rdata_temp 
                                                  >> 0x18U));
            } else {
                vlSelf->top__DOT__rmask = 4U;
                vlSelf->top__DOT__gpr_wdata = (((- (IData)(
                                                           (1U 
                                                            & (vlSelf->top__DOT__ram__DOT__rdata_temp 
                                                               >> 0x17U)))) 
                                                << 8U) 
                                               | (0xffU 
                                                  & (vlSelf->top__DOT__ram__DOT__rdata_temp 
                                                     >> 0x10U)));
            }
        } else if ((1U & vlSelf->top__DOT__inst_execute__DOT__alu_res)) {
            vlSelf->top__DOT__rmask = 2U;
            vlSelf->top__DOT__gpr_wdata = (((- (IData)(
                                                       (1U 
                                                        & (vlSelf->top__DOT__ram__DOT__rdata_temp 
                                                           >> 0xfU)))) 
                                            << 8U) 
                                           | (0xffU 
                                              & (vlSelf->top__DOT__ram__DOT__rdata_temp 
                                                 >> 8U)));
        } else {
            vlSelf->top__DOT__rmask = 1U;
            vlSelf->top__DOT__gpr_wdata = (((- (IData)(
                                                       (1U 
                                                        & (vlSelf->top__DOT__ram__DOT__rdata_temp 
                                                           >> 7U)))) 
                                            << 8U) 
                                           | (0xffU 
                                              & vlSelf->top__DOT__ram__DOT__rdata_temp));
        }
    }
    if ((IData)((0x1003U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (vlSelf->rdata1 + vlSelf->imm);
        vlSelf->top__DOT__mem_raddr = (0xfffffffcU 
                                       & vlSelf->top__DOT__inst_execute__DOT__alu_res);
        if ((0U == (3U & vlSelf->top__DOT__inst_execute__DOT__alu_res))) {
            vlSelf->top__DOT__rmask = 3U;
            vlSelf->top__DOT__gpr_wdata = (((- (IData)(
                                                       (1U 
                                                        & (vlSelf->top__DOT__ram__DOT__rdata_temp 
                                                           >> 0xfU)))) 
                                            << 0x10U) 
                                           | (0xffffU 
                                              & vlSelf->top__DOT__ram__DOT__rdata_temp));
        } else if ((2U == (3U & vlSelf->top__DOT__inst_execute__DOT__alu_res))) {
            vlSelf->top__DOT__rmask = 0xcU;
            vlSelf->top__DOT__gpr_wdata = (((- (IData)(
                                                       (vlSelf->top__DOT__ram__DOT__rdata_temp 
                                                        >> 0x1fU))) 
                                            << 0x10U) 
                                           | (vlSelf->top__DOT__ram__DOT__rdata_temp 
                                              >> 0x10U));
        } else {
            vlSelf->top__DOT__rmask = 0U;
            vlSelf->top__DOT__gpr_wdata = 0U;
        }
    }
    if ((IData)((0x4003U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (vlSelf->rdata1 + vlSelf->imm);
        vlSelf->top__DOT__mem_raddr = (0xfffffffcU 
                                       & vlSelf->top__DOT__inst_execute__DOT__alu_res);
        if ((2U & vlSelf->top__DOT__inst_execute__DOT__alu_res)) {
            if ((1U & vlSelf->top__DOT__inst_execute__DOT__alu_res)) {
                vlSelf->top__DOT__rmask = 8U;
                vlSelf->top__DOT__gpr_wdata = (vlSelf->top__DOT__ram__DOT__rdata_temp 
                                               >> 0x18U);
            } else {
                vlSelf->top__DOT__rmask = 4U;
                vlSelf->top__DOT__gpr_wdata = (0xffU 
                                               & (vlSelf->top__DOT__ram__DOT__rdata_temp 
                                                  >> 0x10U));
            }
        } else if ((1U & vlSelf->top__DOT__inst_execute__DOT__alu_res)) {
            vlSelf->top__DOT__rmask = 2U;
            vlSelf->top__DOT__gpr_wdata = (0xffU & 
                                           (vlSelf->top__DOT__ram__DOT__rdata_temp 
                                            >> 8U));
        } else {
            vlSelf->top__DOT__rmask = 1U;
            vlSelf->top__DOT__gpr_wdata = (0xffU & vlSelf->top__DOT__ram__DOT__rdata_temp);
        }
    }
    if ((IData)((0x5003U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        vlSelf->top__DOT__inst_execute__DOT__alu_res 
            = (vlSelf->rdata1 + vlSelf->imm);
        vlSelf->top__DOT__mem_raddr = (0xfffffffcU 
                                       & vlSelf->top__DOT__inst_execute__DOT__alu_res);
        if ((0U == (3U & vlSelf->top__DOT__inst_execute__DOT__alu_res))) {
            vlSelf->top__DOT__rmask = 3U;
            vlSelf->top__DOT__gpr_wdata = (0xffffU 
                                           & vlSelf->top__DOT__ram__DOT__rdata_temp);
        } else if ((2U == (3U & vlSelf->top__DOT__inst_execute__DOT__alu_res))) {
            vlSelf->top__DOT__rmask = 0xcU;
            vlSelf->top__DOT__gpr_wdata = (vlSelf->top__DOT__ram__DOT__rdata_temp 
                                           >> 0x10U);
        } else {
            vlSelf->top__DOT__rmask = 0U;
            vlSelf->top__DOT__gpr_wdata = 0U;
        }
    }
    if (vlSelf->top__DOT__mem_ren) {
        Vtop___024root____Vdpiimwrap_top__DOT__ram__DOT__pmem_read_TOP(vlSelf->top__DOT__mem_raddr, vlSelf->__Vtask_top__DOT__ram__DOT__pmem_read__1__rdata, (IData)(vlSelf->top__DOT__rmask));
        vlSelf->top__DOT__ram__DOT__rdata_temp = vlSelf->__Vtask_top__DOT__ram__DOT__pmem_read__1__rdata;
    } else {
        vlSelf->top__DOT__ram__DOT__rdata_temp = 0U;
    }
}

void Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
    // Body
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        Vtop___024root___act_sequent__TOP__0(vlSelf);
    }
}

void Vtop___024root____Vdpiimwrap_top__DOT__ram__DOT__pmem_write_TOP(IData/*31:0*/ waddr, IData/*31:0*/ wdata, CData/*7:0*/ wmask);
void Vtop___024root____Vdpiimwrap_top__DOT__inst_execute__DOT__log_ftrace_TOP(IData/*31:0*/ pc, IData/*31:0*/ target, CData/*0:0*/ is_ret);
void Vtop___024root____Vdpiimwrap_top__DOT__inst_execute__DOT__ebreak_TOP();

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    // Init
    CData/*4:0*/ __Vdlyvdim0__top__DOT__gpr__DOT__x__v0;
    __Vdlyvdim0__top__DOT__gpr__DOT__x__v0 = 0;
    IData/*31:0*/ __Vdlyvval__top__DOT__gpr__DOT__x__v0;
    __Vdlyvval__top__DOT__gpr__DOT__x__v0 = 0;
    CData/*0:0*/ __Vdlyvset__top__DOT__gpr__DOT__x__v0;
    __Vdlyvset__top__DOT__gpr__DOT__x__v0 = 0;
    // Body
    if (vlSelf->top__DOT__mem_wen) {
        Vtop___024root____Vdpiimwrap_top__DOT__ram__DOT__pmem_write_TOP(vlSelf->top__DOT__mem_waddr, vlSelf->top__DOT__mem_wdata, (IData)(vlSelf->top__DOT__wmask));
    }
    __Vdlyvset__top__DOT__gpr__DOT__x__v0 = 0U;
    if ((IData)((((0x67U == (0x7fU & vlSelf->top__DOT__ram__DOT__inst_temp)) 
                  & (0U == (IData)(vlSelf->top__DOT__gpr_waddr))) 
                 & (0x8000U == (0xf8000U & vlSelf->inst))))) {
        Vtop___024root____Vdpiimwrap_top__DOT__inst_execute__DOT__log_ftrace_TOP(vlSelf->pc, vlSelf->top__DOT__dnpc, 1U);
    } else if ((((0x6fU == (0x7fU & vlSelf->top__DOT__ram__DOT__inst_temp)) 
                 | (0x67U == (0x7fU & vlSelf->top__DOT__ram__DOT__inst_temp))) 
                & (1U == (IData)(vlSelf->top__DOT__gpr_waddr)))) {
        Vtop___024root____Vdpiimwrap_top__DOT__inst_execute__DOT__log_ftrace_TOP(vlSelf->pc, vlSelf->top__DOT__dnpc, 0U);
    }
    if (((IData)(vlSelf->top__DOT__gpr_wen) & (0U != (IData)(vlSelf->top__DOT__gpr_waddr)))) {
        __Vdlyvval__top__DOT__gpr__DOT__x__v0 = vlSelf->top__DOT__gpr_wdata;
        __Vdlyvset__top__DOT__gpr__DOT__x__v0 = 1U;
        __Vdlyvdim0__top__DOT__gpr__DOT__x__v0 = vlSelf->top__DOT__gpr_waddr;
    }
    if (vlSelf->rst) {
        vlSelf->top__DOT__gpr__DOT__mstatus = 0x1800U;
        vlSelf->top__DOT__gpr__DOT__mtvec = 0U;
        vlSelf->top__DOT__gpr__DOT__mcause = 0U;
        vlSelf->top__DOT__gpr__DOT__mepc = 0U;
        vlSelf->pc = 0x80000000U;
    } else {
        if (vlSelf->top__DOT__wen_mstatus) {
            vlSelf->top__DOT__gpr__DOT__mstatus = vlSelf->top__DOT__mstatus_wdata;
        }
        if (vlSelf->top__DOT__wen_mtvec) {
            vlSelf->top__DOT__gpr__DOT__mtvec = vlSelf->top__DOT__mtvec_wdata;
        }
        if (vlSelf->top__DOT__wen_mcause) {
            vlSelf->top__DOT__gpr__DOT__mcause = vlSelf->top__DOT__mcause_wdata;
        }
        if (vlSelf->top__DOT__wen_mepc) {
            vlSelf->top__DOT__gpr__DOT__mepc = vlSelf->top__DOT__mepc_wdata;
        }
        vlSelf->pc = vlSelf->top__DOT__dnpc;
    }
    if (__Vdlyvset__top__DOT__gpr__DOT__x__v0) {
        vlSelf->top__DOT__gpr__DOT__x[__Vdlyvdim0__top__DOT__gpr__DOT__x__v0] 
            = __Vdlyvval__top__DOT__gpr__DOT__x__v0;
    }
    vlSelf->x10 = vlSelf->top__DOT__gpr__DOT__x[0xaU];
    vlSelf->x15 = vlSelf->top__DOT__gpr__DOT__x[0xfU];
    Vtop___024root____Vdpiimwrap_top__DOT__ram__DOT__pmem_read_TOP(vlSelf->pc, vlSelf->__Vtask_top__DOT__ram__DOT__pmem_read__0__rdata, 0xfU);
    vlSelf->top__DOT__ram__DOT__inst_temp = vlSelf->__Vtask_top__DOT__ram__DOT__pmem_read__0__rdata;
    vlSelf->top__DOT__mem_wen = 0U;
    vlSelf->top__DOT__gpr_wen = 0U;
    vlSelf->top__DOT__mem_ren = 0U;
    if ((1U & (~ (vlSelf->top__DOT__ram__DOT__inst_temp 
                  >> 6U)))) {
        if ((0x20U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
            if ((1U & (~ (vlSelf->top__DOT__ram__DOT__inst_temp 
                          >> 4U)))) {
                if ((1U & (~ (vlSelf->top__DOT__ram__DOT__inst_temp 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelf->top__DOT__ram__DOT__inst_temp 
                                  >> 2U)))) {
                        if ((2U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                            if ((1U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                                vlSelf->top__DOT__mem_wen = 1U;
                            }
                        }
                    }
                }
            }
        }
        if ((1U & (~ (vlSelf->top__DOT__ram__DOT__inst_temp 
                      >> 5U)))) {
            if ((1U & (~ (vlSelf->top__DOT__ram__DOT__inst_temp 
                          >> 4U)))) {
                if ((1U & (~ (vlSelf->top__DOT__ram__DOT__inst_temp 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelf->top__DOT__ram__DOT__inst_temp 
                                  >> 2U)))) {
                        if ((2U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                            if ((1U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                                vlSelf->top__DOT__mem_ren = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
    vlSelf->inst = vlSelf->top__DOT__ram__DOT__inst_temp;
    if ((0x40U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
        if ((0x20U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
            if ((0x10U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                if ((1U & (~ (vlSelf->top__DOT__ram__DOT__inst_temp 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelf->top__DOT__ram__DOT__inst_temp 
                                  >> 2U)))) {
                        if ((2U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                            if ((1U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                                vlSelf->top__DOT__gpr_wen 
                                    = (0U != (7U & 
                                              (vlSelf->top__DOT__ram__DOT__inst_temp 
                                               >> 0xcU)));
                            }
                        }
                    }
                }
            } else if ((8U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                if ((4U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                    if ((2U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                        if ((1U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                            vlSelf->top__DOT__gpr_wen = 1U;
                        }
                    }
                }
            } else if ((4U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                if ((2U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                    if ((1U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                        vlSelf->top__DOT__gpr_wen = 1U;
                    }
                }
            }
        }
    } else if ((0x20U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
        if ((0x10U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
            if ((1U & (~ (vlSelf->top__DOT__ram__DOT__inst_temp 
                          >> 3U)))) {
                if ((4U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                    if ((2U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                        if ((1U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                            vlSelf->top__DOT__gpr_wen = 1U;
                        }
                    }
                } else if ((2U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                    if ((1U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                        vlSelf->top__DOT__gpr_wen = 1U;
                    }
                }
            }
        }
    } else if ((0x10U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
        if ((1U & (~ (vlSelf->top__DOT__ram__DOT__inst_temp 
                      >> 3U)))) {
            if ((4U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                if ((2U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                    if ((1U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                        vlSelf->top__DOT__gpr_wen = 1U;
                    }
                }
            } else if ((2U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                if ((1U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                    vlSelf->top__DOT__gpr_wen = 1U;
                }
            }
        }
    } else if ((1U & (~ (vlSelf->top__DOT__ram__DOT__inst_temp 
                         >> 3U)))) {
        if ((1U & (~ (vlSelf->top__DOT__ram__DOT__inst_temp 
                      >> 2U)))) {
            if ((2U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                if ((1U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                    vlSelf->top__DOT__gpr_wen = 1U;
                }
            }
        }
    }
    if (((IData)((0x73U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp))) 
         & (vlSelf->inst >> 0x14U))) {
        Vtop___024root____Vdpiimwrap_top__DOT__inst_execute__DOT__ebreak_TOP();
    }
    vlSelf->top__DOT__inst_decode__DOT__inst_type = 0U;
    if ((0x40U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
        if ((0x20U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
            if ((0x10U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                if ((1U & (~ (vlSelf->top__DOT__ram__DOT__inst_temp 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelf->top__DOT__ram__DOT__inst_temp 
                                  >> 2U)))) {
                        if ((2U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                            if ((1U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                                vlSelf->top__DOT__inst_decode__DOT__inst_type = 0U;
                            }
                        }
                    }
                }
            } else if ((8U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                if ((4U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                    if ((2U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                        if ((1U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                            vlSelf->top__DOT__inst_decode__DOT__inst_type = 4U;
                        }
                    }
                }
            } else if ((4U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                if ((2U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                    if ((1U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                        vlSelf->top__DOT__inst_decode__DOT__inst_type = 0U;
                    }
                }
            } else if ((2U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                if ((1U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                    vlSelf->top__DOT__inst_decode__DOT__inst_type = 6U;
                }
            }
        }
    } else if ((0x20U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
        if ((0x10U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
            if ((1U & (~ (vlSelf->top__DOT__ram__DOT__inst_temp 
                          >> 3U)))) {
                if ((4U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                    if ((2U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                        if ((1U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                            vlSelf->top__DOT__inst_decode__DOT__inst_type = 2U;
                        }
                    }
                } else if ((2U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                    if ((1U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                        vlSelf->top__DOT__inst_decode__DOT__inst_type = 1U;
                    }
                }
            }
        } else if ((1U & (~ (vlSelf->top__DOT__ram__DOT__inst_temp 
                             >> 3U)))) {
            if ((1U & (~ (vlSelf->top__DOT__ram__DOT__inst_temp 
                          >> 2U)))) {
                if ((2U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                    if ((1U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                        vlSelf->top__DOT__inst_decode__DOT__inst_type = 5U;
                    }
                }
            }
        }
    } else if ((0x10U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
        if ((1U & (~ (vlSelf->top__DOT__ram__DOT__inst_temp 
                      >> 3U)))) {
            if ((4U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                if ((2U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                    if ((1U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                        vlSelf->top__DOT__inst_decode__DOT__inst_type = 2U;
                    }
                }
            } else if ((2U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                if ((1U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                    vlSelf->top__DOT__inst_decode__DOT__inst_type = 0U;
                }
            }
        }
    } else if ((1U & (~ (vlSelf->top__DOT__ram__DOT__inst_temp 
                         >> 3U)))) {
        if ((1U & (~ (vlSelf->top__DOT__ram__DOT__inst_temp 
                      >> 2U)))) {
            if ((2U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                if ((1U & vlSelf->top__DOT__ram__DOT__inst_temp)) {
                    vlSelf->top__DOT__inst_decode__DOT__inst_type = 0U;
                }
            }
        }
    }
    vlSelf->imm = 0U;
    vlSelf->top__DOT__raddr1 = 0U;
    vlSelf->top__DOT__raddr2 = 0U;
    vlSelf->top__DOT__gpr_waddr = 0U;
    if ((4U & (IData)(vlSelf->top__DOT__inst_decode__DOT__inst_type))) {
        if ((2U & (IData)(vlSelf->top__DOT__inst_decode__DOT__inst_type))) {
            if ((1U & (IData)(vlSelf->top__DOT__inst_decode__DOT__inst_type))) {
                vlSelf->imm = 0U;
                vlSelf->top__DOT__raddr1 = 0U;
                vlSelf->top__DOT__gpr_waddr = 0U;
            } else {
                vlSelf->imm = (((- (IData)((vlSelf->inst 
                                            >> 0x1fU))) 
                                << 0xcU) | ((0x800U 
                                             & (vlSelf->inst 
                                                << 4U)) 
                                            | ((0x7e0U 
                                                & (vlSelf->inst 
                                                   >> 0x14U)) 
                                               | (0x1eU 
                                                  & (vlSelf->inst 
                                                     >> 7U)))));
                vlSelf->top__DOT__raddr1 = (0x1fU & 
                                            (vlSelf->inst 
                                             >> 0xfU));
                vlSelf->top__DOT__raddr2 = (0x1fU & 
                                            (vlSelf->inst 
                                             >> 0x14U));
            }
        } else if ((1U & (IData)(vlSelf->top__DOT__inst_decode__DOT__inst_type))) {
            vlSelf->imm = (((- (IData)((vlSelf->inst 
                                        >> 0x1fU))) 
                            << 0xcU) | ((0xfe0U & (vlSelf->inst 
                                                   >> 0x14U)) 
                                        | (0x1fU & 
                                           (vlSelf->inst 
                                            >> 7U))));
            vlSelf->top__DOT__raddr1 = (0x1fU & (vlSelf->inst 
                                                 >> 0xfU));
            vlSelf->top__DOT__raddr2 = (0x1fU & (vlSelf->inst 
                                                 >> 0x14U));
        } else {
            vlSelf->imm = (((- (IData)((vlSelf->inst 
                                        >> 0x1fU))) 
                            << 0x14U) | ((0xff000U 
                                          & vlSelf->inst) 
                                         | ((0x800U 
                                             & (vlSelf->inst 
                                                >> 9U)) 
                                            | (0x7feU 
                                               & (vlSelf->inst 
                                                  >> 0x14U)))));
            vlSelf->top__DOT__gpr_waddr = (0x1fU & 
                                           (vlSelf->inst 
                                            >> 7U));
        }
    } else if ((2U & (IData)(vlSelf->top__DOT__inst_decode__DOT__inst_type))) {
        if ((1U & (IData)(vlSelf->top__DOT__inst_decode__DOT__inst_type))) {
            vlSelf->imm = 0U;
            vlSelf->top__DOT__raddr1 = 0U;
            vlSelf->top__DOT__gpr_waddr = 0U;
        } else {
            vlSelf->imm = (0xfffff000U & vlSelf->inst);
            vlSelf->top__DOT__gpr_waddr = (0x1fU & 
                                           (vlSelf->inst 
                                            >> 7U));
        }
    } else if ((1U & (IData)(vlSelf->top__DOT__inst_decode__DOT__inst_type))) {
        vlSelf->top__DOT__raddr1 = (0x1fU & (vlSelf->inst 
                                             >> 0xfU));
        vlSelf->top__DOT__raddr2 = (0x1fU & (vlSelf->inst 
                                             >> 0x14U));
        vlSelf->top__DOT__gpr_waddr = (0x1fU & (vlSelf->inst 
                                                >> 7U));
    } else {
        vlSelf->imm = (((- (IData)((vlSelf->inst >> 0x1fU))) 
                        << 0xcU) | (vlSelf->inst >> 0x14U));
        vlSelf->top__DOT__raddr1 = (0x1fU & (vlSelf->inst 
                                             >> 0xfU));
        vlSelf->top__DOT__gpr_waddr = (0x1fU & (vlSelf->inst 
                                                >> 7U));
    }
    vlSelf->rdata1 = ((0U == (IData)(vlSelf->top__DOT__raddr1))
                       ? 0U : vlSelf->top__DOT__gpr__DOT__x
                      [vlSelf->top__DOT__raddr1]);
    vlSelf->rdata2 = ((0U == (IData)(vlSelf->top__DOT__raddr2))
                       ? 0U : vlSelf->top__DOT__gpr__DOT__x
                      [vlSelf->top__DOT__raddr2]);
    vlSelf->top__DOT__wen_mtvec = 0U;
    vlSelf->top__DOT__wen_mstatus = 0U;
    vlSelf->top__DOT__wen_mcause = 0U;
    if ((0x73U == vlSelf->inst)) {
        vlSelf->top__DOT__wen_mcause = 1U;
    }
    if ((IData)((0x1073U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        if ((0x300U != vlSelf->imm)) {
            if ((0x305U == vlSelf->imm)) {
                vlSelf->top__DOT__wen_mtvec = 1U;
            }
            if ((0x305U != vlSelf->imm)) {
                if ((0x341U != vlSelf->imm)) {
                    if ((0x342U == vlSelf->imm)) {
                        vlSelf->top__DOT__wen_mcause = 1U;
                    }
                }
            }
        }
        if ((0x300U == vlSelf->imm)) {
            vlSelf->top__DOT__wen_mstatus = 1U;
        }
    }
    vlSelf->top__DOT__wen_mepc = 0U;
    if ((0x73U == vlSelf->inst)) {
        vlSelf->top__DOT__wen_mepc = 1U;
    }
    if ((IData)((0x1073U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        if ((0x300U != vlSelf->imm)) {
            if ((0x305U != vlSelf->imm)) {
                if ((0x341U == vlSelf->imm)) {
                    vlSelf->top__DOT__wen_mepc = 1U;
                }
            }
        }
    }
    if ((IData)((0x2073U == (0x707fU & vlSelf->top__DOT__ram__DOT__inst_temp)))) {
        if ((0x300U != vlSelf->imm)) {
            if ((0x305U == vlSelf->imm)) {
                vlSelf->top__DOT__wen_mtvec = 1U;
            }
            if ((0x305U != vlSelf->imm)) {
                if ((0x341U != vlSelf->imm)) {
                    if ((0x342U == vlSelf->imm)) {
                        vlSelf->top__DOT__wen_mcause = 1U;
                    }
                }
                if ((0x341U == vlSelf->imm)) {
                    vlSelf->top__DOT__wen_mepc = 1U;
                }
            }
        }
        if ((0x300U == vlSelf->imm)) {
            vlSelf->top__DOT__wen_mstatus = 1U;
        }
    }
}

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    // Body
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((3ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vtop___024root___act_sequent__TOP__0(vlSelf);
    }
}

void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf);

bool Vtop___024root___eval_phase__act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<2> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vtop___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vtop___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtop___024root___eval_phase__nba(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vtop___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("vsrc/top.v", 1, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("vsrc/top.v", 1, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vtop___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vtop___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
}
#endif  // VL_DEBUG
