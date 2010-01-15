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
// IN:  p_mm1, p_mm2 - the MemoryMaps that are compared; the comparison criterion refers to the memory offset;
//      The MemoryMapBuilder will sort the MemoryMap space in ascending order of the offsets.
// OUT: 
// RET: 
bool MemMapSortCriterion(MemoryMap* p_mm1_, MemoryMap* p_mm2_)
{
    if (p_mm1_->get_offset() < p_mm2_->get_offset()) return true;
    if (p_mm1_->get_offset() >= p_mm2_->get_offset()) return false;
}
/////////////////////////////////////////////////////////////////////////////////////
// This function does not alter the hw_resource value, it prepares only the value needed
// IN:  block_id_ - the block where the register to be modified is located
//      reg_id_   - the register to be modified
//      field_id_ - the field to be modified
//      field_value_ - the new value of the field
// OUT: 
// RET: the new value of the entire register (32 bit) 
uint32_t WriteField(uint32_t block_id_, uint32_t field_id_, uint32_t field_value_)
{
    uint32_t msb = 0;
    uint32_t lsb = 0;
    MemoryMap* p_mmap = MemoryMapBuilder::GetInstance()->GetMemoryMap(block_id_);
    p_mmap->get_register_field(field_id_, &msb, &lsb);
    sc_uint<32> data;
    data.range(msb, lsb) = field_value_;
    return data.to_uint();
}
/////////////////////////////////////////////////////////////////////////////////////
// This function does not read the hw_resource value, it extracts the field value out of a already read hardware resource 
// IN:  block_id_ - the block where the register to be read is located
//      reg_id_   - the register to be read 
//      field_id_ - the field to be read 
//      reg_value_ - the value of the register that has the fiels read
// OUT:
// RET: the value of the field 
uint32_t ReadField(uint32_t block_id_, uint32_t field_id_, uint32_t reg_value_)
{
    uint32_t msb = 0;
    uint32_t lsb = 0;
    MemoryMap* p_mmap = MemoryMapBuilder::GetInstance()->GetMemoryMap(block_id_);
    p_mmap->get_register_field(field_id_, &msb, &lsb);
    sc_uint<32> reg_val = reg_value_;
    uint32_t field_value =  reg_val.range(msb, lsb);
    return field_value;
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
//       hw_resource_id_ - the local id of a resource (reg or memory) 
// OUT: 
// RET:  the address in the absolute memory space of the reource 
uint64_t MemoryMapBuilder::GetAbsoluteAddress(uint32_t block_id_, uint32_t hw_resource_id_)
{
    uint32_t addr = m_memory_map[block_id_]->get_offset() + hw_resource_id_ << 2; //  
    return addr;
}
/////////////////////////////////////////////////////////////////////////////////////
//  
// IN:   block_id_ - the target peripheral
//       local_addr_ - the local address of a resource (reg or memory) 
// OUT: 
// RET:  the address in the absolute memory space of the reource 
uint64_t   MemoryMapBuilder::GetAbsoluteAddress(uint32_t block_id_, uint64_t local_addr_)
{
    uint32_t addr = m_memory_map[block_id_]->get_offset() + local_addr_; //  
    return addr;
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN:  addr_ - the address of the resource in the global memory space 
// OUT: p_ local_addr__ - reference to the local address of the target 
// RET: the ID of the block that contains the adress addr_
uint32_t MemoryMapBuilder::FindTarget(uint64_t addr_, uint64_t* p_local_addr_)
{
    vector<MemoryMap*>::iterator pos;
    MemoryMap local_mmap(0, "local", addr_);
    pos = std::upper_bound(m_memory_map.begin(), m_memory_map.end(), &local_mmap, MemMapSortCriterion);
    if (pos == m_memory_map.begin()) {
        fprintf(stderr, "ERROR! Wrong start address!\n");
        exit(1);
    }
    pos--; // find the start of the range
    *p_local_addr_ = addr_ - (*pos)->get_offset();
    return (*pos)->get_id();
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN:  block_id_ - the peripheral block id 
// OUT: 
// RET: reference to the memory map 
MemoryMap* MemoryMapBuilder::GetMemoryMap(uint32_t block_id_)
{
    return m_memory_map[block_id_];
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
int MemoryMapBuilder::PrintMemoryMap()
{
}

