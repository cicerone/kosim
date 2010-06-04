/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/


#ifndef KOSIM_IPCA_INITIATOR_ADAPTER_H
#define KOSIM_IPCA_INITIATOR_ADAPTER_H


#define SC_INCLUDE_DYNAMIC_PROCESSES
#include "systemc.h"
#include "generic_cpu_base.h"

#include "target_sm.h"

class InitiatorAdapter : public GenericCPUBase 
{
public:

    SC_HAS_PROCESS(InitiatorAdapter);
    InitiatorAdapter(sc_module_name name_, uint32_t id_);
    ~InitiatorAdapter();

private: 
    void IRQThread();
    void DataThread();

    boost::interprocess::shared_memory_object m_shared_mem;
    TargetSharedMemory* mp_target_sm;

    const sc_time IRQ_RESOLUTION;

};


#endif // KOSIM_IPCA_INITIATOR_ADAPTER_H
