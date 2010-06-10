/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#include "gc_test_target.h"
#include "gen_from_sysrdl.h"
#include "program_options.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
GCTestTarget::GCTestTarget(sc_module_name name_, uint32_t id_, uint32_t no_irq_) : 
    GCTarget(name_, id_, no_irq_)
{
    SC_THREAD(TReadWrite);
    SC_THREAD(TProcess);
    
    
    for (uint32_t i = 0; i < ProgramOptions::GetInstance()->get_memory_size(); i++)
    {
        mp_memory_map->Write(i, i);
    }
    
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void GCTestTarget::TReadWrite()
{

    
    while(1)
    {
        wait(m_io_event);

        if (mp_memory_map->Read(0) != 0)
        {
            mp_memory_map->Write(0, 0);
            m_ev_process.notify(10, SC_NS);
            //m_ev_process.notify(SC_ZERO_TIME);
//       fprintf(stdout, "%s_(%d)\n", __PRETTY_FUNCTION__, m_id);
            
        }
    }
}

void GCTestTarget::TProcess()
{
    while(1)
    {
        wait(m_ev_process);
        
        uint32_t k = 0;

    
           for (uint32_t i = 0; i < ProgramOptions::GetInstance()->get_nr_ops_per_xfer(); i++)
            {
                uint32_t data =  mp_memory_map->Read(k);
                data *= 10;
                mp_memory_map->Write(k, data);
                if (m_id == 1) fprintf(stderr, "k(%d) i(%d) data(%d)\n", k, i, data);
                
                k++;
                if (k >= mp_memory_map->get_memory_size()) k = 0;
            
            }
            
        mv_irq[0]->write(m_id);
//            fprintf(stderr, "GENERRATE interrupts m_id(%d)\n", m_id);
    }
    
}


