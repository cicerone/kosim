/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_GC_B_INITIATOR_H
#define KOSIM_GC_B_INITIATOR_H

#include <stdint.h>
#include <vector>

//#define SC_INCLUDE_DYNAMIC_PROCESSES defined in CMakeList.txt defined in CMakeList.txt
#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

// BInitiator module generating generic payload transactions

class BInitiator : public sc_module
{
public:
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_initiator_socket<BInitiator> socket;

  BInitiator(sc_module_name name_);
  virtual ~BInitiator();

  void     Write   (const sc_dt::uint64 addr_, uint32_t data_);
  uint32_t Read    (const sc_dt::uint64 addr_);
  void     DbgWrite(const sc_dt::uint64 addr_, uint32_t data_);
  uint32_t DbgRead (const sc_dt::uint64 addr_);
  
  void    Write   (const sc_dt::uint64 addr_, uint32_t* const p_data_, const uint32_t size_ = 4);
  void    Read    (const sc_dt::uint64 addr_, uint32_t* const p_data_, const uint32_t size_ = 4);
  void    DbgWrite(const sc_dt::uint64 addr_, uint32_t* const p_data_, const uint32_t size_ = 4);
  void    DbgRead (const sc_dt::uint64 addr_, uint32_t* const p_data_, const uint32_t size_ = 4);

protected:
  tlm::tlm_generic_payload* mp_payload;

private:
  virtual void InitSystem() = 0;

  // TLM-2 backward DMI method
  void invalidate_direct_mem_ptr(sc_dt::uint64 start_range_, sc_dt::uint64 end_range_);
  void CheckAddressAlignment(const uint32_t addr_);
  void CheckDataSize(const uint32_t size_);

  bool m_is_dmi_ptr_valid;
  tlm::tlm_dmi m_dmi_data;
  tlm::tlm_generic_payload* mp_dmi_payload;
  tlm::tlm_generic_payload* mp_dbg_payload;
};
#endif // KOSIM_GC_B_INITIATOR_H

