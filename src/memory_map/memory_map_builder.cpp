/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#include "memory_map_builder.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
MemoryMapBuilder* MemoryMapBuilder::mp_instance = 0;

/////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
MemoryMapBuilder::MemoryMapBuilder()  
{
}

/////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
MemoryMapBuilder::~MemoryMapBuilder()  
{
}

/////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
MemoryMapBuilder* MemoryMapBuilder::GetInstance()
{
    if (mp_instance == 0) {
        mp_instance = new MemoryMapBuilder();
    }
    return mp_instance;  
} 


/////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
int MemoryMapBuilder::PrintMemoryMap()
{
}

