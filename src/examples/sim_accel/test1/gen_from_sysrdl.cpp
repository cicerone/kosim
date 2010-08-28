/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

//#define SC_INCLUDE_DYNAMIC_PROCESSES defined in CMakeList.txt defined in CMakeList.txt

#include "gen_from_sysrdl.h"
#include "memory_map_builder.h"
#include "memory_map.h"
#include "program_options.h"


/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void BuildMemoryMap4Mem0()
{
    uint64_t m0_memory_space_offset = 0;
    uint64_t m0_memory_size = ProgramOptions::GetInstance()->get_memory_size();
    MemoryMapBuilder* p_mm_builder = MemoryMapBuilder::GetInstance();
    MemoryMap* p_mm0 = new MemoryMap(MEM0, "MEMORY_MAP_0", m0_memory_space_offset);
    p_mm0->SetSpaceSize(M0_NUMBER_REGS, m0_memory_size);
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
    uint64_t m1_memory_space_offset = ProgramOptions::GetInstance()->get_memory_size();
    uint64_t m1_memory_size = ProgramOptions::GetInstance()->get_memory_size();
    MemoryMapBuilder* p_mm_builder = MemoryMapBuilder::GetInstance();
    MemoryMap* p_mm1 = new MemoryMap(MEM1, "MEMORY_MAP_1", m1_memory_space_offset);
    p_mm1->SetSpaceSize(M1_NUMBER_REGS, m1_memory_size);
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
    uint64_t m2_memory_space_offset = 2*ProgramOptions::GetInstance()->get_memory_size();
    uint64_t m2_memory_size = ProgramOptions::GetInstance()->get_memory_size();
    MemoryMapBuilder* p_mm_builder = MemoryMapBuilder::GetInstance();
    MemoryMap* p_mm2 = new MemoryMap(MEM2, "MEMORY_MAP_2", m2_memory_space_offset);
    p_mm2->SetSpaceSize(M2_NUMBER_REGS, m2_memory_size);
    p_mm2->SetRegisterFieldsSize(M2_NUMBER_FIELDS);
    p_mm_builder->AddBlock(p_mm2);
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void BuildMemoryMap4Mem3()
{
    uint64_t m3_memory_space_offset = 3*ProgramOptions::GetInstance()->get_memory_size();
    uint64_t m3_memory_size = ProgramOptions::GetInstance()->get_memory_size();
    MemoryMapBuilder* p_mm_builder = MemoryMapBuilder::GetInstance();
    MemoryMap* p_mm3 = new MemoryMap(MEM3, "MEMORY_MAP_3", m3_memory_space_offset);
    p_mm3->SetSpaceSize(M3_NUMBER_REGS, m3_memory_size);
    p_mm3->SetRegisterFieldsSize(M3_NUMBER_FIELDS);
    p_mm_builder->AddBlock(p_mm3);
}

