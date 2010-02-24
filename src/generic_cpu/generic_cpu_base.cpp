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

