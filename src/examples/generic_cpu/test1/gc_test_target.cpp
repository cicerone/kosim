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
GCTestTarget::GCTestTarget(sc_module_name name_, uint32_t id_) : 
    GCTarget(name_, id_)
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
        uint32_t mem[3];
        mp_memory_map->Read(0, &mem[0]);
        mp_memory_map->Read(4, &mem[1]);
        mp_memory_map->Read(8, &mem[2]);
       
        mem[2] = mem[0] + mem[1];

        mp_memory_map->Write(8, mem[2]);
        if (m_id == MEM2) {
            uint32_t data = 0;
            mp_memory_map->Read(M2_REG0, M2_FIELD1, &data);  
            printf("M2_FIELD4(0x%x)\n", data);
            mp_memory_map->Write(M2_REG1, M2_FIELD4, 0x77);  
        }
        wait(10, SC_NS);
        m_irq.write(m_id);
    }
}

