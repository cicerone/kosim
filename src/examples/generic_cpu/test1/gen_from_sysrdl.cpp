/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#define SC_INCLUDE_DYNAMIC_PROCESSES

//#include "generic_cpu.h"
//#include "gc_memory.h"
//#include "gc_router.h"
//#include "gc_interrupt_controller.h"
#include "gen_from_sysrdl.h"
#include "memory_map_builder.h"
#include "memory_map.h"


/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void BuildMemoryMap4Mem0()
{
    MemoryMapBuilder* p_mm_builder = MemoryMapBuilder::GetInstance();
    MemoryMap* p_mm0 = new MemoryMap(MEM0, "MEMORY_MAP_0", M0_MEMORY_SPACE_OFFSET);
    p_mm0->SetSpaceSize(M0_NUMBER_REGS, M0_MEMORY_SIZE);
    p_mm0->SetRegisterFieldsSize(M0_NUMBER_FIELDS);
    p_mm_builder->AddBlock(p_mm0);
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void BuildMemoryMap4Mem1()
{
    MemoryMapBuilder* p_mm_builder = MemoryMapBuilder::GetInstance();
    MemoryMap* p_mm1 = new MemoryMap(MEM1, "MEMORY_MAP_1", M1_MEMORY_SPACE_OFFSET);
    p_mm1->SetSpaceSize(M1_NUMBER_REGS, M1_MEMORY_SIZE);
    p_mm1->SetRegisterFieldsSize(M1_NUMBER_FIELDS);
    p_mm_builder->AddBlock(p_mm1);
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void BuildMemoryMap4Mem2()
{
    MemoryMapBuilder* p_mm_builder = MemoryMapBuilder::GetInstance();
    MemoryMap* p_mm2 = new MemoryMap(MEM2, "MEMORY_MAP_2", M2_MEMORY_SPACE_OFFSET);
    p_mm2->SetSpaceSize(M2_NUMBER_REGS, M2_MEMORY_SIZE);
    p_mm2->SetRegisterFieldsSize(M2_NUMBER_FIELDS);
    p_mm2->set_register_field(M2_FIELD0, 15,  7);
    p_mm2->set_register_field(M2_FIELD1,  6,  1);
    p_mm2->set_register_field(M2_FIELD2,  0,  0);
    p_mm2->set_register_field(M2_FIELD3, 31, 10);
    p_mm2->set_register_field(M2_FIELD4,  9,  0);
    p_mm_builder->AddBlock(p_mm2);
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void BuildMemoryMap4Mem3()
{
    MemoryMapBuilder* p_mm_builder = MemoryMapBuilder::GetInstance();
    MemoryMap* p_mm3 = new MemoryMap(MEM3, "MEMORY_MAP_3", M3_MEMORY_SPACE_OFFSET);
    p_mm3->SetSpaceSize(M3_NUMBER_REGS, M3_MEMORY_SIZE);
    p_mm3->SetRegisterFieldsSize(M3_NUMBER_FIELDS);
    p_mm_builder->AddBlock(p_mm3);
}

