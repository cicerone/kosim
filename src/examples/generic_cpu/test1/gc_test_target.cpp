/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#include "gc_test_target.h"
#include "gen_from_sysrdl.h"

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
    while(1)
    {
        wait(m_io_event);
        fprintf(stdout, "%s_(%d)\n", __PRETTY_FUNCTION__, m_id);
        uint32_t mem[3];
        mem[0] = mp_memory_map->Read(0);
        mem[1] = mp_memory_map->Read(1);
        mem[2] = mp_memory_map->Read(2);
       
        mem[2] = mem[0] + mem[1];

        mp_memory_map->Write(2, mem[2]);
        if (m_id == MEM2) {
            uint32_t data = 0;
            data = mp_memory_map->Read(M2_REG0, M2_FIELD1);  
            printf("M2_FIELD4(0x%x)\n", data);
            mp_memory_map->Write(M2_REG1, M2_FIELD4, 0x77);  
        }
        wait(10, SC_NS);
        mv_irq[0]->write(m_id);
    }
}

