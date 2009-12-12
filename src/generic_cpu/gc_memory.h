/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosym@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_GC_GC_MEMORY_H
#define KOSIM_GC_GC_MEMORY_H


#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"


/////////////////////////////////////////////////////////////////////////////////////////////////
// Target module representing a simple memory
/////////////////////////////////////////////////////////////////////////////////////////////////
class GCMemory : public sc_module
{

public:
  SC_HAS_PROCESS(GCMemory);
  GCMemory(sc_module_name name_);
  ~GCMemory() {};
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_target_socket<GCMemory> socket;


  // TLM-2 blocking transport method
  void b_transport( tlm::tlm_generic_payload& payload_, sc_time& delay_ );
  // TLM-2 forward DMI method
  bool get_direct_mem_ptr(tlm::tlm_generic_payload& payload_ , tlm::tlm_dmi& dmi_data_ );
  // TLM-2 debug transaction method
  unsigned int transport_dbg(tlm::tlm_generic_payload& payload_ );

private:
  enum { SIZE = 256 };
  const sc_time LATENCY;

  int mem[SIZE];
  static unsigned int mem_nr;
};


#endif //KOSIM_GC_GC_MEMORY_H

