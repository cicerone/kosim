/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_EX_GC_TEST1_GEN_FROM_SYSRDL_H
#define KOSIM_EX_GC_TEST1_GEN_FROM_SYSRDL_H

#include <stdint.h>

enum BLOCK_ID
{
    MEM0 = 0,
    MEM1    ,
    NUMBER_PERIPHERALS
};

enum MEM0_MEMORY_MAP
{
    M0_MEMORY_SIZE   = 64,
    M0_MEMORY_SPACE_OFFSET = 0x000 
};

enum MEM0_REGS
{
    M0_NUMBER_REGS   =  0
};

enum MEM0_FIELDS
{
    M0_NUMBER_FIELDS =  0
};

enum MEM1_MEMORY_MAP
{
    M1_MEMORY_SIZE   = 64,
    M1_MEMORY_SPACE_OFFSET = 0x100 
};

enum MEM1_REGS
{
    M1_NUMBER_REGS   =  0
};

enum MEM1_FIELDS
{
    M1_NUMBER_FIELDS =  0
};

void BuildMemoryMap4Mem0();
void BuildMemoryMap4Mem1();

#endif //  KOSIM_EX_GC_TEST1_GEN_FROM_SYSRDL_H
