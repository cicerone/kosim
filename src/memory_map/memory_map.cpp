/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#include "memory_map.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
MemoryMap::MemoryMap(const uint32_t id_, const string& name_, const uint32_t offset_) :
  m_id              (id_    ),
  m_name            (name_  ),
  m_offset          (offset_),
  m_number_registers(0      ),
  m_memory_size     (0      )
{
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
MemoryMap::~MemoryMap()  
{
}
/////////////////////////////////////////////////////////////////////////////////////
// allocates the memory needed for registers and the memory bank
// IN:  num_regs_ - the number of registers
//      mem_size_ - the size of the memory bank
// OUT: 
// RET: 
void MemoryMap::SetSpaceSize(const uint32_t num_regs_, const uint32_t mem_size_)
{
    m_number_registers = num_regs_;
    m_memory_size      = mem_size_;
    uint32_t size = num_regs_ + mem_size_;
    m_hw_resource.resize(size, 0);
}

/////////////////////////////////////////////////////////////////////////////////////
//
// IN:   addr_ - the address of reg/memory; it is 4 byte aligned 
//       data_ - the value to be written
// OUT: 
// RET:  true if the operation was succesfull
bool MemoryMap::write(const uint32_t addr_, const uint32_t data_)
{
    uint32_t local_addr = addr_ >> 2;
    if (local_addr > m_hw_resource.size()) return false; // out of space
    m_hw_resource[local_addr] = data_;
    return true;
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
bool MemoryMap::read (const uint32_t addr_, uint32_t* const p_data_)
{
    uint32_t local_addr = addr_ >> 2;
    if (local_addr > m_hw_resource.size()) return false; // out of space
    *p_data_ = m_hw_resource[local_addr];
    return true;
}

