/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_GC_B_TARGET_H
#define KOSIM_GC_B_TARGET_H

#include <stdint.h>

#define SC_INCLUDE_DYNAMIC_PROCESSES
#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"
#include "memory_map.h"


/////////////////////////////////////////////////////////////////////////////////////////////////
// Target module representing a simple memory
/////////////////////////////////////////////////////////////////////////////////////////////////
class BTarget : public sc_module
{

public:
  BTarget(sc_module_name name_, uint32_t id_);
  virtual ~BTarget() {};
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_target_socket<BTarget> socket;


  // TLM-2 blocking transport method
  void b_transport( tlm::tlm_generic_payload& payload_, sc_time& delay_ );
  // TLM-2 forward DMI method
  bool get_direct_mem_ptr(tlm::tlm_generic_payload& payload_ , tlm::tlm_dmi& dmi_data_ );
  // TLM-2 debug transaction method
  uint32_t transport_dbg(tlm::tlm_generic_payload& payload_ );

protected:
  const sc_time DMI_LATENCY;
  MemoryMap* mp_memory_map;
  uint32_t m_id;
  sc_event m_io_event;
private:
  
};


#endif //KOSIM_GC_B_TARGET_H

