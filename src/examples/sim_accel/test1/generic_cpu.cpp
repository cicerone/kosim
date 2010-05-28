/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#include "generic_cpu.h"
#include "memory_map_builder.h"
#include "gen_from_sysrdl.h"
#include "program_options.h"

using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: name_ - the name of the module 
// OUT: 
// RET: 
GenericCPU::GenericCPU(sc_module_name name_, uint32_t id_) : 
    GenericCPUBase(name_, id_)
{
    m_data.resize(ProgramOptions::GetInstance()->get_transfer_size() , 5);
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
   
   TreatPeripheral0();
   TreatPeripheral1();
   TreatPeripheral2();
   TreatPeripheral3();         
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
    uint64_t addr = MemoryMapBuilder::GetInstance()->GetAbsoluteAddress2(MEM0, 0); 
    Write(addr, &m_data[0], m_data.size() * sizeof(uint32_t));
//    printf("zzz size(%d)\n", m_data.size());
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
    uint64_t addr = MemoryMapBuilder::GetInstance()->GetAbsoluteAddress2(MEM1, 0); 
    Write(addr, &m_data[0], m_data.size() * sizeof(uint32_t));
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
    uint64_t addr = MemoryMapBuilder::GetInstance()->GetAbsoluteAddress2(MEM2, 0); 
    Write(addr, &m_data[0], m_data.size() * sizeof(uint32_t));
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
    uint64_t addr = MemoryMapBuilder::GetInstance()->GetAbsoluteAddress2(MEM3, 0); 
    Write(addr, &m_data[0], m_data.size() * sizeof(uint32_t));

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
        // read the result

        if (cntr++ > ProgramOptions::GetInstance()->get_nr_xfers()) 
        { 
            cout << "Test PASSED" << endl; 
            exit(0);
        }
    }
}
