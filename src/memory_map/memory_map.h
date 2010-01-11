/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_MM_MEMORY_MAP_H
#define KOSIM_MM_MEMORY_MAP_H

#include <string>
#include <vector>
#include <stdint.h>

#include "systemc.h"
#include <boost/utility.hpp>

using namespace std;

class MemoryMap : boost::noncopyable
{
public:
    MemoryMap(const uint32_t id_, const string& name_, const uint32_t offset_);
    ~MemoryMap();
    uint32_t get_id()     { return m_id;};
    string*  get_name()   { return &m_name;};
    uint32_t get_offset() { return m_offset;};
    void     SetSpaceSize(const uint32_t num_regs_, const uint32_t mem_size_);
    uint32_t get_number_regs() { return m_number_registers;};
    uint32_t get_memory_size() { return m_memory_size;};
    bool     write(const uint32_t addr_, const uint32_t data_);
    bool     read (const uint32_t addr_, uint32_t* const p_data_);    
    
private:
    uint32_t    m_id    ; 
    string      m_name  ; 
    uint32_t    m_offset;           // 4bytes aligned
    uint32_t    m_number_registers; // 4 bytes regs
    uint32_t    m_memory_size;      // 4 bytes per memory location
    vector<sc_uint<32> > m_hw_resource;
};

#endif // KOSIM_MM_MEMORY_MAP_H
