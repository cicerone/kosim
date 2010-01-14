/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_MM_MEMORY_MAP_BUILDER_H
#define KOSIM_MM_MEMORY_MAP_BUILDER_H

#include <stdint.h>
#include <vector>

#include <boost/utility.hpp>
#include "memory_map.h"


bool MemMapSortCriterion(MemoryMap* p_mm1_, MemoryMap* p_mm2_);
uint32_t WriteField(uint32_t block_id_, uint32_t field_id_, uint32_t field_value_);
uint32_t ReadField(uint32_t block_id_, uint32_t field_id_, uint32_t reg_value_);

class MemoryMapBuilder : boost::noncopyable
{
public:
    static MemoryMapBuilder* GetInstance();     
    void AddBlock(MemoryMap* p_memmap_);
    uint32_t GetAbsoluteAddress(uint32_t block_id_, uint32_t reg_id_);
    uint32_t FindTarget(uint32_t addr_);
    MemoryMap* GetMemoryMap(uint32_t block_id_);

    int  PrintMemoryMap();
    ~MemoryMapBuilder();
private:
    static MemoryMapBuilder* mp_instance;

    MemoryMapBuilder();
    vector<MemoryMap*> m_memory_map;
};

#endif // KOSIM_MM_MEMORY_MAP_BUILDER_H
