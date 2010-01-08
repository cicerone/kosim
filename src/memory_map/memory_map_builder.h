/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_MM_MEMORY_MAP_BUILDER_H
#define KOSIM_MM_MEMORY_MAP_BUILDER_H

//#include <string>
//#include <iostream>
//#include <fstream>
#include <stdint.h>

#include <boost/utility.hpp>


class MemoryMapBuilder : boost::noncopyable
{
public:
    static MemoryMapBuilder* GetInstance();                       // NOTE: can be called any time after 

    int  PrintMemoryMap();

    ~MemoryMapBuilder();
private:
    static MemoryMapBuilder* mp_instance;

    MemoryMapBuilder();
};

#endif // KOSIM_MM_MEMORY_MAP_BUILDER_H
