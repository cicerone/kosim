/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "generic_cpu.h"
#include "gc_test_target.h"
#include "b_router.h"
#include "gc_interrupt_controller.h"
#include "memory_map_builder.h"
#include "memory_map.h"
#include "gen_from_sysrdl.h"
#include "program_options.h"



/////////////////////////////////////////////////////////////////////////////////////////////////
// Top is the class that creates and binds the objects together.
/////////////////////////////////////////////////////////////////////////////////////////////////
class Top : public sc_module
{
public:
    SC_HAS_PROCESS(Top);
    
    Top(sc_module_name name_);
  
private:
   void BuildMemoryMap();
   GenericCPU* p_gcpu[NUMBER_CPUS];
   BRouter<NUMBER_CPUS, NUMBER_PERIPHERALS>* p_router;
   GCTestTarget*    p_test_target[NUMBER_PERIPHERALS];
   GCInterruptController<2>* p_irq_ctrler[NUMBER_CPUS];
   sc_fifo<uint32_t> cpu_irq[NUMBER_CPUS];
   sc_fifo<uint32_t> peripheral_irq0[2];
   sc_fifo<uint32_t> peripheral_irq1[2];

};
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
Top::Top(sc_module_name name_) : sc_module(name_)
{
     // Instantiate components
     BuildMemoryMap();

     for (int i = 0; i < NUMBER_CPUS; i++) 
     {
         char txt[20];
         sprintf(txt, "gen_cpu_%d", i);
         p_gcpu[i] = new GenericCPU(txt, i);
         sprintf(txt, "interrupt_controller_%d", i);
         p_irq_ctrler[i] = new GCInterruptController<2>(txt);
         
     }
     
     p_router        = new BRouter<NUMBER_CPUS, NUMBER_PERIPHERALS>("router");
          
     for (int i = 0; i < NUMBER_PERIPHERALS; i++)
     {
       char txt[20];
       sprintf(txt, "p_test_target_%d", i);
       if (i == 1) {
           p_test_target[i] = new GCTestTarget(txt, i, 2);  
       }
       else {
           p_test_target[i] = new GCTestTarget(txt, i, 1);  
       }
     }
     
     for (int i = 0; i < NUMBER_CPUS; i++) {
         p_gcpu[i]->socket.bind( *(p_router->mp_target_socket[i]) ); // Bind sockets
         p_gcpu[i]->m_irq(cpu_irq[i]);                               // Bind interrupts
         p_irq_ctrler[i]->m_irq_out(cpu_irq[i]);


     }
     
     for (int i = 0; i < NUMBER_PERIPHERALS; i++) {
         p_router->mp_initiator_socket[i]->bind( p_test_target[i]->socket );
     }
     
     // Bind interrupts
     p_irq_ctrler[0]->m_irq_in[0](peripheral_irq0[0]);
     p_irq_ctrler[0]->m_irq_in[1](peripheral_irq0[1]);
     p_irq_ctrler[1]->m_irq_in[0](peripheral_irq1[0]);
     p_irq_ctrler[1]->m_irq_in[1](peripheral_irq1[1]);

     (*p_test_target[0]->mv_irq[0])(peripheral_irq0[0]);
     (*p_test_target[1]->mv_irq[0])(peripheral_irq0[1]);
     (*p_test_target[1]->mv_irq[1])(peripheral_irq1[0]);
     (*p_test_target[2]->mv_irq[0])(peripheral_irq1[1]);
         
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void Top::BuildMemoryMap()
{
    BuildMemoryMap4Mem0();
    BuildMemoryMap4Mem1();
    BuildMemoryMap4Mem2();
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// Entry point if the program is run as an executable
// IN:  argc, argv as the C "main" function
// OUT: 
// RET: 
int sc_main(int argc, char* argv[])
{
    ProgramOptions::GetInstance(argc, argv); // if need to run the c++ executable, not the python variation
    Top top("top");
    sc_start();
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// Entry point if the program is loaded as a module to python  
// IN: 
// OUT: 
// RET: 
void run_sim()
{
    cout << "=======================================================" << endl;
    cout << ProgramOptions::GetInstance()->get_test_name() << endl;
    cout << "=======================================================" << endl;


    Top top("top");
    sc_start();
}

