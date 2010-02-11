/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#include "generic_cpu_base.h"
#include "memory_map_builder.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: name_ - the name of the module 
// OUT: 
// RET: 
GenericCPUBase::GenericCPUBase(sc_module_name name_) : 
    BInitiator(name_)
{

    
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
GenericCPUBase::~GenericCPUBase()
{
}

/////////////////////////////////////////////////////////////////////////////////////
// This function does not alter the hw_resource value, it prepares only the value needed
// IN:  block_id_ - the block where the register to be modified is located
//      reg_id_   - the register to be modified
//      field_id_ - the field to be modified
//      field_value_ - the new value of the field
// OUT: 
// RET: the new value of the entire register (32 bit) 
uint32_t 
GenericCPUBase::SetFieldValue(const uint32_t block_id_, const uint32_t field_id_, const uint32_t field_value_, const uint32_t reg_value_) // RESOURCES_ON_32_BITS
{
    MemoryMap* p_mmap = MemoryMapBuilder::GetInstance()->GetMemoryMap(block_id_);
    FieldTraits* p_field = p_mmap->GetFieldTraits(field_id_);
    m_field_accessor = reg_value_;
    m_field_accessor.range(p_field->msb, p_field->lsb) = field_value_;
    return m_field_accessor.to_uint();
}
/////////////////////////////////////////////////////////////////////////////////////
// This function does not read the hw_resource value, it extracts the field value out of a already read hardware resource 
// IN:  block_id_ - the block where the register to be read is located
//      reg_id_   - the register to be read 
//      field_id_ - the field to be read 
//      reg_value_ - the value of the register that has the fields read
// OUT:
// RET: the value of the field  
uint32_t 
GenericCPUBase::GetFieldValue(const uint32_t block_id_, const uint32_t field_id_, const uint32_t reg_value_) // RESOURCES_ON_32_BITS
{
    MemoryMap* p_mmap = MemoryMapBuilder::GetInstance()->GetMemoryMap(block_id_);
    FieldTraits* p_field = p_mmap->GetFieldTraits(field_id_);
    m_field_accessor = reg_value_;
    uint32_t field_value =  m_field_accessor.range(p_field->msb, p_field->lsb);
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
uint32_t 
GenericCPUBase::SetFieldValueRDL(const uint32_t block_id_, const uint32_t field_id_, const uint32_t field_value_, const uint32_t reg_value_) // RESOURCES_ON_32_BITS
{
    MemoryMap* p_mmap = MemoryMapBuilder::GetInstance()->GetMemoryMap(block_id_);
    FieldTraits* p_field = p_mmap->GetFieldTraits(field_id_);
    if (p_field->is_sw_write == false) return reg_value_; 
    m_field_accessor = reg_value_;
    uint32_t current_field_val = m_field_accessor.range(p_field->msb, p_field->lsb);
    uint32_t new_field_val = 0;
    if      (p_field->is_sw_write_one_to_set)   new_field_val = current_field_val | field_value_; 
    else if (p_field->is_sw_write_one_to_clear) new_field_val = current_field_val & ~field_value_; 
    else                                        new_field_val = field_value_; 

    m_field_accessor.range(p_field->msb, p_field->lsb) = new_field_val;
    return m_field_accessor.to_uint();
}
/////////////////////////////////////////////////////////////////////////////////////
// This function does not read the hw_resource value, it extracts the field value out of a already read hardware resource 
// IN:  block_id_ - the block where the register to be read is located
//      reg_id_   - the register to be read 
//      field_id_ - the field to be read 
//      reg_value_ - the value of the register that has the fields read
// OUT:
// RET: the value of the field  
uint32_t 
GenericCPUBase::GetFieldValueRDL(const uint32_t block_id_, const uint32_t field_id_, const uint32_t reg_value_) // RESOURCES_ON_32_BITS
{
    
    MemoryMap* p_mmap = MemoryMapBuilder::GetInstance()->GetMemoryMap(block_id_);
    FieldTraits* p_field = p_mmap->GetFieldTraits(field_id_);
    if (p_field->is_sw_read == false) return 0; // returns 0 for all fields that are not readable 
    m_field_accessor = reg_value_;
    uint32_t field_value =  m_field_accessor.range(p_field->msb, p_field->lsb);
    return field_value;
}

/////////////////////////////////////////////////////////////////////////////////////
// This function does not read the hw_resource value, it extracts the field value out of a already read hardware resource 
// IN:  block_id_ - the block where the register to be read is located
//      reg_id_   - the register to be read 
//      data_     - the new value of the register
// OUT:
// RET:
void  
GenericCPUBase::WriteRDL   (const uint32_t block_id_, const uint32_t reg_id_, uint32_t data_)
{
    MemoryMap* p_mmap = MemoryMapBuilder::GetInstance()->GetMemoryMap(block_id_);
    RegisterTraits* p_reg = p_mmap->GetRegisterTraits(reg_id_);
    m_field_accessor = data_;  
    vector<uint32_t>::iterator pos;
    uint32_t new_reg_val = 0;
    for ( pos = p_reg->m_fields.begin(); pos != p_reg->m_fields.end(); ++pos )
    {
        FieldTraits* p_field = p_mmap->GetFieldTraits(*pos);
        uint32_t field_val = m_field_accessor.range(p_field->msb, p_field->lsb);
        new_reg_val = SetFieldValueRDL(block_id_,  *pos, field_val, new_reg_val); // RESOURCES_ON_32_BITS
    }
    uint64_t  addr =  MemoryMapBuilder::GetInstance()->GetAbsoluteAddress(block_id_, reg_id_);
    Write(addr, new_reg_val);
}
/////////////////////////////////////////////////////////////////////////////////////
// This function does not read the hw_resource value, it extracts the field value out of a already read hardware resource 
// IN:  block_id_ - the block where the register to be read is located
//      reg_id_   - the register to be read 
//      field_id_ - the field to be read 
//      reg_value_ - the value of the register that has the fields read
// OUT:
// RET: the value of the register
uint32_t 
GenericCPUBase::ReadRDL    (const uint32_t block_id_, const uint32_t reg_id_)
{
    uint64_t  addr =  MemoryMapBuilder::GetInstance()->GetAbsoluteAddress(block_id_, reg_id_);
    uint32_t reg_value = Read(addr);

    MemoryMap* p_mmap = MemoryMapBuilder::GetInstance()->GetMemoryMap(block_id_);
    RegisterTraits* p_reg = p_mmap->GetRegisterTraits(reg_id_);

    m_field_accessor = 0;  
    vector<uint32_t>::iterator pos;
    for ( pos = p_reg->m_fields.begin(); pos != p_reg->m_fields.end(); ++pos )
    {
        uint32_t field_val = GetFieldValueRDL(block_id_, *pos, reg_value); // RESOURCES_ON_32_BITS
        FieldTraits* p_field = p_mmap->GetFieldTraits(*pos);
        m_field_accessor.range(p_field->msb, p_field->lsb) = field_val;
    }

    return m_field_accessor.to_uint();
}


