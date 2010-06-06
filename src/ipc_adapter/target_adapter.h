/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/


#ifndef KOSIM_IPCA_TARGET_ADAPTER_H
#define KOSIM_IPCA_TARGET_ADAPTER_H


#define SC_INCLUDE_DYNAMIC_PROCESSES
#include "systemc.h"
#include "gc_ipc_target.h"

#include "target_sm.h"

class TargetAdapter : public GCIPCTarget 
{
public:

    SC_HAS_PROCESS(TargetAdapter);
    TargetAdapter(sc_module_name name_, uint32_t id_, uint32_t no_irq_ = 1);
    ~TargetAdapter();

private: 
    void IRQThread();
    void DataThread();

    boost::interprocess::shared_memory_object* mp_shared_mem;
    boost::interprocess::mapped_region* mp_mapped_region; 
    TargetSharedMemory* mp_target_sm;

    const sc_time IRQ_RESOLUTION;

};


#endif // KOSIM_IPCA_TARGET_ADAPTER_H
