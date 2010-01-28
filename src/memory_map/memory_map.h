/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_MM_MEMORY_MAP_H
#define KOSIM_MM_MEMORY_MAP_H

#include <stdint.h>
#include <string>
#include <vector>

#include "systemc.h"
#include <boost/utility.hpp>

using namespace std;

class MemoryMap : boost::noncopyable
{
public:
    MemoryMap(const uint32_t id_, const string& name_, const uint64_t offset_);
    ~MemoryMap();
    uint32_t get_id()         const { return m_id;};
    const string*  get_name() const { return &m_name;};
    uint32_t get_offset()     const { return m_offset;};
    void     SetSpaceSize(const uint64_t num_regs_, const uint64_t mem_size_);
    void     SetRegisterFieldsSize(const uint64_t num_fields_);
    uint32_t get_number_regs() const  { return m_number_registers;};
    uint32_t get_memory_size() const { return m_memory_size;};
    // size of memory space in bytes
    uint32_t get_memory_space() { return (sizeof(uint32_t)*(m_number_registers + m_memory_size));};  // RESOURCES_ON_32_BITS
    void     Write(const uint64_t resource_id_, const uint32_t data_);
    void     Read (const uint64_t resource_id_, uint32_t* const p_data_);    
    void     Write(const uint64_t reg_id_, const uint32_t field_, const uint32_t data_);
    void     Read (const uint64_t reg_id_, const uint32_t field_, uint32_t* const p_data_);    
    void     set_register_field(const uint32_t field_, const uint32_t msb_, const uint32_t lsb_);
    void     get_register_field(const uint32_t field_, uint32_t* const p_msb_, uint32_t* const p_lsb_);
    uint32_t* GetPhysicalAddress(const uint64_t addr_);
    
private:
    struct FieldRange
    {
        uint32_t msb;
        uint32_t lsb;
    };

    uint32_t    m_id    ; 
    string      m_name  ; 
    uint64_t    m_offset;           // 4 bytes aligned
    uint64_t    m_number_registers; // 4 bytes regs
    uint64_t    m_memory_size;      // 4 bytes per memory location
    
//    vector<sc_uint<32> > m_hw_resource;     //RESOURCES_ON_32_BITS 
    vector<uint32_t>     m_hw_resource;       //RESOURCES_ON_32_BITS 
    vector<FieldRange>   m_register_field;

};

#endif // KOSIM_MM_MEMORY_MAP_H
