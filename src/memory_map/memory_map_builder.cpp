/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#include <algorithm>
#include "memory_map_builder.h"

using namespace std;

static sc_uint<32> g_reg_val;

/////////////////////////////////////////////////////////////////////////////////////
//
// IN:  p_mm1, p_mm2 - the MemoryMaps that are compared; the comparison criterion refers to the memory offset;
//      The MemoryMapBuilder will sort the MemoryMap space in ascending order of the offsets.
// OUT: 
// RET: 
bool MemMapSortCriterion(const MemoryMap* p_mm1_, const MemoryMap* p_mm2_)
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
uint32_t SetFieldValue(const uint32_t block_id_, const uint32_t field_id_, const uint32_t field_value_, const uint32_t reg_value_) // RESOURCES_ON_32_BITS
{
    MemoryMap* p_mmap = MemoryMapBuilder::GetInstance()->GetMemoryMap(block_id_);
    FieldTraits* p_field = p_mmap->GetFieldTraits(field_id_);
    g_reg_val = reg_value_;
    g_reg_val.range(p_field->msb, p_field->lsb) = field_value_;
    return g_reg_val.to_uint();
}
/////////////////////////////////////////////////////////////////////////////////////
// This function does not read the hw_resource value, it extracts the field value out of a already read hardware resource 
// IN:  block_id_ - the block where the register to be read is located
//      reg_id_   - the register to be read 
//      field_id_ - the field to be read 
//      reg_value_ - the value of the register that has the fields read
// OUT:
// RET: the value of the field  
uint32_t GetFieldValue(const uint32_t block_id_, const uint32_t field_id_, const uint32_t reg_value_) // RESOURCES_ON_32_BITS
{
    MemoryMap* p_mmap = MemoryMapBuilder::GetInstance()->GetMemoryMap(block_id_);
    FieldTraits* p_field = p_mmap->GetFieldTraits(field_id_);
    g_reg_val = reg_value_;
    uint32_t field_value =  g_reg_val.range(p_field->msb, p_field->lsb);
    return field_value;
}
/////////////////////////////////////////////////////////////////////////////////////
// This function does not alter the hw_resource value, it prepares only the value needed
// IN:  block_id_ - the block where the register to be modified is located
//      field_id_ - the field to be modified
//      field_value_ - the new value of the field
//      reg_value_   - the value of the register before updating the field
// OUT: 
// RET: the new value of the entire register (32 bit) 
uint32_t SetFieldValueRDL(const uint32_t block_id_, const uint32_t field_id_, const uint32_t field_value_, const uint32_t reg_value_) // RESOURCES_ON_32_BITS
{
    MemoryMap* p_mmap = MemoryMapBuilder::GetInstance()->GetMemoryMap(block_id_);
    FieldTraits* p_field = p_mmap->GetFieldTraits(field_id_);
    if (p_field->is_sw_write == false) return reg_value_; 
    g_reg_val = reg_value_;
    uint32_t current_field_val = g_reg_val.range(p_field->msb, p_field->lsb);
    uint32_t new_field_val = 0;
    if      (p_field->is_sw_write_one_to_set)   new_field_val = current_field_val | field_value_; 
    else if (p_field->is_sw_write_one_to_clear) new_field_val = current_field_val & ~field_value_; 
    else                                        new_field_val = field_value_; 

    g_reg_val.range(p_field->msb, p_field->lsb) = new_field_val;
    return g_reg_val.to_uint();
}
/////////////////////////////////////////////////////////////////////////////////////
// This function does not read the hw_resource value, it extracts the field value out of a already read hardware resource 
// IN:  block_id_ - the block where the register to be read is located
//      reg_id_   - the register to be read 
//      field_id_ - the field to be read 
//      reg_value_ - the value of the register that has the fields read
// OUT:
// RET: the value of the field  
uint32_t GetFieldValueRDL(const uint32_t block_id_, const uint32_t field_id_, const uint32_t reg_value_) // RESOURCES_ON_32_BITS
{
    
    MemoryMap* p_mmap = MemoryMapBuilder::GetInstance()->GetMemoryMap(block_id_);
    FieldTraits* p_field = p_mmap->GetFieldTraits(field_id_);
    if (p_field->is_sw_read == false) return 0; // returns 0 for all fields that are not readable 
    g_reg_val = reg_value_;
    uint32_t field_value =  g_reg_val.range(p_field->msb, p_field->lsb);
    return field_value;
}

/////////////////////////////////////////////////////////////////////////////////////
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
uint64_t MemoryMapBuilder::GetAbsoluteAddress(const uint32_t block_id_, const uint32_t hw_resource_id_) const
{
    uint64_t addr = m_memory_map[block_id_]->get_offset() + (hw_resource_id_ << 2); // RESOURCES_ON_32_BITS  
    return addr;
}
/////////////////////////////////////////////////////////////////////////////////////
//  
// IN:   block_id_ - the target peripheral
//       local_addr_ - the local address of a resource (reg or memory) 
// OUT: 
// RET:  the address in the absolute memory space of the reource 
uint64_t   MemoryMapBuilder::GetAbsoluteAddress2(const uint32_t block_id_, const uint64_t local_addr_) const
{
    uint64_t addr = m_memory_map[block_id_]->get_offset() + local_addr_;   
    return addr;
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN:  addr_ - the address of the resource in the global memory space 
// OUT: p_ local_addr__ - reference to the local address of the target 
// RET: the ID of the block that contains the adress addr_
uint32_t MemoryMapBuilder::FindTarget(const uint64_t addr_, uint64_t* const p_local_addr_)  
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
MemoryMap* MemoryMapBuilder::GetMemoryMap(const uint32_t block_id_) const 
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

