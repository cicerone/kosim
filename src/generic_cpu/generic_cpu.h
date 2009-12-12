/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosym@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_GC_GENERIC_CPU_H
#define KOSIM_GC_GENERIC_CPU_H

#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

// GenericCPU module generating generic payload transactions

class GenericCPU : public sc_module
{
public:
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_initiator_socket<GenericCPU> socket;

  SC_HAS_PROCESS(GenericCPU);
  GenericCPU(sc_module_name name_);

private:
  void thread_process();

  // TLM-2 backward DMI method
  void invalidate_direct_mem_ptr(sc_dt::uint64 start_range_, sc_dt::uint64 end_range_);

  bool dmi_ptr_valid;
  tlm::tlm_dmi dmi_data;
};


#endif // KOSIM_GC_GENERIC_CPU_H

