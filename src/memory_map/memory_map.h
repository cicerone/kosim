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

class FieldTraits
{
public:
    FieldTraits();
    ~FieldTraits();
    void     SetPosition(const uint32_t msb_, const uint32_t lsb_);
    void     SetValues(const uint32_t reset_val_, const uint32_t mask_val_);
    void     SetHWAccessProperties(const bool hw_read_, const bool hw_write_, const bool hw_anded_, const bool hw_ored_, 
                                   const bool hw_xored_, const bool hw_hwenable_, const bool hw_hwmask_);
    void     SetSWAccessProperties( const bool sw_read_, const bool sw_write_, const bool sw_clear_on_read_, 
                                    const bool sw_set_on_read_, const bool sw_write_one_to_set_, const bool sw_write_one_to_clear_);

public:
    uint32_t msb;
    uint32_t lsb;
    uint32_t reset_value;
    uint32_t mask_value;
    bool is_hw_read;
    bool is_hw_write;
    bool is_hw_anded;
    bool is_hw_ored;
    bool is_hw_xored;
    bool is_hw_hwenable;
    bool is_hw_hwmask;
//NA    bool is_hw_we;
//NA    bool is_hw_wel;
//NA    bool is_hw_fieldwidth;
//NA    bool is_hw_hwclr;
//NA    bool is_hw_hwset;

    bool is_sw_read;
    bool is_sw_write;
    bool is_sw_clear_on_read;  // NOTE: a read operation triggers a write operation, not implemented for now...
    bool is_sw_set_on_read;    // NOTE: a read operation triggers a write operation, not implemented for now...
    bool is_sw_write_one_to_set;
    bool is_sw_write_one_to_clear;
//NA    bool is_sw_swwe;
//NA    bool is_sw_swwel;
//NA    bool is_sw_swmod;
//NA    bool is_sw_swacc;
//NA    bool is_sw_single_pulse;
    
};

class RegisterTraits
{
public:
    RegisterTraits();
    ~RegisterTraits();
public:
    vector<uint32_t>  m_fields;   
};


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
    uint32_t Read (const uint64_t resource_id_);    
    void     WriteRDL(const uint64_t resource_id_, const uint32_t data_);
    uint32_t ReadRDL (const uint64_t resource_id_);    
    void     Write(const uint64_t reg_id_, const uint32_t field_, const uint32_t data_);
    uint32_t Read (const uint64_t reg_id_, const uint32_t field_);    
    void     WriteRDL(const uint64_t reg_id_, const uint32_t field_, const uint32_t data_);
    uint32_t ReadRDL (const uint64_t reg_id_, const uint32_t field_);    

    uint32_t*    GetPhysicalAddress(const uint64_t addr_);
    FieldTraits* GetFieldTraits(const uint32_t field_);
    void AddField(const uint64_t reg_id_, const uint32_t field_);
    
private:

    uint32_t    m_id    ; 
    string      m_name  ; 
    uint64_t    m_offset;           // 4 bytes aligned
    uint64_t    m_number_registers; // 4 bytes regs
    uint64_t    m_memory_size;      // 4 bytes per memory location
    
//    vector<sc_uint<32> > m_hw_resource;     //RESOURCES_ON_32_BITS 
    vector<uint32_t>       m_hw_resource;       //RESOURCES_ON_32_BITS 
    vector<FieldTraits>    m_register_field;
    vector<RegisterTraits> m_register;

    sc_uint<32> m_field_accessor; // used for field access
    sc_uint<32> m_field_accessor_rdl; // used for field access
};

#endif // KOSIM_MM_MEMORY_MAP_H
