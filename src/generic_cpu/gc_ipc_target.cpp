/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#include "gc_ipc_target.h"
//#include "memory_map_builder.h"
//#include "memory_map.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
GCIPCTarget::GCIPCTarget(sc_module_name name_, uint32_t id_, uint32_t no_irq_) : 
    BIPCTarget(name_, id_),
    m_no_irq(no_irq_)
{
    for (uint32_t i = 0; i < no_irq_; i++)
    {
        sc_fifo_out<uint32_t>* p_irq = new sc_fifo_out<uint32_t>;
        mv_irq.push_back(p_irq);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
GCIPCTarget::~GCIPCTarget()
{
    mv_irq.clear();
}

