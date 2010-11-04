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
FieldTraits::FieldTraits() : 
  msb(0),
  lsb(0),
  reset_value(0),
  mask_value (0),
  is_hw_read     (true), 
  is_hw_write    (true),
  is_hw_hwenable (false),
  is_hw_hwmask   (false),
  is_sw_read              (true),
  is_sw_write             (true),
  is_sw_clear_on_read     (false),
  is_sw_set_on_read       (false),
  is_sw_write_one_to_set  (false),
  is_sw_write_one_to_clear(false)
{
};
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
FieldTraits::~FieldTraits()
{
};
/////////////////////////////////////////////////////////////////////////////////////
//
// IN:   field_- the field ID
//       msb - the position of the most significatn bit
//       lsb - the position of the least significatn bit
// OUT: 
// RET: 
void FieldTraits::SetPosition(const uint32_t msb_, const uint32_t lsb_) // RESOURCES_ON_32_BITS
{
    msb = msb_;
    lsb = lsb_;
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN:   field_- the field ID
//       reset_val_ - the reset value 
//       mask_val   - the mask value
// OUT: 
// RET: 
void FieldTraits::SetValues(const uint32_t reset_val_, const uint32_t mask_val_)
{
    reset_value = reset_val_;
    mask_value  = mask_val_ ;
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN:  field_  - the field ID 
// OUT: 
// RET: 
void  FieldTraits::SetHWAccessProperties(const bool hw_read_, const bool hw_write_,  const bool hw_hwenable_, const bool hw_hwmask_)
{
    is_hw_read     = hw_read_    ;   
    is_hw_write    = hw_write_   ;
    is_hw_hwenable = hw_hwenable_;
    is_hw_hwmask   = hw_hwmask_  ;
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN:  field_  - the field ID 
// OUT: 
// RET: 
void FieldTraits::SetSWAccessProperties( const bool sw_read_, const bool sw_write_, const bool sw_clear_on_read_, 
                                         const bool sw_set_on_read_, const bool sw_write_one_to_set_, const bool sw_write_one_to_clear_)
{
    is_sw_read               = sw_read_              ;
    is_sw_write              = sw_write_             ;
    is_sw_clear_on_read      = sw_clear_on_read_     ; 
    is_sw_set_on_read        = sw_set_on_read_       ;  
    is_sw_write_one_to_set   = sw_write_one_to_set_  ;
    is_sw_write_one_to_clear = sw_write_one_to_clear_;
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
RegisterTraits::RegisterTraits()
{
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
RegisterTraits::~RegisterTraits()
{
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
MemoryMap::MemoryMap(const uint32_t id_, const string& name_, const sc_dt::uint64 offset_) :
  m_id              (id_    ),
  m_name            (name_  ),
  m_offset          (offset_),
  m_number_registers(0      ),
  m_memory_size     (0      )

{
    if (offset_ % sizeof(uint32_t) != 0) {
        fprintf(stderr, "ERROR! the memory map offset (0x%x) must be multiple of (%d)\n", offset_, sizeof(uint32_t)); // RESOURCES_ON_32_BITS
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
void MemoryMap::SetSpaceSize(const sc_dt::uint64 num_regs_, const sc_dt::uint64 mem_size_)
{
    m_number_registers = num_regs_;
    m_memory_size      = mem_size_;
    sc_dt::uint64 size = num_regs_ + mem_size_;
    m_hw_resource.resize(size, 0);
    m_register.resize(m_number_registers);
}
/////////////////////////////////////////////////////////////////////////////////////
// allocates the memory needed for registers and the memory bank
// IN:  num_fields_ - the total number of fields of all registers 
// OUT: 
// RET: 
void MemoryMap::SetRegisterFieldsSize(const sc_dt::uint64 num_fields_)
{
    m_register_field.resize(num_fields_);
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN:   resource_id_ - the ID of reg/memory
//       data_ - the value to be written
// OUT: 
// RET:  
void MemoryMap::Write(const sc_dt::uint64 resource_id_, const uint32_t data_) // RESOURCES_ON_32_BITS
{
    if (resource_id_ > m_hw_resource.size()) {
        fprintf(stderr, "ERROR! Block %s has resource ID (0x%x) out of range (0x%x)\n", m_name.c_str(), resource_id_, m_hw_resource.size()); 
        exit(1);
    }
    m_hw_resource[resource_id_] = data_;
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN:  resource_id_ - the ID of reg/memory
// OUT: p_data_      - reference to data that is read 
// RET:  
uint32_t MemoryMap::Read (const sc_dt::uint64 resource_id_)  // RESOURCES_ON_32_BITS
{
    if (resource_id_ > m_hw_resource.size()) {
        fprintf(stderr, "ERROR! Block %s has resource ID (0x%x) out of range (0x%x)\n", m_name.c_str(), resource_id_, m_hw_resource.size()); 
        exit(1);
    }
    return m_hw_resource[resource_id_];
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN:   resource_id_ - the ID of reg/memory
//       data_ - the value to be written
// OUT: 
// RET:  
void MemoryMap::WriteHwRDL(const sc_dt::uint64 reg_id_, const uint32_t data_) // RESOURCES_ON_32_BITS
{
    if (reg_id_ > m_register.size()) {
        fprintf(stderr, "ERROR! Block %s has resource ID (0x%x) out of range (0x%x)\n", m_name.c_str(), reg_id_, m_register.size()); 
        exit(1);
    }

    RegisterTraits reg = m_register[reg_id_];
    m_field_accessor_reg = data_;  
    vector<uint32_t>::iterator pos;
    for ( pos = reg.m_fields.begin(); pos != reg.m_fields.end(); ++pos )
    {
        uint32_t field_val = m_field_accessor_reg.range(m_register_field[*pos].msb, m_register_field[*pos].lsb);
        WriteHwRDL(reg_id_, *pos, field_val); // RESOURCES_ON_32_BITS
    }
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN:  resource_id_ - the ID of reg/memory
// OUT: p_data_      - reference to data that is read 
// RET:  
uint32_t MemoryMap::ReadHwRDL (const sc_dt::uint64 reg_id_)  // RESOURCES_ON_32_BITS
{
    if (reg_id_ > m_hw_resource.size()) {
        fprintf(stderr, "ERROR! Block %s has resource ID (0x%x) out of range (0x%x)\n", m_name.c_str(), reg_id_, m_hw_resource.size()); 
        exit(1);
    }

    RegisterTraits reg = m_register[reg_id_];
    m_field_accessor_reg = 0;  
    vector<uint32_t>::iterator pos;
    for ( pos = reg.m_fields.begin(); pos != reg.m_fields.end(); ++pos )
    {
        uint32_t field_val = ReadHwRDL (reg_id_, *pos); // RESOURCES_ON_32_BITS
        m_field_accessor_reg.range(m_register_field[*pos].msb, m_register_field[*pos].lsb) = field_val;
    }

    return m_field_accessor_reg.to_uint();
}
/////////////////////////////////////////////////////////////////////////////////////
// IN:   reg_id_ - the register ID
//       field_ - the field of the register where data is written
//       data_  - the value to be written
// OUT: 
// RET:  
void MemoryMap::Write(const sc_dt::uint64 reg_id_, const uint32_t field_, const uint32_t data_) // RESOURCES_ON_32_BITS
{
    m_field_accessor = m_hw_resource[reg_id_];
    m_field_accessor.range(m_register_field[field_].msb, m_register_field[field_].lsb) = data_;
    m_hw_resource[reg_id_] = m_field_accessor.to_uint();   
}
///////////////////////////////////////////////////////////////////////////////////// 
// IN:  reg_id_ - the register ID
//      field_  - the field the data is read from
// OUT:
// RET: the field value  
uint32_t MemoryMap::Read (const sc_dt::uint64 reg_id_, const uint32_t field_) // RESOURCES_ON_32_BITS
{
    m_field_accessor = m_hw_resource[reg_id_];
    return m_field_accessor.range(m_register_field[field_].msb, m_register_field[field_].lsb);
}
/////////////////////////////////////////////////////////////////////////////////////
// IN:   reg_id_ - the register ID
//       field_ - the field of the register where data is written
//       data_  - the value to be written
// OUT: 
// RET:  
void MemoryMap::WriteHwRDL(const sc_dt::uint64 reg_id_, const uint32_t field_id_, const uint32_t data_) // RESOURCES_ON_32_BITS
{
    if (m_register_field[field_id_].is_hw_write == false) return;
    FieldTraits field = m_register_field[field_id_];
    
    m_field_accessor_field = m_hw_resource[reg_id_];
    uint32_t new_field_value = data_;
    if      (field.is_hw_hwenable) 
    {
        sc_uint<32> aligned_data = data_ << field.lsb;
        sc_uint<32> aligned_mask = field.mask_value << field.lsb;
        for (uint32_t i = field.lsb; i <= field.msb; i++) {
            if (aligned_mask[i] == 1)  m_field_accessor_field[i] = aligned_data[i];   
        }        
    }
    else if (field.is_hw_hwmask)
    {
        sc_uint<32> aligned_data = data_ << field.lsb;
        sc_uint<32> aligned_mask = field.mask_value << field.lsb;
        
        for (uint32_t i = field.lsb; i <= field.msb; i++) {
            if (aligned_mask[i] == 0)  m_field_accessor_field[i] = aligned_data[i];
        }    
    }
    else {
        m_field_accessor_field.range(field.msb, field.lsb) = data_;
    }
    
    m_hw_resource[reg_id_] = m_field_accessor_field.to_uint();
}
///////////////////////////////////////////////////////////////////////////////////// 
// IN:  reg_id_ - the register ID
//      field_  - the field the data is read from
// OUT:  
// RET: the value of the field  
uint32_t MemoryMap::ReadHwRDL (const sc_dt::uint64 reg_id_, const uint32_t field_) // RESOURCES_ON_32_BITS
{
    if (m_register_field[field_].is_hw_read == false) return 0;
    m_field_accessor_field = m_hw_resource[reg_id_];
    return m_field_accessor_field.range(m_register_field[field_].msb, m_register_field[field_].lsb);
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN:  addr_ - the address of reg/memory; it is 4 bytes aligned
// OUT:
// RET: reference to the physical address where the vector data is stored 
uint32_t* MemoryMap::GetPhysicalAddress(const sc_dt::uint64 addr_)   // RESOURCES_ON_32_BITS
{
    sc_dt::uint64 local_addr = addr_ >> 2;
    if (local_addr > m_hw_resource.size()) {
        fprintf(stderr, "ERROR! Block %s has address (0x%x) out of range (0x%x)\n", m_name.c_str(), addr_, m_hw_resource.size()); 
        exit(1);
    }
    return &m_hw_resource[local_addr];
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN:  field_ - the field ID
// OUT:
// RET: reference to the field's traits 

FieldTraits* MemoryMap::GetFieldTraits(const uint32_t field_)
{
    return &m_register_field[field_];
}
/////////////////////////////////////////////////////////////////////////////////////
// Add the field to the register traits and resets the value of the field. 
// IN:  field_ - the field ID
// OUT:
// RET: reference to the field's traits 
void MemoryMap::AddField(const sc_dt::uint64 reg_id_, const uint32_t field_)
{
    m_register[reg_id_].m_fields.push_back(field_);  
    Write(reg_id_, field_, m_register_field[field_].reset_value); // reset the field
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN:  field_ - the field ID
// OUT:
// RET: reference to the field's traits 
RegisterTraits* MemoryMap::GetRegisterTraits(const uint32_t reg_id_)
{
    return &m_register[reg_id_];
}
/////////////////////////////////////////////////////////////////////////////////////
// This function does not alter the hw_resource value, it prepares only the value needed
// IN:  field_id_ - the field to be modified
//      field_value_ - the new value of the field
//      reg_value_   - the value of the register before updating the field
// OUT: 
// RET: the new value of the entire register (32 bit) 
void 
MemoryMap::WriteSwRDL(const sc_dt::uint64 reg_id_, const uint32_t field_id_, const uint32_t field_value_) // RESOURCES_ON_32_BITS
{
    if (m_register_field[field_id_].is_sw_write == false) return;     
    m_field_accessor_field = m_hw_resource[reg_id_];
    FieldTraits field = m_register_field[field_id_];
    uint32_t current_field_val = m_field_accessor_field.range(field.msb, field.lsb);
    uint32_t new_field_val = 0;
    if      ( field.is_sw_write_one_to_set)   new_field_val = current_field_val | field_value_; 
    else if ( field.is_sw_write_one_to_clear) new_field_val = current_field_val & (~field_value_); 
    else                                      new_field_val = field_value_; 

    m_field_accessor_field.range( field.msb, field.lsb) = new_field_val;
    m_hw_resource[reg_id_] = m_field_accessor_field.to_uint();
}

/////////////////////////////////////////////////////////////////////////////////////
// This function does not read the hw_resource value, it extracts the field value out of a already read hardware resource 
// IN:  reg_id_   - the register to be read 
//      field_id_ - the field to be read 
//      reg_value_ - the value of the register that has the fields read
// OUT:
// RET: the value of the field  
uint32_t 
MemoryMap::ReadSwRDL(const sc_dt::uint64 reg_id_, const uint32_t field_id_) // RESOURCES_ON_32_BITS
{
    FieldTraits field = m_register_field[field_id_];
    if ( field.is_sw_read == false) return 0; // returns 0 for all fields that are not readable 
    m_field_accessor_field = m_hw_resource[reg_id_];
    uint32_t field_value =  m_field_accessor_field.range(field.msb, field.lsb);
     
    if( field.is_sw_clear_on_read) {
        m_field_accessor_field.range(field.msb, field.lsb) = 0;
        m_hw_resource[reg_id_] = m_field_accessor_field;
    }; 
    if( field.is_sw_set_on_read) {
        m_field_accessor_field.range(field.msb, field.lsb) = 0xffffffff;
        m_hw_resource[reg_id_] = m_field_accessor_field;
    };   
    return field_value;
}
/////////////////////////////////////////////////////////////////////////////////////
// This function does not read the hw_resource value, it extracts the field value out of a already read hardware resource 
// IN:  reg_id_   - the register to be read 
//      data_     - the new value of the register
// OUT:
// RET:
void  
MemoryMap::WriteSwRDL   (const uint32_t reg_id_, uint32_t data_)
{
    RegisterTraits reg = m_register[reg_id_];
    m_field_accessor_reg = data_;  
    vector<uint32_t>::iterator pos;
    for ( pos = reg.m_fields.begin(); pos != reg.m_fields.end(); ++pos )
    {   
        uint32_t field_val = m_field_accessor_reg.range(m_register_field[*pos].msb, m_register_field[*pos].lsb);      
        WriteSwRDL(reg_id_, *pos, field_val);
    }
}
/////////////////////////////////////////////////////////////////////////////////////
// This function does not read the hw_resource value, it extracts the field value out of a already read hardware resource 
// IN:  reg_id_   - the register to be read 
//      field_id_ - the field to be read 
//      reg_value_ - the value of the register that has the fields read
// OUT:
// RET: the value of the register
uint32_t 
MemoryMap::ReadSwRDL    (const uint32_t reg_id_)
{
    RegisterTraits reg = m_register[reg_id_];
    m_field_accessor_reg = 0;  
    vector<uint32_t>::iterator pos;
    for ( pos = reg.m_fields.begin(); pos != reg.m_fields.end(); ++pos )
    {
        uint32_t field_val = ReadSwRDL(reg_id_, *pos);
        m_field_accessor_reg.range(m_register_field[*pos].msb, m_register_field[*pos].lsb) = field_val;
    }

    return m_field_accessor_reg.to_uint();
}


