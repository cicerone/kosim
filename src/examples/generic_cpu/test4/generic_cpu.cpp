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
GenericCPU::GenericCPU(sc_module_name name_, uint32_t id_) : 
    GenericCPUBase(name_, id_)
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

   TreatPeripheral0(); 
   TreatPeripheral1();
   TreatPeripheral2();

}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void 
GenericCPU::TreatPeripheral0()
{
    if (m_id == 0)
    {
        cout <<__PRETTY_FUNCTION__  << ": time = " << sc_time_stamp() << endl;
        Write(0x00, 1);
        Write(0x04, 2);
    }   
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void 
GenericCPU::TreatPeripheral1()
{
    if (m_id == 0)
    {
        cout <<__PRETTY_FUNCTION__  << ": time = " << sc_time_stamp() << endl;
        Write(0x100, 3);
        Write(0x104, 4);
    }
    else if (m_id == 1)
    {
        cout <<__PRETTY_FUNCTION__  << ": time = " << sc_time_stamp() << endl;
        Write(0x108, 5);
        Write(0x10c, 6);
    }    
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void 
GenericCPU::TreatPeripheral2()
{
    if (m_id == 1)
    {
        cout <<__PRETTY_FUNCTION__  << ": time = " << sc_time_stamp() << endl;
        Write(0x200, 7);
        Write(0x204, 8);
    }
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

        if (cntr++ > 100000) { cout << "Test PASSED" << endl; sc_stop();}
    }
}
