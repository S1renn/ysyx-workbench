// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop___024root.h"

VL_ATTR_COLD void Vtop___024root___eval_static(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    // Body
    Vtop___024root___eval_initial__TOP(vlSelf);
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__ram__DOT__rdata_temp__0 
        = vlSelf->top__DOT__ram__DOT__rdata_temp;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__ram__DOT__rdata_temp__1 
        = vlSelf->top__DOT__ram__DOT__rdata_temp;
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
}

void Vtop___024root____Vdpiimwrap_top__DOT__gpr__DOT__set_gpr_ptr__Vdpioc2_TOP(const IData/*31:0*/ &a);

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial__TOP\n"); );
    // Body
    Vtop___024root____Vdpiimwrap_top__DOT__gpr__DOT__set_gpr_ptr__Vdpioc2_TOP(
                                                                              vlSelf->top__DOT__gpr__DOT__x
                                                                              [0U]);
}

VL_ATTR_COLD void Vtop___024root___eval_final(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_final\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_settle(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_settle\n"); );
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelf->__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("vsrc/top.v", 1, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vtop___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelf->__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
    if ((2ULL & vlSelf->__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 1 is active: @([hybrid] top.ram.rdata_temp)\n");
    }
}
#endif  // VL_DEBUG

void Vtop___024root____Vdpiimwrap_top__DOT__ram__DOT__pmem_read_TOP(IData/*31:0*/ raddr, IData/*31:0*/ &rdata, CData/*7:0*/ rmask);
void Vtop___024root____Vdpiimwrap_top__DOT__inst_execute__DOT__ebreak_TOP();

VL_ATTR_COLD void Vtop___024root___stl_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___stl_sequent__TOP__0\n"); );
    // Body
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

void Vtop___024root___act_sequent__TOP__0(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_stl\n"); );
    // Body
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        Vtop___024root___stl_sequent__TOP__0(vlSelf);
    }
    if ((3ULL & vlSelf->__VstlTriggered.word(0U))) {
        Vtop___024root___act_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void Vtop___024root___eval_triggers__stl(Vtop___024root* vlSelf);

VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__stl\n"); );
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtop___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelf->__VstlTriggered.any();
    if (__VstlExecute) {
        Vtop___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @([hybrid] top.ram.rdata_temp)\n");
    }
    if ((2ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @([hybrid] top.ram.rdata_temp)\n");
    }
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = 0;
    vlSelf->rst = 0;
    vlSelf->pc = 0;
    vlSelf->inst = 0;
    vlSelf->x10 = 0;
    vlSelf->x15 = 0;
    vlSelf->rdata1 = 0;
    vlSelf->rdata2 = 0;
    vlSelf->imm = 0;
    vlSelf->top__DOT__dnpc = 0;
    vlSelf->top__DOT__mem_wdata = 0;
    vlSelf->top__DOT__wmask = 0;
    vlSelf->top__DOT__rmask = 0;
    vlSelf->top__DOT__mem_waddr = 0;
    vlSelf->top__DOT__mem_raddr = 0;
    vlSelf->top__DOT__gpr_wen = 0;
    vlSelf->top__DOT__mem_wen = 0;
    vlSelf->top__DOT__mem_ren = 0;
    vlSelf->top__DOT__raddr1 = 0;
    vlSelf->top__DOT__raddr2 = 0;
    vlSelf->top__DOT__gpr_waddr = 0;
    vlSelf->top__DOT__gpr_wdata = 0;
    vlSelf->top__DOT__wen_mtvec = 0;
    vlSelf->top__DOT__wen_mepc = 0;
    vlSelf->top__DOT__wen_mcause = 0;
    vlSelf->top__DOT__wen_mstatus = 0;
    vlSelf->top__DOT__mepc_wdata = 0;
    vlSelf->top__DOT__mtvec_wdata = 0;
    vlSelf->top__DOT__mstatus_wdata = 0;
    vlSelf->top__DOT__mcause_wdata = 0;
    vlSelf->top__DOT__ram__DOT__inst_temp = 0;
    vlSelf->top__DOT__ram__DOT__rdata_temp = 0;
    vlSelf->top__DOT__inst_decode__DOT__inst_type = 0;
    vlSelf->top__DOT__inst_execute__DOT__snpc = 0;
    vlSelf->top__DOT__inst_execute__DOT__alu_res = 0;
    vlSelf->top__DOT__inst_execute__DOT__tmp = 0;
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->top__DOT__gpr__DOT__x[__Vi0] = 0;
    }
    vlSelf->top__DOT__gpr__DOT__mepc = 0;
    vlSelf->top__DOT__gpr__DOT__mtvec = 0;
    vlSelf->top__DOT__gpr__DOT__mcause = 0;
    vlSelf->top__DOT__gpr__DOT__mstatus = 0;
    vlSelf->__Vtask_top__DOT__ram__DOT__pmem_read__0__rdata = 0;
    vlSelf->__Vtask_top__DOT__ram__DOT__pmem_read__1__rdata = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__ram__DOT__rdata_temp__0 = 0;
    vlSelf->__VstlDidInit = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__ram__DOT__rdata_temp__1 = 0;
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    vlSelf->__VactDidInit = 0;
}
