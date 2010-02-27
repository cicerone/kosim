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
printf("%s\n", __PRETTY_FUNCTION__);
    uint32_t data[2] = {1, 2};
    DbgWrite(0x00, data, 2*sizeof(uint32_t));
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void 
GenericCPU::TreatPeripheral1()
{
printf("%s\n", __PRETTY_FUNCTION__);
    uint32_t data[2] = {3, 4};
    Write(0x100, data, 2*sizeof(uint32_t));
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
   uint32_t reg_val = Read(addr);
   fprintf(stderr, "==== Read reg_val(0x%8x)\n", reg_val);
   reg_val = DbgRead(addr);
   fprintf(stderr, "==== DbgRead note FIELD2 0x0==>0xb, FIELD5 0xf==>0x0, FIELD6 0x5==>0xf reg_val(0x%8x)\n", reg_val);

   reg_val = SetFieldValue(MEM2, M2_FIELD0, 0x3,  reg_val);
   Write(addr, &reg_val);
   reg_val = DbgRead(addr);
   fprintf(stderr, "==== DbgRead FIELD0 must be 4 reg_val(0x%08x)\n", reg_val);

   reg_val = SetFieldValue(MEM2, M2_FIELD1, 0,  reg_val);
   Write(addr, &reg_val);
   reg_val = DbgRead(addr);
   fprintf(stderr, "==== DbgRead FIELD1 must be 0xf reg_val(0x%08x)\n", reg_val);
   
   reg_val = SetFieldValue(MEM2, M2_FIELD3, 0x7,  reg_val);
   Write(addr, &reg_val);
   reg_val = DbgRead(addr);
   fprintf(stderr, "==== DbgRead FIELD3 must be 0x7 reg_val(0x%08x)\n", reg_val);

   reg_val = SetFieldValue(MEM2, M2_FIELD4, 0x8,  reg_val);
   Write(addr, &reg_val);
   reg_val = DbgRead(addr);
   fprintf(stderr, "==== DbgRead FIELD4 must be 0x8 reg_val(0x%08x)\n", reg_val);
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
    uint32_t a_data[3] = {0, 0, 0};
    Read(0x00, a_data, 3*sizeof(uint32_t));
    printf("data[0x%x] = 0x%08x\n", 0x00, a_data[0]);
    printf("data[0x%x] = 0x%08x\n", 0x04, a_data[1]);
    printf("data[0x%x] = 0x%08x\n", 0x08, a_data[2]);


    DbgRead(0x100, a_data, 3*sizeof(uint32_t));
    printf("data[0x%x] = 0x%08x\n", 0x100, a_data[0]);
    printf("data[0x%x] = 0x%08x\n", 0x104, a_data[1]);
    printf("data[0x%x] = 0x%08x\n", 0x108, a_data[2]);

    uint32_t data = 0; 
    DbgRead(0x200, &data);
    printf("data[0x%x] = 0x%08x\n",  0x200, data);
    DbgRead(0x204, &data);
    printf("data[0x%x] = 0x%08x\n",  0x204, data);
    DbgRead(0x208, &data);
    printf("data[0x%x] = 0x%08x\n",  0x208, data);
    
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
        if (peripheral_id < NUMBER_PERIPHERALS) {
            (this->*mv_program_peripheral[peripheral_id])();
        }

        if (cntr++ > 4) { cout << "Test PASSED" << endl; exit(0);}
    }
}
