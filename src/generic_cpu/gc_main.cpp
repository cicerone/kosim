/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosym@kotys.biz 
===============================================================================================*/

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "generic_cpu.h"
#include "gc_memory.h"
#include "gc_router.h"


/////////////////////////////////////////////////////////////////////////////////////////////////
// Top is the class that creates and binds the objects together.
/////////////////////////////////////////////////////////////////////////////////////////////////
class Top : public sc_module
{

public:
    SC_HAS_PROCESS(Top);
    
    Top(sc_module_name name_) : sc_module(name_)
    {
        // Instantiate components
        p_gcpu   = new GenericCPU("gen_cpu");
        p_router = new GCRouter<4>("router");
        
        for (int i = 0; i < 4; i++)
        {
          char txt[20];
          sprintf(txt, "p_memory_%d", i);
          p_memory[i] = new GCMemory(txt);
        }
        
        // Bind sockets
        p_gcpu->socket.bind( p_router->m_target_socket );
        for (int i = 0; i < 4; i++)
            p_router->mp_initiator_socket[i]->bind( p_memory[i]->socket );
   }
  
private:
   GenericCPU* p_gcpu;
   GCRouter<4>* p_router;
   GCMemory*    p_memory[4];
};
/////////////////////////////////////////////////////////////////////////////////////////////////
// Entry point if the program is run as an executable
// IN:  argc, argv as the C "main" function
// OUT: 
// RET: 
int sc_main(int argc, char* argv[])
{
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
    Top top("top");
    sc_start();
}

