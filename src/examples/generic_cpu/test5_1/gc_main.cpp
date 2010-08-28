/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

//#define SC_INCLUDE_DYNAMIC_PROCESSES defined in CMakeList.txt defined in CMakeList.txt

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sched.h>


#include "generic_cpu.h"
#include "gc_test_target.h"
#include "b_router.h"
#include "gc_interrupt_controller.h"
#include "memory_map_builder.h"
#include "memory_map.h"
#include "gen_from_sysrdl.h"
#include "program_options.h"

#include "target_adapter.h"


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
   GCTestTarget*    p_test_target[NUMBER_PERIPHERALS - 1]; // rcm IPC
   TargetAdapter*   p_target_adapter;                      // rcm IPC
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
     
     for (int i = 0; i < NUMBER_PERIPHERALS - 1; i++) // rcm IPC
     {
       char txt[20];
       sprintf(txt, "p_test_target_%d", i);
       p_test_target[i] = new GCTestTarget(txt, i);  
     }
     p_target_adapter = new TargetAdapter("target_adapter", 1); // the ID must match the ID of the replaced test_target
     
     // Bind sockets
     p_gcpu->socket.bind( *(p_router->mp_target_socket[0]) );
     for (int i = 0; i < NUMBER_PERIPHERALS - 1; i++)  // rcm IPC
         p_router->mp_initiator_socket[i]->bind( p_test_target[i]->socket );
         
     p_router->mp_initiator_socket[1]->bind( p_target_adapter->socket ); // rcm IPC    
     // Bind interrupts
     p_gcpu->m_irq(cpu_irq);
     p_irq_ctrler->m_irq_out(cpu_irq);
     for (int i = 0; i < NUMBER_PERIPHERALS; i++)
     {
         p_irq_ctrler->m_irq_in[i](peripheral_irq[i]);
//         (*p_test_target[i]->mv_irq[0])(peripheral_irq[i]); // rcm IPC
     }
     (*p_test_target[0]->mv_irq[0])(peripheral_irq[0]); // rcm IPC
     (*p_target_adapter->mv_irq[0])(peripheral_irq[1]); // rcm IPC
     

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

#define LAUNCH_CHILD_PROCESS

#ifdef LAUNCH_CHILD_PROCESS
    pid_t pid;
    {
        pid = fork();
        if (!pid)
        {
//            sched_yield(); // make sure taht the parrent starts first ???
            timespec req, rem;
            req.tv_sec = 0   ;
            req.tv_nsec = 90000000; // delay for 90 milisec so that the parent process has time to initialize common resources 
            nanosleep(&req, &rem); // ideally this should be replaced with some sync mechanism... 


            

//            char* const args[] = { "kosim_generic_cpu_test5_2", "--cfg",  "sim_accel.cfg", NULL };           
            char* const args[] = { "kosim_generic_cpu_test5_2", argv[1],  argv[2], NULL };           
            int ret = execv("../test5_2/kosim_generic_cpu_test5_2", args);
            if (ret == -1)
            {
                perror("execv");
                exit(EXIT_FAILURE);
            }
        }
        else if (pid > 0)
        {
            fprintf(stderr, "The parent of the pid(%d)\n", pid);
        }
        else if (pid == -1)
        {
            perror ("fork");
        }
    }
#endif

    Top top("top");
    sc_start();

#ifdef LAUNCH_CHILD_PROCESS
    // NOTE: with the current implementation this code is not reached. The child must be destroyed manually. 
    {
        if (pid > 0)
        {
             fprintf(stderr, "Terminate the child process - pid(%d).\n", pid);
             int ret = kill(pid, SIGKILL);
             if (ret) perror("kill");
        }
    }
#endif

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

