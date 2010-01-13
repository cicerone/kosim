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
// IN: p_memmap_ - reference to a block memory map that is added to the global space
// OUT: 
// RET: 
void MemoryMapBuilder::AddBlock(MemoryMap*  p_memmap_)
{
    m_memory_map.push_back(p_memmap_);
    std::sort(m_memory_map.begin(), m_memory_map.end(), MemMapSortCriterion);
}
/////////////////////////////////////////////////////////////////////////////////////
//  
// IN:   block_id_ - the target peripheral
//       ihw_resource_id_ - the local address of a resource (reg or memory) 
// OUT: 
// RET:  the address in the absolute memory space of the reource 
uint32_t MemoryMapBuilder::GetAbsoluteAddress(uint32_t block_id_, uint32_t hw_resource_id_)
{
    uint32_t addr = m_memory_map[block_id_]->get_offset() + hw_resource_id_ << 2; //  
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN:  addr_ - the address of the resource 
// OUT: 
// RET: the ID of the block that contains the adress addr_
uint32_t MemoryMapBuilder::FindTarget(uint32_t addr_)
{
    vector<MemoryMap*>::iterator pos;
    MemoryMap local_mmap(0, "local", addr_);
    pos = std::upper_bound(m_memory_map.begin(), m_memory_map.end(), &local_mmap, MemMapSortCriterion);
    if (pos == m_memory_map.begin()) {
        fprintf(stderr, "ERROR! Wrong start address!\n");
        exit(1);
    }
    pos--; // find the start of the range
    return (*pos)->get_id();
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
int MemoryMapBuilder::PrintMemoryMap()
{
}

