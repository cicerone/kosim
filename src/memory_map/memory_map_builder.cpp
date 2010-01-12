/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#include <algorithm>
#include "memory_map_builder.h"

using namespace std;
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
bool MemMapSortCriterion(MemoryMap* p_mm1_, MemoryMap* p_mm2_)
{
    if (p_mm1_->get_offset() < p_mm2_->get_offset()) return true;
    if (p_mm1_->get_offset() > p_mm2_->get_offset()) return false;
    fprintf(stderr, "ERROR! Two blocks (%s) and (%s) have the same offset (0x%x)\n", 
                     p_mm1_->get_name()->c_str(), p_mm2_->get_name()->c_str(), p_mm1_->get_offset());
    exit(1);
    return false;
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
MemoryMapBuilder* MemoryMapBuilder::mp_instance = 0;
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
MemoryMapBuilder::MemoryMapBuilder()  
{
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
MemoryMapBuilder::~MemoryMapBuilder()  
{
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
MemoryMapBuilder* MemoryMapBuilder::GetInstance()
{
    if (mp_instance == 0) {
        mp_instance = new MemoryMapBuilder();
    }
    return mp_instance;  
} 
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void MemoryMapBuilder::AddBlock(MemoryMap*  p_memmap_)
{
    m_memory_map.push_back(p_memmap_);
    std::sort(m_memory_map.begin(), m_memory_map.end(), MemMapSortCriterion);
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
int MemoryMapBuilder::PrintMemoryMap()
{
}

