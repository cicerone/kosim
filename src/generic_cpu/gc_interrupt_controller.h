/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_GC_GC_INTERRUPT_CONTROLLER_H
#define KOSIM_GC_GC_INTERRUPT_CONTROLLER_H

#include <stdint.h>
#include "systemc.h"


/////////////////////////////////////////////////////////////////////////////////////////////////
// GCInterruptController implemtents a many peripherals to one CPU, first come first served priority 
// controller
/////////////////////////////////////////////////////////////////////////////////////////////////

template<uint32_t N_PERIPHERALS>
class GCInterruptController: sc_module
{
public:
  sc_fifo_out<uint32_t> m_irq_out;
  sc_fifo_in <uint32_t> m_irq_in[N_PERIPHERALS] ;

  SC_HAS_PROCESS(GCInterruptController);
  GCInterruptController(sc_module_name name_);
  ~GCInterruptController();

private:

  void ThreadIRQ(); 

};
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
template <uint32_t N_PERIPHERALS>
GCInterruptController<N_PERIPHERALS>::GCInterruptController(sc_module_name name_) : 
    sc_module(name_)
{
    SC_THREAD(ThreadIRQ);
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
template <uint32_t N_PERIPHERALS>
GCInterruptController<N_PERIPHERALS>::~GCInterruptController() 
{
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// This thread is polling the input ports to see if an interrupt was generated.
// NOTE: this implementation must be replaced with a blocking one.
// IN: 
// OUT: 
// RET: 
template<uint32_t N_PERIPHERALS>
void GCInterruptController<N_PERIPHERALS>::ThreadIRQ()
{
    while(1)
    {
        for (uint32_t i = 0; i < N_PERIPHERALS; i++) {
            if (m_irq_in[i].num_available() != 0) m_irq_out.write(m_irq_in[i].read());
        }
        wait(1, SC_NS);
    }
}

#endif // KOSIM_GC_GC_INTERRUPT_CONTROLLER_H

