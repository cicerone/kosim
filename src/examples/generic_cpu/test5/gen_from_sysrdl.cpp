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
    sc_dt::uint64 m0_memory_space_offset = 0;
    sc_dt::uint64 m0_memory_size = ProgramOptions::GetInstance()->get_memory_size();
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
    sc_dt::uint64 m1_memory_space_offset = ProgramOptions::GetInstance()->get_memory_size();
    sc_dt::uint64 m1_memory_size = ProgramOptions::GetInstance()->get_memory_size();
    MemoryMapBuilder* p_mm_builder = MemoryMapBuilder::GetInstance();
    MemoryMap* p_mm1 = new MemoryMap(MEM1, "MEMORY_MAP_1", m1_memory_space_offset);
    p_mm1->SetSpaceSize(M1_NUMBER_REGS, m1_memory_size);
    p_mm1->SetRegisterFieldsSize(M1_NUMBER_FIELDS);
    p_mm_builder->AddBlock(p_mm1);
}

