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

#include <boost/utility.hpp>

using namespace std;

class MemoryMap : boost::noncopyable
{
public:
    MemoryMap(const uint32_t id_, const string& name_, const uint32_t offset_);
    ~MemoryMap();
private:
    uint32_t    m_id    ; 
    string      m_name  ; 
    uint32_t    m_offset;
};

#endif // KOSIM_MM_MEMORY_MAP_H
