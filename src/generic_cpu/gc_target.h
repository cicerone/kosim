/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_GC_GC_TARGET_H
#define KOSIM_GC_GC_TARGET_H

#include <stdint.h>

#define SC_INCLUDE_DYNAMIC_PROCESSES
#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"
#include "memory_map.h"
#include "b_target.h"


/////////////////////////////////////////////////////////////////////////////////////////////////
// Target module representing a simple memory
/////////////////////////////////////////////////////////////////////////////////////////////////
class GCTarget : public BTarget 
{

public:
  GCTarget(sc_module_name name_, uint32_t id_);
  virtual ~GCTarget() {};
  sc_fifo_out<uint32_t> m_irq ;


protected:
private:
};


#endif //KOSIM_GC_GC_TARGET_H

