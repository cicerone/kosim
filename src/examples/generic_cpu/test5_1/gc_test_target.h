/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_EX_GC_GC_TEST_TARGET_H
#define KOSIM_EX_GC_GC_TEST_TARGET_H

#include <stdint.h>

#define SC_INCLUDE_DYNAMIC_PROCESSES
#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"
#include "gc_target.h"

class MemoryMap;

/////////////////////////////////////////////////////////////////////////////////////////////////
// Target module representing a simple memory
/////////////////////////////////////////////////////////////////////////////////////////////////
class GCTestTarget : public GCTarget 
{

public:
  SC_HAS_PROCESS(GCTestTarget);
  GCTestTarget(sc_module_name name_, uint32_t id_, uint32_t no_irq_ = 1);
  ~GCTestTarget() {};

private:
  void TReadWrite();
  void TProcess();
  sc_event m_ev_process;

};


#endif // KOSIM_EX_GC_GC_TEST_TARGET_H

