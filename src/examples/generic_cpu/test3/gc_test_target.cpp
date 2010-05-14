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
        if (m_id == MEM2) {
          uint32_t reg_val = mp_memory_map->ReadHwRDL(M2_REG1);
          fprintf(stderr, "=== ReadHwRDL FIELD8 must be 0x0 reg_val(0x%08x)\n", reg_val);
          mp_memory_map->WriteHwRDL(M2_REG1, 0xaa558811);
          mp_memory_map->WriteHwRDL(M2_REG1, M2_FIELD10, 0x7);
          uint32_t field_val = mp_memory_map->ReadHwRDL(M2_REG1, M2_FIELD10);
          fprintf(stderr, "=== ReadHwRDL FIELD10 must be 0x7 field_val(0x%01x)\n", field_val);
          mp_memory_map->WriteHwRDL(M2_REG1, M2_FIELD11, 0xa);
          field_val = mp_memory_map->Read(M2_REG1, M2_FIELD11);
          reg_val = mp_memory_map->ReadHwRDL(M2_REG1);
          fprintf(stderr, "=== Read FIELD11 must be 0x2 field_val(0x%01x) reg_val(0x%08x)\n", field_val, reg_val);
          mp_memory_map->WriteHwRDL(M2_REG1, M2_FIELD12, 0x3);
          field_val = mp_memory_map->Read(M2_REG1, M2_FIELD12);
          reg_val = mp_memory_map->ReadHwRDL(M2_REG1);
          fprintf(stderr, "=== Read FIELD12 must be 0x2 field_val(0x%01x) reg_val(0x%08x)\n", field_val, reg_val);

           // mp_memory_map->Write(M2_REG1, M2_FIELD4, 0xaa558811); // update continuosly this field to test is_sw_write_one_to_clear  
        }
        switch(m_id)
        {
            case MEM0: wait(10, SC_NS);
            break;
            case MEM1: wait(11, SC_NS);
            break;
            case MEM2: wait(12, SC_NS);
            break;
            case MEM3: wait(13, SC_NS);
            break;
            default: fprintf(stderr, "ERROR! UNKNOWN peripheral ID!\n"); exit(1);
        }
        mv_irq[0]->write(m_id);
    }
}

