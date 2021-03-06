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
    SC_THREAD(STMain);
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void GCTestTarget::STMain()
{

    for (uint32_t i = 0; i < ProgramOptions::GetInstance()->get_memory_size(); i++)
    {
        mp_memory_map->Write(i, 7);
    }
    
    uint32_t k = 0;
    
    while(1)
    {
        wait(m_io_event);
//        fprintf(stdout, "%s_(%d)\n", __PRETTY_FUNCTION__, m_id);
        for (uint32_t i = 0; i < ProgramOptions::GetInstance()->get_nr_ops_per_xfer(); i++)
        {
            uint32_t data =  mp_memory_map->Read(k);
            data *= 9;
            mp_memory_map->Write(k, data);
            k++;
            if (k > mp_memory_map->get_memory_size()) k = 0;
        }
//       uint32_t mem[3];
//       mem[0] = mp_memory_map->Read(0);
//       mem[1] = mp_memory_map->Read(1);
//       mem[2] = mp_memory_map->Read(2);
//      
//       mem[2] = mem[0] + mem[1];
//
//       mp_memory_map->Write(2, mem[2]);
        wait(10, SC_NS);
        mv_irq[0]->write(m_id);
    }
}

