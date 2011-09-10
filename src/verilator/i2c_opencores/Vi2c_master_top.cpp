// Verilated -*- SystemC -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vi2c_master_top.h for the primary calling header

#include "Vi2c_master_top.h"   // For This
#include "Vi2c_master_top__Syms.h"

//--------------------
// STATIC VARIABLES


//--------------------

VL_SC_CTOR_IMP(Vi2c_master_top)
#if (SYSTEMC_VERSION>20011000)
    : wb_clk_i("wb_clk_i"), wb_rst_i("wb_rst_i"), arst_i("arst_i"), 
      wb_adr_i("wb_adr_i"), wb_dat_i("wb_dat_i"), wb_dat_o("wb_dat_o"), 
      wb_we_i("wb_we_i"), wb_stb_i("wb_stb_i"), wb_cyc_i("wb_cyc_i"), 
      wb_ack_o("wb_ack_o"), wb_inta_o("wb_inta_o"), 
      scl_pad_i("scl_pad_i"), scl_pad_o("scl_pad_o"), 
      scl_padoen_o("scl_padoen_o"), sda_pad_i("sda_pad_i"), 
      sda_pad_o("sda_pad_o"), sda_padoen_o("sda_padoen_o")
#endif
 {
    Vi2c_master_top__Syms* __restrict vlSymsp = __VlSymsp = new Vi2c_master_top__Syms(this, name());
    Vi2c_master_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Sensitivities on all clocks and combo inputs
    SC_METHOD(eval);
    sensitive << wb_clk_i;
    sensitive << wb_rst_i;
    sensitive << arst_i;
    sensitive << wb_adr_i;
    sensitive << wb_dat_i;
    sensitive << wb_we_i;
    sensitive << wb_stb_i;
    sensitive << wb_cyc_i;
    sensitive << scl_pad_i;
    sensitive << sda_pad_i;
    
    // Reset internal values
    
    // Reset structure values
    __Vcellinp__v__wb_clk_i = VL_RAND_RESET_I(1);
    __Vcellinp__v__wb_rst_i = VL_RAND_RESET_I(1);
    __Vcellinp__v__arst_i = VL_RAND_RESET_I(1);
    __Vcellinp__v__wb_adr_i = VL_RAND_RESET_I(3);
    __Vcellinp__v__wb_dat_i = VL_RAND_RESET_I(8);
    __Vcellinp__v__wb_dat_o = VL_RAND_RESET_I(8);
    __Vcellinp__v__wb_we_i = VL_RAND_RESET_I(1);
    __Vcellinp__v__wb_stb_i = VL_RAND_RESET_I(1);
    __Vcellinp__v__wb_cyc_i = VL_RAND_RESET_I(1);
    __Vcellinp__v__wb_ack_o = VL_RAND_RESET_I(1);
    __Vcellinp__v__wb_inta_o = VL_RAND_RESET_I(1);
    __Vcellinp__v__scl_pad_i = VL_RAND_RESET_I(1);
    __Vcellinp__v__scl_padoen_o = VL_RAND_RESET_I(1);
    __Vcellinp__v__sda_pad_i = VL_RAND_RESET_I(1);
    __Vcellinp__v__sda_padoen_o = VL_RAND_RESET_I(1);
    v__DOT__prer = VL_RAND_RESET_I(16);
    v__DOT__ctr = VL_RAND_RESET_I(8);
    v__DOT__txr = VL_RAND_RESET_I(8);
    v__DOT__cr = VL_RAND_RESET_I(8);
    v__DOT__sr = VL_RAND_RESET_I(8);
    v__DOT__done = VL_RAND_RESET_I(1);
    v__DOT__irxack = VL_RAND_RESET_I(1);
    v__DOT__rxack = VL_RAND_RESET_I(1);
    v__DOT__tip = VL_RAND_RESET_I(1);
    v__DOT__irq_flag = VL_RAND_RESET_I(1);
    v__DOT__i2c_busy = VL_RAND_RESET_I(1);
    v__DOT__i2c_al = VL_RAND_RESET_I(1);
    v__DOT__al = VL_RAND_RESET_I(1);
    v__DOT__wb_wacc = VL_RAND_RESET_I(1);
    v__DOT__byte_controller__DOT__core_cmd = VL_RAND_RESET_I(4);
    v__DOT__byte_controller__DOT__core_txd = VL_RAND_RESET_I(1);
    v__DOT__byte_controller__DOT__core_ack = VL_RAND_RESET_I(1);
    v__DOT__byte_controller__DOT__core_rxd = VL_RAND_RESET_I(1);
    v__DOT__byte_controller__DOT__sr = VL_RAND_RESET_I(8);
    v__DOT__byte_controller__DOT__shift = VL_RAND_RESET_I(1);
    v__DOT__byte_controller__DOT__ld = VL_RAND_RESET_I(1);
    v__DOT__byte_controller__DOT__dcnt = VL_RAND_RESET_I(3);
    v__DOT__byte_controller__DOT__c_state = VL_RAND_RESET_I(5);
    v__DOT__byte_controller__DOT__bit_controller__DOT__cSCL = VL_RAND_RESET_I(2);
    v__DOT__byte_controller__DOT__bit_controller__DOT__cSDA = VL_RAND_RESET_I(2);
    v__DOT__byte_controller__DOT__bit_controller__DOT__fSCL = VL_RAND_RESET_I(3);
    v__DOT__byte_controller__DOT__bit_controller__DOT__fSDA = VL_RAND_RESET_I(3);
    v__DOT__byte_controller__DOT__bit_controller__DOT__sSCL = VL_RAND_RESET_I(1);
    v__DOT__byte_controller__DOT__bit_controller__DOT__sSDA = VL_RAND_RESET_I(1);
    v__DOT__byte_controller__DOT__bit_controller__DOT__dSCL = VL_RAND_RESET_I(1);
    v__DOT__byte_controller__DOT__bit_controller__DOT__dSDA = VL_RAND_RESET_I(1);
    v__DOT__byte_controller__DOT__bit_controller__DOT__dscl_oen = VL_RAND_RESET_I(1);
    v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk = VL_RAND_RESET_I(1);
    v__DOT__byte_controller__DOT__bit_controller__DOT__clk_en = VL_RAND_RESET_I(1);
    v__DOT__byte_controller__DOT__bit_controller__DOT__slave_wait = VL_RAND_RESET_I(1);
    v__DOT__byte_controller__DOT__bit_controller__DOT__cnt = VL_RAND_RESET_I(16);
    v__DOT__byte_controller__DOT__bit_controller__DOT__filter_cnt = VL_RAND_RESET_I(14);
    v__DOT__byte_controller__DOT__bit_controller__DOT__c_state = VL_RAND_RESET_I(18);
    v__DOT__byte_controller__DOT__bit_controller__DOT__sta_condition = VL_RAND_RESET_I(1);
    v__DOT__byte_controller__DOT__bit_controller__DOT__sto_condition = VL_RAND_RESET_I(1);
    v__DOT__byte_controller__DOT__bit_controller__DOT__cmd_stop = VL_RAND_RESET_I(1);
    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__fSCL = VL_RAND_RESET_I(3);
    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__fSDA = VL_RAND_RESET_I(3);
    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sSCL = VL_RAND_RESET_I(1);
    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sSDA = VL_RAND_RESET_I(1);
    __Vdly____Vcellinp__v__scl_padoen_o = VL_RAND_RESET_I(1);
    __VinpClk__TOP____Vcellinp__v__arst_i = VL_RAND_RESET_I(1);
    __Vclklast__TOP____Vcellinp__v__wb_clk_i = VL_RAND_RESET_I(1);
    __Vclklast__TOP____VinpClk__TOP____Vcellinp__v__arst_i = VL_RAND_RESET_I(1);
    __Vchglast__TOP____Vcellinp__v__arst_i = VL_RAND_RESET_I(1);
}

void Vi2c_master_top::__Vconfigure(Vi2c_master_top__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vi2c_master_top::~Vi2c_master_top() {
    delete __VlSymsp; __VlSymsp=NULL;
}

//--------------------


void Vi2c_master_top::eval() {
    Vi2c_master_top__Syms* __restrict vlSymsp = this->__VlSymsp; // Setup global symbol table
    Vi2c_master_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    VL_DEBUG_IF(VL_PRINTF("\n----TOP Evaluate Vi2c_master_top::eval\n"); );
    int __VclockLoop = 0;
    IData __Vchange=1;
    while (VL_LIKELY(__Vchange)) {
	VL_DEBUG_IF(VL_PRINTF(" Clock loop\n"););
	vlSymsp->__Vm_activity = true;
	_eval(vlSymsp);
	__Vchange = _change_request(vlSymsp);
	if (++__VclockLoop > 100) vl_fatal(__FILE__,__LINE__,__FILE__,"Verilated model didn't converge");
    }
}

void Vi2c_master_top::_eval_initial_loop(Vi2c_master_top__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    vlSymsp->__Vm_activity = true;
    int __VclockLoop = 0;
    IData __Vchange=1;
    while (VL_LIKELY(__Vchange)) {
	_eval_settle(vlSymsp);
	_eval(vlSymsp);
	__Vchange = _change_request(vlSymsp);
	if (++__VclockLoop > 100) vl_fatal(__FILE__,__LINE__,__FILE__,"Verilated model didn't DC converge");
    }
}

//--------------------
// Internal Methods

void Vi2c_master_top::_settle__TOP__1(Vi2c_master_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vi2c_master_top::_settle__TOP__1\n"); );
    Vi2c_master_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SII(1,vlTOPp->scl_pad_o, 0);
    VL_ASSIGN_SII(1,vlTOPp->sda_pad_o, 0);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__wb_we_i, vlTOPp->wb_we_i);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__wb_clk_i, vlTOPp->wb_clk_i);
}

void Vi2c_master_top::_combo__TOP__2(Vi2c_master_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vi2c_master_top::_combo__TOP__2\n"); );
    Vi2c_master_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__wb_we_i, vlTOPp->wb_we_i);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__wb_clk_i, vlTOPp->wb_clk_i);
}

void Vi2c_master_top::_sequent__TOP__3(Vi2c_master_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vi2c_master_top::_sequent__TOP__3\n"); );
    Vi2c_master_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VL_SIG8(__Vdly____Vcellinp__v__wb_ack_o,0,0);
    //char	__VpadToAlign45[3];
    // Body
    __Vdly____Vcellinp__v__wb_ack_o = vlTOPp->__Vcellinp__v__wb_ack_o;
    // ALWAYS at i2c_master_top.v:158
    __Vdly____Vcellinp__v__wb_ack_o = (((IData)(vlTOPp->__Vcellinp__v__wb_cyc_i) 
					& (IData)(vlTOPp->__Vcellinp__v__wb_stb_i)) 
				       & (~ (IData)(vlTOPp->__Vcellinp__v__wb_ack_o)));
    // ALWAYS at i2c_master_top.v:162
    vlTOPp->__Vcellinp__v__wb_dat_o = (0xff & ((4 & (IData)(vlTOPp->__Vcellinp__v__wb_adr_i))
					        ? (
						   (2 
						    & (IData)(vlTOPp->__Vcellinp__v__wb_adr_i))
						    ? 
						   ((1 
						     & (IData)(vlTOPp->__Vcellinp__v__wb_adr_i))
						     ? 0
						     : (IData)(vlTOPp->v__DOT__cr))
						    : 
						   ((1 
						     & (IData)(vlTOPp->__Vcellinp__v__wb_adr_i))
						     ? (IData)(vlTOPp->v__DOT__txr)
						     : (IData)(vlTOPp->v__DOT__sr)))
					        : (
						   (2 
						    & (IData)(vlTOPp->__Vcellinp__v__wb_adr_i))
						    ? 
						   ((1 
						     & (IData)(vlTOPp->__Vcellinp__v__wb_adr_i))
						     ? (IData)(vlTOPp->v__DOT__byte_controller__DOT__sr)
						     : (IData)(vlTOPp->v__DOT__ctr))
						    : 
						   ((1 
						     & (IData)(vlTOPp->__Vcellinp__v__wb_adr_i))
						     ? 
						    ((IData)(vlTOPp->v__DOT__prer) 
						     >> 8)
						     : (IData)(vlTOPp->v__DOT__prer)))));
    vlTOPp->__Vcellinp__v__wb_ack_o = __Vdly____Vcellinp__v__wb_ack_o;
    VL_ASSIGN_SII(1,vlTOPp->wb_ack_o, vlTOPp->__Vcellinp__v__wb_ack_o);
    VL_ASSIGN_SII(8,vlTOPp->wb_dat_o, vlTOPp->__Vcellinp__v__wb_dat_o);
}

void Vi2c_master_top::_sequent__TOP__4(Vi2c_master_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vi2c_master_top::_sequent__TOP__4\n"); );
    Vi2c_master_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VL_SIG8(__Vdly__v__DOT__al,0,0);
    VL_SIG8(__Vdly__v__DOT__irq_flag,0,0);
    VL_SIG8(__Vdly__v__DOT__byte_controller__DOT__sr,7,0);
    VL_SIG8(__Vdly__v__DOT__byte_controller__DOT__dcnt,2,0);
    VL_SIG8(__Vdly__v__DOT__byte_controller__DOT__core_cmd,3,0);
    VL_SIG8(__Vdly__v__DOT__byte_controller__DOT__core_txd,0,0);
    VL_SIG8(__Vdly__v__DOT__done,0,0);
    VL_SIG8(__Vdly__v__DOT__byte_controller__DOT__c_state,4,0);
    VL_SIG8(__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__slave_wait,0,0);
    VL_SIG8(__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__cSCL,1,0);
    VL_SIG8(__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__cSDA,1,0);
    VL_SIG8(__Vdly__v__DOT__i2c_busy,0,0);
    VL_SIG8(__Vdly____Vcellinp__v__sda_padoen_o,0,0);
    VL_SIG8(__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk,0,0);
    VL_SIG16(__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__cnt,15,0);
    VL_SIG16(__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__filter_cnt,13,0);
    //char	__VpadToAlign86[2];
    VL_SIG(__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state,17,0);
    // Body
    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__cSDA 
	= vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__cSDA;
    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__cSCL 
	= vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__cSCL;
    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__slave_wait 
	= vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__slave_wait;
    vlTOPp->__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__fSCL 
	= vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__fSCL;
    vlTOPp->__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__fSDA 
	= vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__fSDA;
    vlTOPp->__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sSDA 
	= vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sSDA;
    vlTOPp->__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sSCL 
	= vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sSCL;
    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__filter_cnt 
	= vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__filter_cnt;
    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__cnt 
	= vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__cnt;
    __Vdly__v__DOT__i2c_busy = vlTOPp->v__DOT__i2c_busy;
    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state 
	= vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state;
    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk 
	= vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk;
    vlTOPp->__Vdly____Vcellinp__v__scl_padoen_o = vlTOPp->__Vcellinp__v__scl_padoen_o;
    __Vdly____Vcellinp__v__sda_padoen_o = vlTOPp->__Vcellinp__v__sda_padoen_o;
    __Vdly__v__DOT__byte_controller__DOT__c_state = vlTOPp->v__DOT__byte_controller__DOT__c_state;
    __Vdly__v__DOT__done = vlTOPp->v__DOT__done;
    __Vdly__v__DOT__byte_controller__DOT__core_txd 
	= vlTOPp->v__DOT__byte_controller__DOT__core_txd;
    __Vdly__v__DOT__byte_controller__DOT__core_cmd 
	= vlTOPp->v__DOT__byte_controller__DOT__core_cmd;
    __Vdly__v__DOT__irq_flag = vlTOPp->v__DOT__irq_flag;
    __Vdly__v__DOT__al = vlTOPp->v__DOT__al;
    __Vdly__v__DOT__byte_controller__DOT__dcnt = vlTOPp->v__DOT__byte_controller__DOT__dcnt;
    __Vdly__v__DOT__byte_controller__DOT__sr = vlTOPp->v__DOT__byte_controller__DOT__sr;
    // ALWAYS at i2c_master_bit_ctrl.v:235
    if (vlTOPp->__Vcellinp__v__arst_i) {
	if (vlTOPp->__Vcellinp__v__wb_rst_i) {
	    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__cSCL = 0;
	    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__cSDA = 0;
	} else {
	    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__cSCL 
		= ((2 & ((IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__cSCL) 
			 << 1)) | (IData)(vlTOPp->__Vcellinp__v__scl_pad_i));
	    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__cSDA 
		= ((2 & ((IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__cSDA) 
			 << 1)) | (IData)(vlTOPp->__Vcellinp__v__sda_pad_i));
	}
    } else {
	__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__cSCL = 0;
	__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__cSDA = 0;
    }
    // ALWAYS at i2c_master_bit_ctrl.v:198
    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__slave_wait 
	= ((IData)(vlTOPp->__Vcellinp__v__arst_i) & 
	   ((((IData)(vlTOPp->__Vcellinp__v__scl_padoen_o) 
	      & (~ (IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__dscl_oen))) 
	     & (~ (IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sSCL))) 
	    | ((IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__slave_wait) 
	       & (~ (IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sSCL)))));
    // ALWAYS at i2c_master_bit_ctrl.v:263
    if (vlTOPp->__Vcellinp__v__arst_i) {
	if (vlTOPp->__Vcellinp__v__wb_rst_i) {
	    vlTOPp->__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__fSCL = 7;
	    vlTOPp->__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__fSDA = 7;
	} else {
	    if ((1 & (~ (IData)((0 != (IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__filter_cnt)))))) {
		vlTOPp->__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__fSCL 
		    = ((6 & ((IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__fSCL) 
			     << 1)) | (1 & ((IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__cSCL) 
					    >> 1)));
		vlTOPp->__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__fSDA 
		    = ((6 & ((IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__fSDA) 
			     << 1)) | (1 & ((IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__cSDA) 
					    >> 1)));
	    }
	}
    } else {
	vlTOPp->__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__fSCL = 7;
	vlTOPp->__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__fSDA = 7;
    }
    // ALWAYS at i2c_master_top.v:284
    vlTOPp->__Vcellinp__v__wb_inta_o = ((IData)(vlTOPp->__Vcellinp__v__arst_i) 
					& ((~ (IData)(vlTOPp->__Vcellinp__v__wb_rst_i)) 
					   & ((IData)(vlTOPp->v__DOT__irq_flag) 
					      & ((IData)(vlTOPp->v__DOT__ctr) 
						 >> 6))));
    // ALWAYS at i2c_master_bit_ctrl.v:254
    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__filter_cnt 
	= (0x3fff & ((IData)(vlTOPp->__Vcellinp__v__arst_i)
		      ? ((1 & ((IData)(vlTOPp->__Vcellinp__v__wb_rst_i) 
			       | (~ ((IData)(vlTOPp->v__DOT__ctr) 
				     >> 7)))) ? 0 : 
			 ((0 != (IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__filter_cnt))
			   ? ((IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__filter_cnt) 
			      - (IData)(1)) : (0xffff 
					       & ((IData)(vlTOPp->v__DOT__prer) 
						  >> 2))))
		      : 0));
    // ALWAYS at i2c_master_bit_ctrl.v:331
    __Vdly__v__DOT__i2c_busy = ((IData)(vlTOPp->__Vcellinp__v__arst_i) 
				& ((~ (IData)(vlTOPp->__Vcellinp__v__wb_rst_i)) 
				   & (((IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sta_condition) 
				       | (IData)(vlTOPp->v__DOT__i2c_busy)) 
				      & (~ (IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sto_condition)))));
    // ALWAYS at i2c_master_top.v:260
    if (vlTOPp->__Vcellinp__v__arst_i) {
	if (vlTOPp->__Vcellinp__v__wb_rst_i) {
	    __Vdly__v__DOT__al = 0;
	    vlTOPp->v__DOT__rxack = 0;
	    vlTOPp->v__DOT__tip = 0;
	    __Vdly__v__DOT__irq_flag = 0;
	} else {
	    __Vdly__v__DOT__al = ((IData)(vlTOPp->v__DOT__i2c_al) 
				  | ((IData)(vlTOPp->v__DOT__al) 
				     & (~ ((IData)(vlTOPp->v__DOT__cr) 
					   >> 7))));
	    __Vdly__v__DOT__irq_flag = ((((IData)(vlTOPp->v__DOT__done) 
					  | (IData)(vlTOPp->v__DOT__i2c_al)) 
					 | (IData)(vlTOPp->v__DOT__irq_flag)) 
					& (~ (IData)(vlTOPp->v__DOT__cr)));
	    vlTOPp->v__DOT__rxack = vlTOPp->v__DOT__irxack;
	    vlTOPp->v__DOT__tip = (1 & (((IData)(vlTOPp->v__DOT__cr) 
					 >> 5) | ((IData)(vlTOPp->v__DOT__cr) 
						  >> 4)));
	}
    } else {
	__Vdly__v__DOT__al = 0;
	vlTOPp->v__DOT__rxack = 0;
	vlTOPp->v__DOT__tip = 0;
	__Vdly__v__DOT__irq_flag = 0;
    }
    // ALWAYS at i2c_master_byte_ctrl.v:184
    if (vlTOPp->__Vcellinp__v__arst_i) {
	if (vlTOPp->__Vcellinp__v__wb_rst_i) {
	    __Vdly__v__DOT__byte_controller__DOT__dcnt = 0;
	} else {
	    if (vlTOPp->v__DOT__byte_controller__DOT__ld) {
		__Vdly__v__DOT__byte_controller__DOT__dcnt = 7;
	    } else {
		if (vlTOPp->v__DOT__byte_controller__DOT__shift) {
		    __Vdly__v__DOT__byte_controller__DOT__dcnt 
			= (7 & ((IData)(vlTOPp->v__DOT__byte_controller__DOT__dcnt) 
				- (IData)(1)));
		}
	    }
	}
    } else {
	__Vdly__v__DOT__byte_controller__DOT__dcnt = 0;
    }
    // ALWAYS at i2c_master_byte_ctrl.v:173
    if (vlTOPp->__Vcellinp__v__arst_i) {
	if (vlTOPp->__Vcellinp__v__wb_rst_i) {
	    __Vdly__v__DOT__byte_controller__DOT__sr = 0;
	} else {
	    if (vlTOPp->v__DOT__byte_controller__DOT__ld) {
		__Vdly__v__DOT__byte_controller__DOT__sr 
		    = vlTOPp->v__DOT__txr;
	    } else {
		if (vlTOPp->v__DOT__byte_controller__DOT__shift) {
		    __Vdly__v__DOT__byte_controller__DOT__sr 
			= ((0xfe & ((IData)(vlTOPp->v__DOT__byte_controller__DOT__sr) 
				    << 1)) | (IData)(vlTOPp->v__DOT__byte_controller__DOT__core_rxd));
		}
	    }
	}
    } else {
	__Vdly__v__DOT__byte_controller__DOT__sr = 0;
    }
    vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__cSCL 
	= __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__cSCL;
    vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__cSDA 
	= __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__cSDA;
    vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__filter_cnt 
	= __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__filter_cnt;
    vlTOPp->v__DOT__i2c_busy = __Vdly__v__DOT__i2c_busy;
    vlTOPp->v__DOT__irq_flag = __Vdly__v__DOT__irq_flag;
    vlTOPp->v__DOT__al = __Vdly__v__DOT__al;
    VL_ASSIGN_SII(1,vlTOPp->wb_inta_o, vlTOPp->__Vcellinp__v__wb_inta_o);
    vlTOPp->v__DOT__sr = ((0xfc & (IData)(vlTOPp->v__DOT__sr)) 
			  | (((IData)(vlTOPp->v__DOT__tip) 
			      << 1) | (IData)(vlTOPp->v__DOT__irq_flag)));
    vlTOPp->v__DOT__sr = ((3 & (IData)(vlTOPp->v__DOT__sr)) 
			  | (((IData)(vlTOPp->v__DOT__rxack) 
			      << 7) | (((IData)(vlTOPp->v__DOT__i2c_busy) 
					<< 6) | ((IData)(vlTOPp->v__DOT__al) 
						 << 5))));
    // ALWAYS at i2c_master_byte_ctrl.v:201
    if (vlTOPp->__Vcellinp__v__arst_i) {
	if (((IData)(vlTOPp->__Vcellinp__v__wb_rst_i) 
	     | (IData)(vlTOPp->v__DOT__i2c_al))) {
	    __Vdly__v__DOT__byte_controller__DOT__core_cmd = 0;
	    __Vdly__v__DOT__byte_controller__DOT__core_txd = 0;
	    vlTOPp->v__DOT__byte_controller__DOT__shift = 0;
	    vlTOPp->v__DOT__byte_controller__DOT__ld = 0;
	    __Vdly__v__DOT__done = 0;
	    __Vdly__v__DOT__byte_controller__DOT__c_state = 0;
	    vlTOPp->v__DOT__irxack = 0;
	} else {
	    __Vdly__v__DOT__byte_controller__DOT__core_txd 
		= (1 & ((IData)(vlTOPp->v__DOT__byte_controller__DOT__sr) 
			>> 7));
	    vlTOPp->v__DOT__byte_controller__DOT__shift = 0;
	    vlTOPp->v__DOT__byte_controller__DOT__ld = 0;
	    __Vdly__v__DOT__done = 0;
	    if ((0 == (IData)(vlTOPp->v__DOT__byte_controller__DOT__c_state))) {
		if ((1 & (((((IData)(vlTOPp->v__DOT__cr) 
			     >> 5) | ((IData)(vlTOPp->v__DOT__cr) 
				      >> 4)) | ((IData)(vlTOPp->v__DOT__cr) 
						>> 6)) 
			  & (~ (IData)(vlTOPp->v__DOT__done))))) {
		    if ((0x80 & (IData)(vlTOPp->v__DOT__cr))) {
			__Vdly__v__DOT__byte_controller__DOT__c_state = 1;
			__Vdly__v__DOT__byte_controller__DOT__core_cmd = 1;
		    } else {
			if ((0x20 & (IData)(vlTOPp->v__DOT__cr))) {
			    __Vdly__v__DOT__byte_controller__DOT__c_state = 2;
			    __Vdly__v__DOT__byte_controller__DOT__core_cmd = 8;
			} else {
			    if ((0x10 & (IData)(vlTOPp->v__DOT__cr))) {
				__Vdly__v__DOT__byte_controller__DOT__c_state = 4;
				__Vdly__v__DOT__byte_controller__DOT__core_cmd = 4;
			    } else {
				__Vdly__v__DOT__byte_controller__DOT__c_state = 0x10;
				__Vdly__v__DOT__byte_controller__DOT__core_cmd = 2;
			    }
			}
		    }
		    vlTOPp->v__DOT__byte_controller__DOT__ld = 1;
		}
	    } else {
		if ((1 == (IData)(vlTOPp->v__DOT__byte_controller__DOT__c_state))) {
		    if (vlTOPp->v__DOT__byte_controller__DOT__core_ack) {
			if ((0x20 & (IData)(vlTOPp->v__DOT__cr))) {
			    __Vdly__v__DOT__byte_controller__DOT__c_state = 2;
			    __Vdly__v__DOT__byte_controller__DOT__core_cmd = 8;
			} else {
			    __Vdly__v__DOT__byte_controller__DOT__c_state = 4;
			    __Vdly__v__DOT__byte_controller__DOT__core_cmd = 4;
			}
			vlTOPp->v__DOT__byte_controller__DOT__ld = 1;
		    }
		} else {
		    if ((4 == (IData)(vlTOPp->v__DOT__byte_controller__DOT__c_state))) {
			if (vlTOPp->v__DOT__byte_controller__DOT__core_ack) {
			    if ((0 != (IData)(vlTOPp->v__DOT__byte_controller__DOT__dcnt))) {
				__Vdly__v__DOT__byte_controller__DOT__c_state = 4;
				__Vdly__v__DOT__byte_controller__DOT__core_cmd = 4;
				vlTOPp->v__DOT__byte_controller__DOT__shift = 1;
			    } else {
				__Vdly__v__DOT__byte_controller__DOT__c_state = 8;
				__Vdly__v__DOT__byte_controller__DOT__core_cmd = 8;
			    }
			}
		    } else {
			if ((2 == (IData)(vlTOPp->v__DOT__byte_controller__DOT__c_state))) {
			    if (vlTOPp->v__DOT__byte_controller__DOT__core_ack) {
				if ((0 != (IData)(vlTOPp->v__DOT__byte_controller__DOT__dcnt))) {
				    __Vdly__v__DOT__byte_controller__DOT__c_state = 2;
				    __Vdly__v__DOT__byte_controller__DOT__core_cmd = 8;
				} else {
				    __Vdly__v__DOT__byte_controller__DOT__c_state = 8;
				    __Vdly__v__DOT__byte_controller__DOT__core_cmd = 4;
				}
				vlTOPp->v__DOT__byte_controller__DOT__shift = 1;
				__Vdly__v__DOT__byte_controller__DOT__core_txd 
				    = (1 & ((IData)(vlTOPp->v__DOT__cr) 
					    >> 3));
			    }
			} else {
			    if ((8 == (IData)(vlTOPp->v__DOT__byte_controller__DOT__c_state))) {
				if (vlTOPp->v__DOT__byte_controller__DOT__core_ack) {
				    if ((0x40 & (IData)(vlTOPp->v__DOT__cr))) {
					__Vdly__v__DOT__byte_controller__DOT__c_state = 0x10;
					__Vdly__v__DOT__byte_controller__DOT__core_cmd = 2;
				    } else {
					__Vdly__v__DOT__byte_controller__DOT__c_state = 0;
					__Vdly__v__DOT__byte_controller__DOT__core_cmd = 0;
					__Vdly__v__DOT__done = 1;
				    }
				    vlTOPp->v__DOT__irxack 
					= vlTOPp->v__DOT__byte_controller__DOT__core_rxd;
				    __Vdly__v__DOT__byte_controller__DOT__core_txd = 1;
				} else {
				    __Vdly__v__DOT__byte_controller__DOT__core_txd 
					= (1 & ((IData)(vlTOPp->v__DOT__cr) 
						>> 3));
				}
			    } else {
				if ((0x10 == (IData)(vlTOPp->v__DOT__byte_controller__DOT__c_state))) {
				    if (vlTOPp->v__DOT__byte_controller__DOT__core_ack) {
					__Vdly__v__DOT__byte_controller__DOT__c_state = 0;
					__Vdly__v__DOT__byte_controller__DOT__core_cmd = 0;
					__Vdly__v__DOT__done = 1;
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    } else {
	__Vdly__v__DOT__done = 0;
	__Vdly__v__DOT__byte_controller__DOT__core_cmd = 0;
	__Vdly__v__DOT__byte_controller__DOT__core_txd = 0;
	vlTOPp->v__DOT__byte_controller__DOT__shift = 0;
	vlTOPp->v__DOT__byte_controller__DOT__ld = 0;
	__Vdly__v__DOT__byte_controller__DOT__c_state = 0;
	vlTOPp->v__DOT__irxack = 0;
    }
    vlTOPp->v__DOT__byte_controller__DOT__c_state = __Vdly__v__DOT__byte_controller__DOT__c_state;
    vlTOPp->v__DOT__byte_controller__DOT__dcnt = __Vdly__v__DOT__byte_controller__DOT__dcnt;
    vlTOPp->v__DOT__byte_controller__DOT__sr = __Vdly__v__DOT__byte_controller__DOT__sr;
    // ALWAYS at i2c_master_top.v:201
    if (vlTOPp->__Vcellinp__v__arst_i) {
	if (vlTOPp->__Vcellinp__v__wb_rst_i) {
	    vlTOPp->v__DOT__cr = 0;
	} else {
	    if (vlTOPp->v__DOT__wb_wacc) {
		if ((((IData)(vlTOPp->v__DOT__ctr) 
		      >> 7) & (4 == (IData)(vlTOPp->__Vcellinp__v__wb_adr_i)))) {
		    vlTOPp->v__DOT__cr = vlTOPp->__Vcellinp__v__wb_dat_i;
		}
	    } else {
		if (((IData)(vlTOPp->v__DOT__done) 
		     | (IData)(vlTOPp->v__DOT__i2c_al))) {
		    vlTOPp->v__DOT__cr = (0xf & (IData)(vlTOPp->v__DOT__cr));
		}
		vlTOPp->v__DOT__cr = (0xf8 & (IData)(vlTOPp->v__DOT__cr));
	    }
	}
    } else {
	vlTOPp->v__DOT__cr = 0;
    }
    // ALWAYS at i2c_master_bit_ctrl.v:386
    if (vlTOPp->__Vcellinp__v__arst_i) {
	if (((IData)(vlTOPp->__Vcellinp__v__wb_rst_i) 
	     | (IData)(vlTOPp->v__DOT__i2c_al))) {
	    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state = 0;
	    vlTOPp->v__DOT__byte_controller__DOT__core_ack = 0;
	    vlTOPp->__Vdly____Vcellinp__v__scl_padoen_o = 1;
	    __Vdly____Vcellinp__v__sda_padoen_o = 1;
	    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk = 0;
	} else {
	    vlTOPp->v__DOT__byte_controller__DOT__core_ack = 0;
	    if (vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__clk_en) {
		if (((((((((0 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state) 
			   | (1 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) 
			  | (2 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) 
			 | (4 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) 
			| (8 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) 
		       | (0x10 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) 
		      | (0x20 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) 
		     | (0x40 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state))) {
		    if ((0 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) {
			vlTOPp->__Vdly____Vcellinp__v__scl_padoen_o 
			    = vlTOPp->__Vcellinp__v__scl_padoen_o;
			__Vdly____Vcellinp__v__sda_padoen_o 
			    = vlTOPp->__Vcellinp__v__sda_padoen_o;
			__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state 
			    = ((8 & (IData)(vlTOPp->v__DOT__byte_controller__DOT__core_cmd))
			        ? ((4 & (IData)(vlTOPp->v__DOT__byte_controller__DOT__core_cmd))
				    ? 0 : ((2 & (IData)(vlTOPp->v__DOT__byte_controller__DOT__core_cmd))
					    ? 0 : (
						   (1 
						    & (IData)(vlTOPp->v__DOT__byte_controller__DOT__core_cmd))
						    ? 0
						    : 0x200)))
			        : ((4 & (IData)(vlTOPp->v__DOT__byte_controller__DOT__core_cmd))
				    ? ((2 & (IData)(vlTOPp->v__DOT__byte_controller__DOT__core_cmd))
				        ? 0 : ((1 & (IData)(vlTOPp->v__DOT__byte_controller__DOT__core_cmd))
					        ? 0
					        : 0x2000))
				    : ((2 & (IData)(vlTOPp->v__DOT__byte_controller__DOT__core_cmd))
				        ? ((1 & (IData)(vlTOPp->v__DOT__byte_controller__DOT__core_cmd))
					    ? 0 : 0x20)
				        : ((1 & (IData)(vlTOPp->v__DOT__byte_controller__DOT__core_cmd))
					    ? 1 : 0))));
			__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk = 0;
		    } else {
			if ((1 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) {
			    vlTOPp->__Vdly____Vcellinp__v__scl_padoen_o 
				= vlTOPp->__Vcellinp__v__scl_padoen_o;
			    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state = 2;
			    __Vdly____Vcellinp__v__sda_padoen_o = 1;
			    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk = 0;
			} else {
			    if ((2 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) {
				__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state = 4;
				vlTOPp->__Vdly____Vcellinp__v__scl_padoen_o = 1;
				__Vdly____Vcellinp__v__sda_padoen_o = 1;
				__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk = 0;
			    } else {
				if ((4 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) {
				    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state = 8;
				    vlTOPp->__Vdly____Vcellinp__v__scl_padoen_o = 1;
				    __Vdly____Vcellinp__v__sda_padoen_o = 0;
				    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk = 0;
				} else {
				    if ((8 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) {
					__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state = 0x10;
					vlTOPp->__Vdly____Vcellinp__v__scl_padoen_o = 1;
					__Vdly____Vcellinp__v__sda_padoen_o = 0;
					__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk = 0;
				    } else {
					if ((0x10 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) {
					    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state = 0;
					    vlTOPp->v__DOT__byte_controller__DOT__core_ack = 1;
					    vlTOPp->__Vdly____Vcellinp__v__scl_padoen_o = 0;
					    __Vdly____Vcellinp__v__sda_padoen_o = 0;
					    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk = 0;
					} else {
					    if ((0x20 
						 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) {
						__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state = 0x40;
						vlTOPp->__Vdly____Vcellinp__v__scl_padoen_o = 0;
						__Vdly____Vcellinp__v__sda_padoen_o = 0;
						__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk = 0;
					    } else {
						__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state = 0x80;
						vlTOPp->__Vdly____Vcellinp__v__scl_padoen_o = 1;
						__Vdly____Vcellinp__v__sda_padoen_o = 0;
						__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk = 0;
					    }
					}
				    }
				}
			    }
			}
		    }
		} else {
		    if (((((((((0x80 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state) 
			       | (0x100 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) 
			      | (0x200 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) 
			     | (0x400 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) 
			    | (0x800 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) 
			   | (0x1000 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) 
			  | (0x2000 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) 
			 | (0x4000 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state))) {
			if ((0x80 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) {
			    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state = 0x100;
			    vlTOPp->__Vdly____Vcellinp__v__scl_padoen_o = 1;
			    __Vdly____Vcellinp__v__sda_padoen_o = 0;
			    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk = 0;
			} else {
			    if ((0x100 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) {
				__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state = 0;
				vlTOPp->v__DOT__byte_controller__DOT__core_ack = 1;
				vlTOPp->__Vdly____Vcellinp__v__scl_padoen_o = 1;
				__Vdly____Vcellinp__v__sda_padoen_o = 1;
				__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk = 0;
			    } else {
				if ((0x200 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) {
				    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state = 0x400;
				    vlTOPp->__Vdly____Vcellinp__v__scl_padoen_o = 0;
				    __Vdly____Vcellinp__v__sda_padoen_o = 1;
				    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk = 0;
				} else {
				    if ((0x400 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) {
					__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state = 0x800;
					vlTOPp->__Vdly____Vcellinp__v__scl_padoen_o = 1;
					__Vdly____Vcellinp__v__sda_padoen_o = 1;
					__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk = 0;
				    } else {
					if ((0x800 
					     == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) {
					    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state = 0x1000;
					    vlTOPp->__Vdly____Vcellinp__v__scl_padoen_o = 1;
					    __Vdly____Vcellinp__v__sda_padoen_o = 1;
					    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk = 0;
					} else {
					    if ((0x1000 
						 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) {
						__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state = 0;
						vlTOPp->v__DOT__byte_controller__DOT__core_ack = 1;
						vlTOPp->__Vdly____Vcellinp__v__scl_padoen_o = 0;
						__Vdly____Vcellinp__v__sda_padoen_o = 1;
						__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk = 0;
					    } else {
						if (
						    (0x2000 
						     == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) {
						    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state = 0x4000;
						    vlTOPp->__Vdly____Vcellinp__v__scl_padoen_o = 0;
						    __Vdly____Vcellinp__v__sda_padoen_o 
							= vlTOPp->v__DOT__byte_controller__DOT__core_txd;
						    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk = 0;
						} else {
						    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state = 0x8000;
						    vlTOPp->__Vdly____Vcellinp__v__scl_padoen_o = 1;
						    __Vdly____Vcellinp__v__sda_padoen_o 
							= vlTOPp->v__DOT__byte_controller__DOT__core_txd;
						    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk = 0;
						}
					    }
					}
				    }
				}
			    }
			}
		    } else {
			if ((0x8000 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) {
			    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state = 0x10000;
			    vlTOPp->__Vdly____Vcellinp__v__scl_padoen_o = 1;
			    __Vdly____Vcellinp__v__sda_padoen_o 
				= vlTOPp->v__DOT__byte_controller__DOT__core_txd;
			    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk = 1;
			} else {
			    if ((0x10000 == vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state)) {
				__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state = 0;
				vlTOPp->v__DOT__byte_controller__DOT__core_ack = 1;
				vlTOPp->__Vdly____Vcellinp__v__scl_padoen_o = 0;
				__Vdly____Vcellinp__v__sda_padoen_o 
				    = vlTOPp->v__DOT__byte_controller__DOT__core_txd;
				__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk = 0;
			    }
			}
		    }
		}
	    }
	}
    } else {
	__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state = 0;
	vlTOPp->v__DOT__byte_controller__DOT__core_ack = 0;
	vlTOPp->__Vdly____Vcellinp__v__scl_padoen_o = 1;
	__Vdly____Vcellinp__v__sda_padoen_o = 1;
	__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk = 0;
    }
    vlTOPp->v__DOT__done = __Vdly__v__DOT__done;
    vlTOPp->v__DOT__byte_controller__DOT__core_txd 
	= __Vdly__v__DOT__byte_controller__DOT__core_txd;
    // ALWAYS at i2c_master_bit_ctrl.v:350
    vlTOPp->v__DOT__i2c_al = ((IData)(vlTOPp->__Vcellinp__v__arst_i) 
			      & ((~ (IData)(vlTOPp->__Vcellinp__v__wb_rst_i)) 
				 & ((((IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk) 
				      & (~ (IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sSDA))) 
				     & (IData)(vlTOPp->__Vcellinp__v__sda_padoen_o)) 
				    | (((0 != vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state) 
					& (IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sto_condition)) 
				       & (~ (IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__cmd_stop))))));
    vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk 
	= __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sda_chk;
    vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__c_state 
	= __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__c_state;
    vlTOPp->__Vcellinp__v__sda_padoen_o = __Vdly____Vcellinp__v__sda_padoen_o;
    VL_ASSIGN_SII(1,vlTOPp->sda_padoen_o, vlTOPp->__Vcellinp__v__sda_padoen_o);
    // ALWAYS at i2c_master_bit_ctrl.v:312
    if (vlTOPp->__Vcellinp__v__arst_i) {
	if (vlTOPp->__Vcellinp__v__wb_rst_i) {
	    vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sta_condition = 0;
	    vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sto_condition = 0;
	} else {
	    vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sta_condition 
		= (((~ (IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sSDA)) 
		    & (IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__dSDA)) 
		   & (IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sSCL));
	    vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sto_condition 
		= (((IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sSDA) 
		    & (~ (IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__dSDA))) 
		   & (IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sSCL));
	}
    } else {
	vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sta_condition = 0;
	vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sto_condition = 0;
    }
    // ALWAYS at i2c_master_bit_ctrl.v:342
    if (vlTOPp->__Vcellinp__v__arst_i) {
	if (vlTOPp->__Vcellinp__v__wb_rst_i) {
	    vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__cmd_stop = 0;
	} else {
	    if (vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__clk_en) {
		vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__cmd_stop 
		    = (2 == (IData)(vlTOPp->v__DOT__byte_controller__DOT__core_cmd));
	    }
	}
    } else {
	vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__cmd_stop = 0;
    }
    vlTOPp->v__DOT__byte_controller__DOT__core_cmd 
	= __Vdly__v__DOT__byte_controller__DOT__core_cmd;
    // ALWAYS at i2c_master_bit_ctrl.v:208
    if (vlTOPp->__Vcellinp__v__arst_i) {
	if ((1 & ((((IData)(vlTOPp->__Vcellinp__v__wb_rst_i) 
		    | (~ (IData)((0 != (IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__cnt))))) 
		   | (~ ((IData)(vlTOPp->v__DOT__ctr) 
			 >> 7))) | (((IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__dSCL) 
				     & (~ (IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sSCL))) 
				    & (IData)(vlTOPp->__Vcellinp__v__scl_padoen_o))))) {
	    __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__cnt 
		= vlTOPp->v__DOT__prer;
	    vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__clk_en = 1;
	} else {
	    if (vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__slave_wait) {
		__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__cnt 
		    = vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__cnt;
		vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__clk_en = 0;
	    } else {
		__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__cnt 
		    = (0xffff & ((IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__cnt) 
				 - (IData)(1)));
		vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__clk_en = 0;
	    }
	}
    } else {
	__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__cnt = 0;
	vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__clk_en = 1;
    }
    vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__cnt 
	= __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__cnt;
    vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__slave_wait 
	= __Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__slave_wait;
    // ALWAYS at i2c_master_top.v:177
    if (vlTOPp->__Vcellinp__v__arst_i) {
	if (vlTOPp->__Vcellinp__v__wb_rst_i) {
	    vlTOPp->v__DOT__prer = 0xffff;
	    vlTOPp->v__DOT__ctr = 0;
	    vlTOPp->v__DOT__txr = 0;
	} else {
	    if (vlTOPp->v__DOT__wb_wacc) {
		if ((1 & (~ ((IData)(vlTOPp->__Vcellinp__v__wb_adr_i) 
			     >> 2)))) {
		    if ((2 & (IData)(vlTOPp->__Vcellinp__v__wb_adr_i))) {
			if ((1 & (IData)(vlTOPp->__Vcellinp__v__wb_adr_i))) {
			    vlTOPp->v__DOT__txr = vlTOPp->__Vcellinp__v__wb_dat_i;
			} else {
			    vlTOPp->v__DOT__ctr = vlTOPp->__Vcellinp__v__wb_dat_i;
			}
		    } else {
			vlTOPp->v__DOT__prer = ((1 
						 & (IData)(vlTOPp->__Vcellinp__v__wb_adr_i))
						 ? 
						((0xff 
						  & (IData)(vlTOPp->v__DOT__prer)) 
						 | ((IData)(vlTOPp->__Vcellinp__v__wb_dat_i) 
						    << 8))
						 : 
						((0xff00 
						  & (IData)(vlTOPp->v__DOT__prer)) 
						 | (IData)(vlTOPp->__Vcellinp__v__wb_dat_i)));
		    }
		}
	    }
	}
    } else {
	vlTOPp->v__DOT__prer = 0xffff;
	vlTOPp->v__DOT__ctr = 0;
	vlTOPp->v__DOT__txr = 0;
    }
}

void Vi2c_master_top::_combo__TOP__5(Vi2c_master_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vi2c_master_top::_combo__TOP__5\n"); );
    Vi2c_master_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__wb_cyc_i, vlTOPp->wb_cyc_i);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__wb_stb_i, vlTOPp->wb_stb_i);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__scl_pad_i, vlTOPp->scl_pad_i);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__sda_pad_i, vlTOPp->sda_pad_i);
    VL_ASSIGN_ISI(8,vlTOPp->__Vcellinp__v__wb_dat_i, vlTOPp->wb_dat_i);
    VL_ASSIGN_ISI(3,vlTOPp->__Vcellinp__v__wb_adr_i, vlTOPp->wb_adr_i);
    vlTOPp->v__DOT__wb_wacc = ((IData)(vlTOPp->__Vcellinp__v__wb_we_i) 
			       & (IData)(vlTOPp->__Vcellinp__v__wb_ack_o));
}

void Vi2c_master_top::_settle__TOP__6(Vi2c_master_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vi2c_master_top::_settle__TOP__6\n"); );
    Vi2c_master_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__wb_cyc_i, vlTOPp->wb_cyc_i);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__wb_stb_i, vlTOPp->wb_stb_i);
    VL_ASSIGN_SII(1,vlTOPp->wb_ack_o, vlTOPp->__Vcellinp__v__wb_ack_o);
    VL_ASSIGN_SII(8,vlTOPp->wb_dat_o, vlTOPp->__Vcellinp__v__wb_dat_o);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__scl_pad_i, vlTOPp->scl_pad_i);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__sda_pad_i, vlTOPp->sda_pad_i);
    VL_ASSIGN_SII(1,vlTOPp->wb_inta_o, vlTOPp->__Vcellinp__v__wb_inta_o);
    vlTOPp->v__DOT__sr = ((0xfc & (IData)(vlTOPp->v__DOT__sr)) 
			  | (((IData)(vlTOPp->v__DOT__tip) 
			      << 1) | (IData)(vlTOPp->v__DOT__irq_flag)));
    vlTOPp->v__DOT__sr = ((3 & (IData)(vlTOPp->v__DOT__sr)) 
			  | (((IData)(vlTOPp->v__DOT__rxack) 
			      << 7) | (((IData)(vlTOPp->v__DOT__i2c_busy) 
					<< 6) | ((IData)(vlTOPp->v__DOT__al) 
						 << 5))));
    VL_ASSIGN_SII(1,vlTOPp->sda_padoen_o, vlTOPp->__Vcellinp__v__sda_padoen_o);
    VL_ASSIGN_ISI(8,vlTOPp->__Vcellinp__v__wb_dat_i, vlTOPp->wb_dat_i);
    VL_ASSIGN_ISI(3,vlTOPp->__Vcellinp__v__wb_adr_i, vlTOPp->wb_adr_i);
    vlTOPp->v__DOT__wb_wacc = ((IData)(vlTOPp->__Vcellinp__v__wb_we_i) 
			       & (IData)(vlTOPp->__Vcellinp__v__wb_ack_o));
}

void Vi2c_master_top::_sequent__TOP__7(Vi2c_master_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vi2c_master_top::_sequent__TOP__7\n"); );
    Vi2c_master_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at i2c_master_bit_ctrl.v:193
    vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__dscl_oen 
	= vlTOPp->__Vcellinp__v__scl_padoen_o;
    // ALWAYS at i2c_master_bit_ctrl.v:360
    if (((IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sSCL) 
	 & (~ (IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__dSCL)))) {
	vlTOPp->v__DOT__byte_controller__DOT__core_rxd 
	    = vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sSDA;
    }
}

void Vi2c_master_top::_sequent__TOP__8(Vi2c_master_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vi2c_master_top::_sequent__TOP__8\n"); );
    Vi2c_master_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vcellinp__v__scl_padoen_o = vlTOPp->__Vdly____Vcellinp__v__scl_padoen_o;
    VL_ASSIGN_SII(1,vlTOPp->scl_padoen_o, vlTOPp->__Vcellinp__v__scl_padoen_o);
    // ALWAYS at i2c_master_bit_ctrl.v:282
    if (vlTOPp->__Vcellinp__v__arst_i) {
	if (vlTOPp->__Vcellinp__v__wb_rst_i) {
	    vlTOPp->__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sSCL = 1;
	    vlTOPp->__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sSDA = 1;
	    vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__dSCL = 1;
	    vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__dSDA = 1;
	} else {
	    vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__dSCL 
		= vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sSCL;
	    vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__dSDA 
		= vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sSDA;
	    vlTOPp->__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sSCL 
		= (1 & (((3 == (3 & ((IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__fSCL) 
				     >> 1))) | (3 == 
						(3 
						 & (IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__fSCL)))) 
			| (((IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__fSCL) 
			    >> 2) & (IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__fSCL))));
	    vlTOPp->__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sSDA 
		= (1 & (((3 == (3 & ((IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__fSDA) 
				     >> 1))) | (3 == 
						(3 
						 & (IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__fSDA)))) 
			| (((IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__fSDA) 
			    >> 2) & (IData)(vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__fSDA))));
	}
    } else {
	vlTOPp->__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sSCL = 1;
	vlTOPp->__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sSDA = 1;
	vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__dSCL = 1;
	vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__dSDA = 1;
    }
    vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sSCL 
	= vlTOPp->__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sSCL;
    vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__sSDA 
	= vlTOPp->__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__sSDA;
    vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__fSCL 
	= vlTOPp->__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__fSCL;
    vlTOPp->v__DOT__byte_controller__DOT__bit_controller__DOT__fSDA 
	= vlTOPp->__Vdly__v__DOT__byte_controller__DOT__bit_controller__DOT__fSDA;
}

void Vi2c_master_top::_settle__TOP__9(Vi2c_master_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vi2c_master_top::_settle__TOP__9\n"); );
    Vi2c_master_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SII(1,vlTOPp->scl_padoen_o, vlTOPp->__Vcellinp__v__scl_padoen_o);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__arst_i, vlTOPp->arst_i);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__wb_rst_i, vlTOPp->wb_rst_i);
}

void Vi2c_master_top::_combo__TOP__10(Vi2c_master_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vi2c_master_top::_combo__TOP__10\n"); );
    Vi2c_master_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__arst_i, vlTOPp->arst_i);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__wb_rst_i, vlTOPp->wb_rst_i);
}

void Vi2c_master_top::_eval(Vi2c_master_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vi2c_master_top::_eval\n"); );
    Vi2c_master_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__2(vlSymsp);
    if (((IData)(vlTOPp->__Vcellinp__v__wb_clk_i) & 
	 (~ (IData)(vlTOPp->__Vclklast__TOP____Vcellinp__v__wb_clk_i)))) {
	vlTOPp->_sequent__TOP__3(vlSymsp);
    }
    if ((((~ (IData)(vlTOPp->__VinpClk__TOP____Vcellinp__v__arst_i)) 
	  & (IData)(vlTOPp->__Vclklast__TOP____VinpClk__TOP____Vcellinp__v__arst_i)) 
	 | ((IData)(vlTOPp->__Vcellinp__v__wb_clk_i) 
	    & (~ (IData)(vlTOPp->__Vclklast__TOP____Vcellinp__v__wb_clk_i))))) {
	vlTOPp->_sequent__TOP__4(vlSymsp);
    }
    vlTOPp->_combo__TOP__5(vlSymsp);
    if (((IData)(vlTOPp->__Vcellinp__v__wb_clk_i) & 
	 (~ (IData)(vlTOPp->__Vclklast__TOP____Vcellinp__v__wb_clk_i)))) {
	vlTOPp->_sequent__TOP__7(vlSymsp);
    }
    if ((((~ (IData)(vlTOPp->__VinpClk__TOP____Vcellinp__v__arst_i)) 
	  & (IData)(vlTOPp->__Vclklast__TOP____VinpClk__TOP____Vcellinp__v__arst_i)) 
	 | ((IData)(vlTOPp->__Vcellinp__v__wb_clk_i) 
	    & (~ (IData)(vlTOPp->__Vclklast__TOP____Vcellinp__v__wb_clk_i))))) {
	vlTOPp->_sequent__TOP__8(vlSymsp);
    }
    vlTOPp->_combo__TOP__10(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP____Vcellinp__v__wb_clk_i 
	= vlTOPp->__Vcellinp__v__wb_clk_i;
    vlTOPp->__Vclklast__TOP____VinpClk__TOP____Vcellinp__v__arst_i 
	= vlTOPp->__VinpClk__TOP____Vcellinp__v__arst_i;
    vlTOPp->__VinpClk__TOP____Vcellinp__v__arst_i = vlTOPp->__Vcellinp__v__arst_i;
}

void Vi2c_master_top::_eval_initial(Vi2c_master_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vi2c_master_top::_eval_initial\n"); );
    Vi2c_master_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vi2c_master_top::final() {
    VL_DEBUG_IF(VL_PRINTF("    Vi2c_master_top::final\n"); );
    // Variables
    Vi2c_master_top__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vi2c_master_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vi2c_master_top::_eval_settle(Vi2c_master_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vi2c_master_top::_eval_settle\n"); );
    Vi2c_master_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__1(vlSymsp);
    vlTOPp->_settle__TOP__6(vlSymsp);
    vlTOPp->_settle__TOP__9(vlSymsp);
}

IData Vi2c_master_top::_change_request(Vi2c_master_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    Vi2c_master_top::_change_request\n"); );
    Vi2c_master_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    IData __req = false;  // Logically a bool
    __req |= ((vlTOPp->__Vcellinp__v__arst_i ^ vlTOPp->__Vchglast__TOP____Vcellinp__v__arst_i));
    VL_DEBUG_IF( if(__req && ((vlTOPp->__Vcellinp__v__arst_i ^ vlTOPp->__Vchglast__TOP____Vcellinp__v__arst_i))) VL_PRINTF("	CHANGE: i2c_master_top.v:93: __Vcellinp__v__arst_i\n"); );
    // Final
    vlTOPp->__Vchglast__TOP____Vcellinp__v__arst_i 
	= vlTOPp->__Vcellinp__v__arst_i;
    return __req;
}
