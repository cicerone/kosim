/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#include "generic_cpu.h"
#include "memory_map_builder.h"
#include "gen_from_sysrdl.h"

using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: name_ - the name of the module 
// OUT: 
// RET: 
GenericCPU::GenericCPU(sc_module_name name_) : 
    GenericCPUBase(name_)
{
    SC_THREAD(STMain);
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
GenericCPU::~GenericCPU()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void 
GenericCPU::InitSystem()
{
   mv_program_peripheral.resize(4);
   mv_program_peripheral[0] = &GenericCPU::TreatPeripheral0;
   mv_program_peripheral[1] = &GenericCPU::TreatPeripheral1;
   mv_program_peripheral[2] = &GenericCPU::TreatPeripheral2;
   mv_program_peripheral[3] = &GenericCPU::TreatPeripheral3;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void 
GenericCPU::TreatPeripheral0()
{
printf("%s", __PRETTY_FUNCTION__);
    Write32BitWord(0x00, 1);
    Write32BitWord(0x04, 2);
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void 
GenericCPU::TreatPeripheral1()
{
printf("%s", __PRETTY_FUNCTION__);
    Write32BitWord(0x100, 3);
    Write32BitWord(0x104, 4);
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void 
GenericCPU::TreatPeripheral2()
{
printf("%s\n", __PRETTY_FUNCTION__);
    
    uint64_t addr = MemoryMapBuilder::GetInstance()->GetAbsoluteAddress(MEM2, M2_REG0); 
    printf("addr = (0x%x)\n", addr);
    uint32_t reg_val = 5;
    Write32BitWord(addr, reg_val);
    uint32_t new_reg_val = WriteField(MEM2, M2_FIELD0, 1,  reg_val);
    Write32BitWord(addr, new_reg_val);

}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void 
GenericCPU::TreatPeripheral3()
{
    printf("%s\n", __PRETTY_FUNCTION__);
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// The main thread
// IN: 
// OUT: 
// RET: 
void 
GenericCPU::STMain()
{
    InitSystem();
    int32_t cntr = 0; 
    while(1)
    {
        uint32_t peripheral_id = m_irq.read(); //blocking read 
        if (peripheral_id < 3) {
            (this->*mv_program_peripheral[peripheral_id])();
        }
        // read the result
        
        printf("data[0x%x] = 0x%x\n", 0x08, Read32BitWord(0x08));
        printf("data[0x%x] = 0x%x\n", 0x108, Read32BitWord(0x108));
        
        printf("DBG data[0x%x] = 0x%x\n", 0x08, DbgRead32BitWord(0x08));
        printf("DBG data[0x%x] = 0x%x\n", 0x108, DbgRead32BitWord(0x108));

        if (cntr++ > 20) { cout << "Test PASSED" << endl; exit(0);}
    }

}
