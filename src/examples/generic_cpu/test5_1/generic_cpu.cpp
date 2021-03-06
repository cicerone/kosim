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
    m_data_wr.resize(ProgramOptions::GetInstance()->get_transfer_size() , 5);
    m_data_rd.resize(ProgramOptions::GetInstance()->get_transfer_size() , 9);    
    m_data_wr[0] = 0;
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
   
   TreatPeripheral0();
   TreatPeripheral1();
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void 
GenericCPU::TreatPeripheral0()
{
//    fprintf(stderr, "%s\n", __PRETTY_FUNCTION__);
    sc_dt::uint64 addr = MemoryMapBuilder::GetInstance()->GetAbsoluteAddress2(MEM0, 0); 
    Write(addr, &m_data_wr[0], (m_data_wr.size()) * sizeof(uint32_t));
    Write(addr, &m_data_wr[0], (m_data_wr.size()) * sizeof(uint32_t));  
    Read(addr, &m_data_rd[0], m_data_rd.size() * sizeof(uint32_t));
    Read(addr, &m_data_rd[0], m_data_rd.size() * sizeof(uint32_t));
    Write(addr, &m_data_wr[0], (m_data_wr.size()) * sizeof(uint32_t));
    
    addr = MemoryMapBuilder::GetInstance()->GetAbsoluteAddress2(MEM0, 0);
    Write(addr, 7); // instruct to generate interrupt
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void 
GenericCPU::TreatPeripheral1()
{
//    Read(addr, &m_data_wr[0], m_data_wr.size() * sizeof(uint32_t));    
//    fprintf(stderr, "%s\n", __PRETTY_FUNCTION__);
    sc_dt::uint64 addr = MemoryMapBuilder::GetInstance()->GetAbsoluteAddress2(MEM1, 0); 
    Write(addr, &m_data_wr[0], (m_data_wr.size()) * sizeof(uint32_t));
    Write(addr, &m_data_wr[0], (m_data_wr.size()) * sizeof(uint32_t));
    Read(addr, &m_data_rd[0], m_data_rd.size() * sizeof(uint32_t));
    Read(addr, &m_data_rd[0], m_data_rd.size() * sizeof(uint32_t));
    Write(addr, &m_data_wr[0], (m_data_wr.size()) * sizeof(uint32_t));
        
    addr = MemoryMapBuilder::GetInstance()->GetAbsoluteAddress2(MEM1, 0);
    Write(addr, 7); // instruct to generate interrupt

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
    int32_t cntr[NUMBER_PERIPHERALS];
    for (int i = 0; i < NUMBER_PERIPHERALS; i++)
    {
        cntr[i] = 0;
    } 
    
    
    
    
    while(1)
    {
        uint32_t peripheral_id = m_irq.read(); //blocking read 
        
        bool is_exit = false;
        for (int i = 0; i < NUMBER_PERIPHERALS; i++)
        {
            if (cntr[i] < ProgramOptions::GetInstance()->get_nr_xfers()) { 
                break;
            }   
            else {
                if (i == NUMBER_PERIPHERALS - 1) {
                    is_exit = true;
                }
            }
        }
        if (is_exit) 
        {
            cout << "Test PASSED" << endl; 
            sc_stop();
            
        }
        
        
        if (peripheral_id < NUMBER_PERIPHERALS) 
        {
            if (cntr[peripheral_id] < ProgramOptions::GetInstance()->get_nr_xfers())
            {
                (this->*mv_program_peripheral[peripheral_id])();
                cntr[peripheral_id]++;
            }
        }

    }
}

