// Verilated -*- SystemC -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _Vi2c_master_top_H_
#define _Vi2c_master_top_H_

#include "systemc.h"
#include "verilated_sc.h"
#include "verilated.h"
class Vi2c_master_top__Syms;

//----------

SC_MODULE(Vi2c_master_top) {
  public:
    // CELLS
    // Public to allow access to /*verilator_public*/ items;
    // otherwise the application code can consider these internals.
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    sc_in<bool>	wb_clk_i;
    sc_in<bool>	wb_rst_i;
    sc_in<bool>	arst_i;
    sc_in<uint32_t>	wb_adr_i;
    sc_in<uint32_t>	wb_dat_i;
    sc_out<uint32_t>	wb_dat_o;
    sc_in<bool>	wb_we_i;
    sc_in<bool>	wb_stb_i;
    sc_in<bool>	wb_cyc_i;
    sc_out<bool>	wb_ack_o;
    sc_out<bool>	wb_inta_o;
    sc_in<bool>	scl_pad_i;
    sc_out<bool>	scl_pad_o;
    sc_out<bool>	scl_padoen_o;
    sc_in<bool>	sda_pad_i;
    sc_out<bool>	sda_pad_o;
    sc_out<bool>	sda_padoen_o;
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    VL_SIG8(v__DOT__ctr,7,0);
    VL_SIG8(v__DOT__txr,7,0);
    VL_SIG8(v__DOT__cr,7,0);
    VL_SIG8(v__DOT__sr,7,0);
    VL_SIG8(v__DOT__done,0,0);
    VL_SIG8(v__DOT__irxack,0,0);
    VL_SIG8(v__DOT__rxack,0,0);
    VL_SIG8(v__DOT__tip,0,0);
    VL_SIG8(v__DOT__irq_flag,0,0);
    VL_SIG8(v__DOT__i2c_busy,0,0);
    VL_SIG8(v__DOT__i2c_al,0,0);
    VL_SIG8(v__DOT__al,0,0);
    VL_SIG8(v__DOT__wb_wacc,0,0);
    VL_SIG8(v__DOT__byte_controller__DOT__core_cmd,3,0);
    VL_SIG8(v__DOT__byte_controller__DOT__core_txd,0,0);
    VL_SIG8(v__DOT__byte_controller__DOT__core_ack,0,0);
    VL_SIG8(v__DOT__byte_controller__DOT__core_rxd,0,0);
    VL_SIG8(v__DOT__byte_controller__DOT__sr,7,0);
    VL_SIG8(v__DOT__byte_controller__DOT__shift,0,0);
    VL_SIG8(v__DOT__byte_controller__DOT__ld,0,0);
    VL_SIG8(v__DOT__byte_controller__DOT__dcnt,2,0);
    VL_SIG8(v__DOT__byte_controller__DOT__c_state,4,0);
    VL_SIG8(v__DOT__byte_controller__DOT__bit_controller__DOT__cSCL,1,0);
    VL_SIG8(v__DOT__byte_controller__DOT__bit_controller__DOT__cSDA,1,0);
    VL_SIG8(v__DOT__byte_controller__DOT__bit_controller__DOT__fSCL,2,0);
    VL_SIG8(v__DOT__byte_controller__DOT__bit_controller__DOT__fSDA,2,0);
    VL_SIG8(v__DOT__byte_controller__DOT__bit_controller__DOT__sSCL,0,0);
    VL_SIG8(v__DOT__byte_controller__DOT__bit_controller__DOT__sSDA,0,0);
    VL_SIG8(v__DOT__byte_controller__DOT__bit_controller__DOT__dSCL,0,0);
    VL_SIG8(v__DOT__byte_controller__DOT__bit_controller__DOT__dSDA,0,0);
    VL_SIG8(v__DOT__byte_controller__DOT__bit_controller__DOT__dscl_oen,0,0);
    VL_SIG8(v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk,0,0);
    VL_SIG8(v__DOT__byte_controller__DOT__bit_controller__DOT__clk_en,0,0);
    VL_SIG8(v__DOT__byte_controller__DOT__bit_controller__DOT__slave_wait,0,0);
    VL_SIG8(v__DOT__byte_controller__DOT__bit_controller__DOT__sta_condition,0,0);
    VL_SIG8(v__DOT__byte_controller__DOT__bit_controller__DOT__sto_condition,0,0);
    VL_SIG8(v__DOT__byte_controller__DOT__bit_controller__DOT__cmd_stop,0,0);
    //char	__VpadToAlign109[1];
    VL_SIG16(v__DOT__prer,15,0);
    VL_SIG16(v__DOT__byte_controller__DOT__bit_controller__DOT__cnt,15,0);
    VL_SIG16(v__DOT__byte_controller__DOT__bit_controller__DOT__filter_cnt,13,0);
    VL_SIG(v__DOT__byte_controller__DOT__bit_controller__DOT__c_state,17,0);
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    VL_SIG8(__Vcellinp__v__wb_clk_i,0,0);
    VL_SIG8(__Vcellinp__v__arst_i,0,0);
    VL_SIG8(__Vcellinp__v__wb_rst_i,0,0);
    VL_SIG8(__Vcellinp__v__wb_adr_i,2,0);
    VL_SIG8(__Vcellinp__v__wb_dat_i,7,0);
    VL_SIG8(__Vcellinp__v__wb_dat_o,7,0);
    VL_SIG8(__Vcellinp__v__wb_we_i,0,0);
    VL_SIG8(__Vcellinp__v__wb_stb_i,0,0);
    VL_SIG8(__Vcellinp__v__wb_cyc_i,0,0);
    VL_SIG8(__Vcellinp__v__wb_ack_o,0,0);
    VL_SIG8(__Vcellinp__v__wb_inta_o,0,0);
    VL_SIG8(__Vcellinp__v__scl_pad_i,0,0);
    VL_SIG8(__Vcellinp__v__scl_padoen_o,0,0);
    VL_SIG8(__Vcellinp__v__sda_pad_i,0,0);
    VL_SIG8(__Vcellinp__v__sda_padoen_o,0,0);
    VL_SIG8(__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__fSCL,2,0);
    VL_SIG8(__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__fSDA,2,0);
    VL_SIG8(__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sSCL,0,0);
    VL_SIG8(__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sSDA,0,0);
    VL_SIG8(__Vdly____Vcellinp__v__scl_padoen_o,0,0);
    VL_SIG8(__VinpClk__TOP____Vcellinp__v__arst_i,0,0);
    VL_SIG8(__Vclklast__TOP____Vcellinp__v__wb_clk_i,0,0);
    VL_SIG8(__Vclklast__TOP____VinpClk__TOP____Vcellinp__v__arst_i,0,0);
    VL_SIG8(__Vchglast__TOP____Vcellinp__v__arst_i,0,0);
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vi2c_master_top__Syms*	__VlSymsp;		// Symbol table
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
    
    // CONSTRUCTORS
  private:
    Vi2c_master_top& operator= (const Vi2c_master_top&);	///< Copying not allowed
    Vi2c_master_top(const Vi2c_master_top&);	///< Copying not allowed
  public:
    SC_CTOR(Vi2c_master_top);
    virtual ~Vi2c_master_top();
    
    // USER METHODS
    
    // API METHODS
  private:
    void eval();
  public:
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vi2c_master_top__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vi2c_master_top__Syms* symsp, bool first);
  private:
    static IData	_change_request(Vi2c_master_top__Syms* __restrict vlSymsp);
  public:
    static void	_combo__TOP__10(Vi2c_master_top__Syms* __restrict vlSymsp);
    static void	_combo__TOP__2(Vi2c_master_top__Syms* __restrict vlSymsp);
    static void	_combo__TOP__5(Vi2c_master_top__Syms* __restrict vlSymsp);
    static void	_eval(Vi2c_master_top__Syms* __restrict vlSymsp);
    static void	_eval_initial(Vi2c_master_top__Syms* __restrict vlSymsp);
    static void	_eval_settle(Vi2c_master_top__Syms* __restrict vlSymsp);
    static void	_sequent__TOP__3(Vi2c_master_top__Syms* __restrict vlSymsp);
    static void	_sequent__TOP__4(Vi2c_master_top__Syms* __restrict vlSymsp);
    static void	_sequent__TOP__7(Vi2c_master_top__Syms* __restrict vlSymsp);
    static void	_sequent__TOP__8(Vi2c_master_top__Syms* __restrict vlSymsp);
    static void	_settle__TOP__1(Vi2c_master_top__Syms* __restrict vlSymsp);
    static void	_settle__TOP__6(Vi2c_master_top__Syms* __restrict vlSymsp);
    static void	_settle__TOP__9(Vi2c_master_top__Syms* __restrict vlSymsp);
} VL_ATTR_ALIGNED(64);

#endif  /*guard*/
