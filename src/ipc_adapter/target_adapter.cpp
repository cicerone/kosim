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


#include "target_adapter.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;
using namespace boost::interprocess;

///////////////////////////////////////////////////////////////////////////////////////////////
// IN: 
// OUT: 
// RET: 
TargetAdapter::TargetAdapter(sc_module_name name_, uint32_t id_, uint32_t no_irq_) : 
    GCIPCTarget(name_, id_, no_irq_),
    mp_shared_mem(0),
    mp_mapped_region(0),
    mp_target_sm(0)
{
    SC_THREAD(IRQThread);
    SC_THREAD(DataThread);


    
    try
    {
        shared_memory_object::remove("ipc_adapter_shared_memory");
        mp_shared_mem = new shared_memory_object(create_only, "ipc_adapter_shared_memory", read_write);
        //Set size
        mp_shared_mem->truncate(sizeof(TargetSharedMemory));
        //Map the whole shared memory in this process
        mp_mapped_region = new mapped_region( *mp_shared_mem, read_write);
        //Get the address of the mapped region
        void* addr = mp_mapped_region->get_address();
        //Construct the shared structure in memory
        mp_target_sm = new (addr) TargetSharedMemory;
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
TargetAdapter::~TargetAdapter()
{
    delete mp_target_sm; // probably not necessary ???
    delete mp_mapped_region;
    delete mp_shared_mem;
    shared_memory_object::remove("ipc_adapter_shared_memory");
}

///////////////////////////////////////////////////////////////////////////////////////////////
// IN: 
// OUT: 
// RET: 
void TargetAdapter::IRQThread()
{
    while(1)
    {
        wait(1, SC_NS);
        scoped_lock<interprocess_mutex> lock(mp_target_sm->mutex_irq);
        if (!mp_target_sm->is_irq_consumed)
        {
            mv_irq[0]->write(mp_target_sm->irq_vector); 
            mp_target_sm->is_irq_consumed = true;
            mp_target_sm->cond_irq_consumed.notify_one();
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
// IN: 
// OUT: 
// RET: 
void TargetAdapter::DataThread()
{
    while (1)
    {
        wait(m_io_event);
        if ( mp_last_tlm_payload->get_command() == tlm::TLM_WRITE_COMMAND)
        {
            scoped_lock<interprocess_mutex> lock(mp_target_sm->mutex_wr);
            assert(TargetSharedMemory::BUFF_SIZE >= (mp_last_tlm_payload->get_data_length() >> 2));
            mp_target_sm->tlm_payload_wr.deep_copy_from(*mp_last_tlm_payload);
            mp_target_sm->is_buff_wr_full = true;
            if (mp_target_sm->is_buff_wr_full) {
                mp_target_sm->cond_buff_wr_empty.wait(lock);
            }
            mp_last_tlm_payload->update_original_from(mp_target_sm->tlm_payload_wr, false);

        }
        else if ( mp_last_tlm_payload->get_command() == tlm::TLM_READ_COMMAND)
        {
            scoped_lock<interprocess_mutex> lock(mp_target_sm->mutex_rd);
            mp_target_sm->is_buff_rd_empty = true;
            mp_target_sm->tlm_payload_rd.deep_copy_from(*mp_last_tlm_payload);
            if (mp_target_sm->is_buff_rd_empty) {
                mp_target_sm->cond_buff_rd_full.wait(lock);
            }
            mp_last_tlm_payload->update_original_from(mp_target_sm->tlm_payload_rd, false);
        }
    }
}

