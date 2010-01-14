/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "generic_cpu.h"
#include "gc_memory.h"
#include "gc_router.h"
#include "gc_interrupt_controller.h"
#include "memory_map_builder.h"
#include "memory_map.h"


enum BLOCK_ID
{
    MEM0 = 0,
    MEM1    ,
    MEM2    ,
    MEM3    ,
    NUMBER_PERIPHERALS,
};

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
//   static const uint32_t NUMBER_PERIPHERALS = 4;
   GenericCPU* p_gcpu;
   GCRouter<NUMBER_PERIPHERALS>* p_router;
   GCMemory*    p_memory[NUMBER_PERIPHERALS];
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
     p_router     = new GCRouter<NUMBER_PERIPHERALS>("router");
     p_irq_ctrler = new GCInterruptController<NUMBER_PERIPHERALS>("interrupt_controller");
     
     for (int i = 0; i < NUMBER_PERIPHERALS; i++)
     {
       char txt[20];
       sprintf(txt, "p_memory_%d", i);
       p_memory[i] = new GCMemory(txt, i);  
     }
     
     // Bind sockets
     p_gcpu->socket.bind( p_router->m_target_socket );
     for (int i = 0; i < NUMBER_PERIPHERALS; i++)
         p_router->mp_initiator_socket[i]->bind( p_memory[i]->socket );
     // Bind interrupts
     p_gcpu->m_irq(cpu_irq);
     p_irq_ctrler->m_irq_out(cpu_irq);
     for (int i = 0; i < NUMBER_PERIPHERALS; i++)
     {
         p_irq_ctrler->m_irq_in[i](peripheral_irq[i]);
         p_memory[i]->m_irq(peripheral_irq[i]);
     }

}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void Top::BuildMemoryMap()
{
    MemoryMapBuilder* p_mm_builder = MemoryMapBuilder::GetInstance();

    MemoryMap* p_mm0 = new MemoryMap(MEM0, "MEMORY_MAP_0", 0x000);
    MemoryMap* p_mm1 = new MemoryMap(MEM1, "MEMORY_MAP_1", 0x100);
    MemoryMap* p_mm2 = new MemoryMap(MEM2, "MEMORY_MAP_2", 0x200);
    MemoryMap* p_mm3 = new MemoryMap(MEM3, "MEMORY_MAP_3", 0x300);

    p_mm0->SetSpaceSize(0, 64);
    p_mm1->SetSpaceSize(0, 64);
    p_mm2->SetSpaceSize(0, 64);
    p_mm3->SetSpaceSize(0, 64);
    
    p_mm0->SetRegisterFieldsSize(0);
    p_mm1->SetRegisterFieldsSize(0);
    p_mm2->SetRegisterFieldsSize(0);
    p_mm3->SetRegisterFieldsSize(0);

    p_mm_builder->AddBlock(p_mm0);
    p_mm_builder->AddBlock(p_mm1);
    p_mm_builder->AddBlock(p_mm2);
    p_mm_builder->AddBlock(p_mm3);
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

