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
////////////////////////////////////////////////////////////////////////////////////
MemoryMap::MemoryMap(const uint32_t id_, const string& name_, const uint32_t offset_) :
  m_id   (id_     ),
  m_name (name_   ),
  m_offset(offset_)
{
}

/////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
MemoryMap::~MemoryMap()  
{
}
