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
    if (offset_ % sizeof(uint32_t) != 0) {
        fprintf(stderr, "ERROR! the memory map offset (0x%x) must be multiple of (%d)\n", offset_, sizeof(uint32_t));
        exit(1);
    }
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
// allocates the memory needed for registers and the memory bank
// IN:  num_fields_ - the total number of fields of all registers 
// OUT: 
// RET: 
void MemoryMap::SetRegisterFieldsSize(const uint32_t num_fields_)
{
    m_register_field.resize(num_fields_);
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN:   addr_ - the address of reg/memory; it is 4 byte aligned 
//       data_ - the value to be written
// OUT: 
// RET:  true if the operation was succesfull
void MemoryMap::write(const uint32_t addr_, const uint32_t data_)
{
    uint32_t local_addr = addr_ >> 2;
    if (local_addr > m_hw_resource.size()) {
        fprintf(stderr, "ERROR! Block %s has address (0x%x) out of range (0x%x)\n", m_name.c_str(), addr_, m_hw_resource.size()); 
        exit(1);
    }
    m_hw_resource[local_addr] = data_;
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: addr_ - the address of reg/memory; it is 4 bytes aligned
// OUT: p_data_ - reference to data that is read 
// RET:  true if the operation was succesfull
void MemoryMap::read (const uint32_t addr_, uint32_t* const p_data_)
{
    uint32_t local_addr = addr_ >> 2;
    if (local_addr > m_hw_resource.size()) {
        fprintf(stderr, "ERROR! Block %s has address (0x%x) out of range (0x%x)\n", m_name.c_str(), addr_, m_hw_resource.size()); 
        exit(1);
    }
    *p_data_ = m_hw_resource[local_addr];
}
/////////////////////////////////////////////////////////////////////////////////////
// This is a backdoor method to write directly the regs only. Probably should not be used.
// TLM debug transport mechanims probably should be preferred.
// IN:   addr_  - the address of reg/memory; it is 4 byte aligned 
//       field_ - the field of the register where data is written
//       data_  - the value to be written
// OUT: 
// RET:  true if the operation was succesfull
void MemoryMap::write(const uint32_t reg_id_, const uint32_t field_, const uint32_t data_)
{
    m_hw_resource[reg_id_].range(m_register_field[field_].msb, m_register_field[field_].lsb) = data_;
}
/////////////////////////////////////////////////////////////////////////////////////
// This is a backdoor method to read directly the regs only. Probably should not be used.
// TLM debug transport mechanims probably should be preferred.
// IN:  addr_   - the address of reg/memory; it is 4 bytes aligned
//      field_  - the field the data is read from
// OUT: p_data_ - reference to data that is read 
// RET:  true if the operation was succesfull
void MemoryMap::read (const uint32_t reg_id_, const uint32_t field_, uint32_t* const p_data_)
{
    *p_data_ = m_hw_resource[reg_id_].range(m_register_field[field_].msb, m_register_field[field_].lsb);
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN:   addr_ - the address of reg/memory; it is 4 byte aligned 
//       data_ - the value to be written
// OUT: 
// RET:  true if the operation was succesfull
void MemoryMap::set_register_field(const uint32_t field_, const uint32_t msb_, const uint32_t lsb_)
{
    m_register_field[field_].msb = msb_;
    m_register_field[field_].lsb = lsb_;
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: addr_ - the address of reg/memory; it is 4 bytes aligned
// OUT: p_data_ - reference to data that is read 
// RET:  true if the operation was succesfull
void MemoryMap::get_register_field(const uint32_t field_, uint32_t* const p_msb_, uint32_t* const p_lsb_)
{
    *p_msb_ = m_register_field[field_].msb;
    *p_lsb_ = m_register_field[field_].lsb;
}


