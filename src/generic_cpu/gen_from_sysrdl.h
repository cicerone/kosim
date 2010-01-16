/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_GC_GEN_FROM_SYSRDL_H
#define KOSIM_GC_GEN_FROM_SYSRDL_H

enum BLOCK_ID
{
    MEM0 = 0,
    MEM1    ,
    MEM2    ,
    MEM3    ,
    NUMBER_PERIPHERALS
};

enum MEM0_MEMORY_MAP
{
    M0_MEMORY_SIZE   = 64,
    M0_NUMBER_REGS   =  0,
    M0_NUMBER_FIELDS =  0,
    M0_MEMORY_SPACE_OFFSET = 0x000 
};

enum MEM1_MEMORY_MAP
{
    M1_MEMORY_SIZE   = 64,
    M1_NUMBER_REGS   =  0,
    M1_NUMBER_FIELDS =  0,
    M1_MEMORY_SPACE_OFFSET = 0x100 
};

enum MEM2_MEMORY_MAP
{
    M2_MEMORY_SIZE   = 62,
    M2_NUMBER_REGS   =  2,
    M2_NUMBER_FIELDS =  5,
    M2_MEMORY_SPACE_OFFSET = 0x200 
};

enum MEM2_REGS
{
    M2_REG0 = 0,
    M2_REG1    
};

enum MEM2_FIELDS
{
    M2_FIELD0 = 0, // M3_REG0
    M2_FIELD1,     // M3_REG0
    M2_FIELD2,     // M3_REG0
    M2_FIELD3,     // M3_REG1 
    M2_FIELD4      // M3_REG1
};

enum MEM3_MEMORY_MAP
{
    M3_MEMORY_SIZE   = 64,
    M3_NUMBER_REGS   =  0,
    M3_NUMBER_FIELDS =  0,
    M3_MEMORY_SPACE_OFFSET = 0x300 
};

void BuildMemoryMap4Mem0();
void BuildMemoryMap4Mem1();
void BuildMemoryMap4Mem2();
void BuildMemoryMap4Mem3();

#endif //  KOSIM_GC_GEN_FROM_SYSRDL_H
