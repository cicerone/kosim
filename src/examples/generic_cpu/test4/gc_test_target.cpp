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
        uint32_t mem[4];
        mem[0] = mp_memory_map->Read(0);
        mem[1] = mp_memory_map->Read(1);
        mem[2] = mp_memory_map->Read(2);
        mem[3] = mp_memory_map->Read(3);

        if (m_id == 0)
        {
            if (mem[1] != 0) 
            {
                if ((mem[0] == 1) && (mem[1] == 2)) {
                    cout <<__PRETTY_FUNCTION__  << ": time = " << sc_time_stamp() << "target_id = " << m_id << " PASS" << endl;
                    mem[0] = 0;
                    mem[1] = 0;
                } 
                else {
                    printf("%s target_id(%d) ERROR.\n", __PRETTY_FUNCTION__, m_id);
                    exit(1);
                }
                mv_irq[0]->write(m_id);
            } 
            
        }
        else if (m_id == 2)
        {
            if (mem[1] != 0) 
            {
                if ((mem[0] == 7) && (mem[1] == 8)) {
                    cout <<__PRETTY_FUNCTION__  << ": time = " << sc_time_stamp() << "target_id = " << m_id << " PASS" << endl;
                    mem[0] = 0;
                    mem[1] = 0;
                } 
                else {
                    printf("%s target_id(%d) ERROR.\n", __PRETTY_FUNCTION__, m_id);
                    exit(1);                    
                }
                mv_irq[0]->write(m_id);
            }
            
        }
        else if (m_id == 1)
        {
            if (mem[1] != 0) 
            {
                if ((mem[0] == 3) && (mem[1] == 4)) {
                    cout <<__PRETTY_FUNCTION__  << ": time = " << sc_time_stamp() << "target_id = " << m_id << " PASS_CPU0" << endl;
                    mem[0] = 0;
                    mem[1] = 0;
                } 
                else {
                    printf("%s target_id(%d) ERROR_CPU1. Exp(3, 4) got(%d, %d)\n", __PRETTY_FUNCTION__, m_id, mem[0], mem[1]);
                    exit(1);                    
                }
                mv_irq[0]->write(m_id);
            }
            
            
            if (mem[3] != 0) 
            {
                if ((mem[2] == 5) && (mem[3] == 6)) {
                    cout <<__PRETTY_FUNCTION__  << ": time = " << sc_time_stamp() << "target_id = " << m_id << " PASS_CPU1" << endl;
                    mem[2] = 0;
                    mem[3] = 0;
                } 
                else {
                    printf("%s target_id(%d) ERROR_CPU2. Exp(5, 6) got(%d, %d)\n", __PRETTY_FUNCTION__, m_id, mem[2], mem[3]);
                    exit(1);                    
                }
                mv_irq[1]->write(m_id);
            }
        }
        switch (m_id)
        {
            case 0: wait(5, SC_NS);
            break;
            case 1: wait(9, SC_NS);
            break;
            case 2: wait(7, SC_NS);
            break;
        }
        
    }
}

