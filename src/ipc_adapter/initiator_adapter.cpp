/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>


#include "initiator_adapter.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

using namespace boost::interprocess;

///////////////////////////////////////////////////////////////////////////////////////////////
// IN: 
// OUT: 
// RET: 
InitiatorAdapter::InitiatorAdapter(sc_module_name name_, uint32_t id_) : 
    GenericCPUBase(name_, id_),
    mp_shared_mem(0),
    mp_mapped_region(0),
    mp_target_sm(0)
{
    SC_THREAD(IRQThread);
    SC_THREAD(DataThread);


    try
    {
//        shared_memory_object::remove("ipc_adapter_shared_memory");
        mp_shared_mem = new shared_memory_object(open_only, "ipc_adapter_shared_memory", read_write);

        //Map the whole shared memory in this process
        mp_mapped_region = new mapped_region( *mp_shared_mem, read_write);
        //Get the address of the mapped region
        void* addr = mp_mapped_region->get_address();
        //Construct the shared structure in memory
        mp_target_sm = static_cast< TargetSharedMemory* > (addr) ;
    }
    catch (interprocess_exception &ex) 
    {
        shared_memory_object::remove("ipc_adapter_shared_memory");
        std::cout << ex.what() << std::endl;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
// IN: 
// OUT: 
// RET: 
InitiatorAdapter::~InitiatorAdapter()
{
    delete mp_shared_mem;
    shared_memory_object::remove("ipc_adapter_shared_memory");
}
///////////////////////////////////////////////////////////////////////////////////////////////
// IN: 
// OUT: 
// RET: 
void InitiatorAdapter::InitSystem()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////
// IN: 
// OUT: 
// RET: 
void InitiatorAdapter::IRQThread()
{
    while(1)
    {
        uint32_t irq_vector = m_irq.read(); //blocking read
        scoped_lock<interprocess_mutex> lock(mp_target_sm->mutex_irq);
        mp_target_sm->irq_vector = irq_vector; 
        mp_target_sm->is_irq_consumed = false;

        if (!mp_target_sm->is_irq_consumed) {
            mp_target_sm->cond_irq_consumed.wait(lock);
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
// IN: 
// OUT: 
// RET: 
void InitiatorAdapter::DataThread()
{
    while (1)
    {
        wait(10, SC_NS);
        {
            scoped_lock<interprocess_mutex> lock(mp_target_sm->mutex_wr);
            if (mp_target_sm->is_buff_wr_full) 
            {
                Write(mp_target_sm->tlm_payload_wr.get_address(), 
                      &mp_target_sm->buff_wr[0], 
                      mp_target_sm->tlm_payload_wr.get_data_length());

                mp_target_sm->is_buff_wr_full = false;
                mp_target_sm->tlm_payload_wr.update_original_from(*mp_payload, false);
                mp_target_sm->cond_buff_wr_empty.notify_one();
            }
        }
        {
            scoped_lock<interprocess_mutex> lock(mp_target_sm->mutex_rd);
            if (mp_target_sm->is_buff_rd_empty) 
            {
                Read(mp_target_sm->tlm_payload_rd.get_address(), 
                     &mp_target_sm->buff_rd[0], 
                     mp_target_sm->tlm_payload_rd.get_data_length());
                
                mp_target_sm->is_buff_rd_empty = false;
                mp_target_sm->cond_buff_rd_full.notify_one();
            }
        }
    }
}

