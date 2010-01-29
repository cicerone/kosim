/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_GC_GENERIC_CPU_BASE_H
#define KOSIM_GC_GENERIC_CPU_BASE_H

#include <stdint.h>
#include <vector>

#define SC_INCLUDE_DYNAMIC_PROCESSES
#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"
#include "b_initiator.h"

// GenericCPUBase module generating generic payload transactions

class GenericCPUBase : public BInitiator 
{
public:
  sc_fifo_in <uint32_t> m_irq ;

  GenericCPUBase(sc_module_name name_);
  virtual ~GenericCPUBase();

private:

};
#endif // KOSIM_GC_GENERIC_CPU_BASE_H

