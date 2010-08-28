/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

//#define SC_INCLUDE_DYNAMIC_PROCESSES defined in CMakeList.txt defined in CMakeList.txt

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
   GenericCPU* p_gcpu;
   BRouter<1, NUMBER_PERIPHERALS>* p_router;
   GCTestTarget*    p_test_target[NUMBER_PERIPHERALS];
   GCInterruptController<NUMBER_PERIPHERALS>* p_irq_ctrler;
   sc_fifo<uint32_t> cpu_irq;
   sc_fifo<uint32_t> peripheral_irq[NUMBER_PERIPHERALS];
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

     p_gcpu       = new GenericCPU("gen_cpu");
     p_router     = new BRouter<1, NUMBER_PERIPHERALS>("router");
     p_irq_ctrler = new GCInterruptController<NUMBER_PERIPHERALS>("interrupt_controller");
     
     for (int i = 0; i < NUMBER_PERIPHERALS; i++)
     {
       char txt[20];
       sprintf(txt, "p_test_target_%d", i);
       p_test_target[i] = new GCTestTarget(txt, i);  
     }
     
     // Bind sockets
     p_gcpu->socket.bind( *(p_router->mp_target_socket[0]) );
     for (int i = 0; i < NUMBER_PERIPHERALS; i++)
         p_router->mp_initiator_socket[i]->bind( p_test_target[i]->socket );
     // Bind interrupts
     p_gcpu->m_irq(cpu_irq);
     p_irq_ctrler->m_irq_out(cpu_irq);
     for (int i = 0; i < NUMBER_PERIPHERALS; i++)
     {
         p_irq_ctrler->m_irq_in[i](peripheral_irq[i]);
         (*p_test_target[i]->mv_irq[0])(peripheral_irq[i]);
     }

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
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// Entry point if the program is run as an executable
// IN:  argc, argv as the C "main" function
// OUT: 
// RET: 
int sc_main(int argc, char* argv[])
{
    ProgramOptions::GetInstance(argc, argv); // if need to run the c++ executable, not the python variation
    
    ProgramOptions::GetInstance()->Help(); // printf help and version

    cout << "=======================================================" << endl;
    cout << ProgramOptions::GetInstance()->get_test_name      () << endl;
    cout << "Transfer Size   = " << ProgramOptions::GetInstance()->get_transfer_size  () << endl;
    cout << "Memory Size     = " << ProgramOptions::GetInstance()->get_memory_size    () << endl;
    cout << "Nr Ops Per Xfer = " << ProgramOptions::GetInstance()->get_nr_ops_per_xfer() << endl;
    cout << "Nr Xfers        = " << ProgramOptions::GetInstance()->get_nr_xfers       () << endl;
//    cout << ProgramOptions::GetInstance()->get_cmd_line_arg1  () << endl;
    cout << "=======================================================" << endl;

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

    ProgramOptions::GetInstance()->Help(); // printf help and version

    Top top("top");
    sc_start();
}

