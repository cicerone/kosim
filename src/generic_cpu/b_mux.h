/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_GC_GC_MUX_H
#define KOSIM_GC_GC_MUX_H

#include <stdint.h>
#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

//#include "memory_map_builder.h"


/////////////////////////////////////////////////////////////////////////////////////////////////
// BMux implemtents a generic blocking transport mux that connects many initiators with 
// one_TARGET
/////////////////////////////////////////////////////////////////////////////////////////////////

template<uint32_t N_INITIATORS>
class BMux: sc_module
{
public:
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_target_socket<BMux>*  mp_target_socket[N_INITIATORS];
  // Use tagged sockets to be able to distinguish incoming backward path calls
  tlm_utils::simple_initiator_socket_tagged<BMux>* mp_initiator_socket;

  SC_HAS_PROCESS(BMux);
  BMux(sc_module_name name_);
  ~BMux();

private:
  // FORWARD path methods 
  void b_transport( tlm::tlm_generic_payload& payload_, sc_time& delay_ );
  bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data_);
  uint32_t transport_dbg(tlm::tlm_generic_payload& payload_);

  // BACKWARD path methods 

  // Tagged backward DMI method
  void invalidate_direct_mem_ptr(int id, sc_dt::uint64 start_range_, sc_dt::uint64 end_range_);
  
  sc_mutex* mp_mutex;

};
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
template <uint32_t N_INITIATORS>
BMux<N_INITIATORS>::BMux(sc_module_name name_) : 
    sc_module(name_)
{

    char name[30];
     
    for (uint32_t i = 0; i < N_INITIATORS; i++)
    {  
        sprintf(name, "target_socket_%d", i);
        mp_target_socket[i] = new tlm_utils::simple_target_socket<BMux>(name);

        // Register callbacks for incoming interface method calls
        mp_target_socket[i]->register_b_transport(       this, &BMux::b_transport);
        mp_target_socket[i]->register_get_direct_mem_ptr(this, &BMux::get_direct_mem_ptr);
        mp_target_socket[i]->register_transport_dbg(     this, &BMux::transport_dbg);
    }
    
    {
        sprintf(name, "initiator_socket");
        mp_initiator_socket = new tlm_utils::simple_initiator_socket_tagged<BMux>(name);

        // Register callbacks for incoming interface method calls, including tags
        mp_initiator_socket->register_invalidate_direct_mem_ptr(this, &BMux::invalidate_direct_mem_ptr, 0);
        
        sprintf(name, "initiator_mutex");
        mp_mutex = new sc_mutex(name);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
template <uint32_t N_INITIATORS>
BMux<N_INITIATORS>::~BMux() 
{
    for (uint32_t i = 0; i < N_INITIATORS; i++)
    {  
        delete mp_target_socket[i];
    }
    
    delete mp_initiator_socket;
    delete mp_mutex;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// TLM-2 blocking transport method
// IN: 
// OUT: 
// RET: 
template<uint32_t N_INITIATORS>
void BMux<N_INITIATORS>::b_transport( tlm::tlm_generic_payload& payload_, sc_time& delay_ )
{
    // Forward transaction to appropriate target
    mp_mutex->lock();
    ( *mp_initiator_socket)->b_transport( payload_, delay_ );
    mp_mutex->unlock();
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// TLM-2 forward DMI method
// IN: 
// OUT: 
// RET: 
template<uint32_t N_INITIATORS>
bool BMux<N_INITIATORS>::get_direct_mem_ptr(tlm::tlm_generic_payload& payload_, tlm::tlm_dmi& dmi_data_)
{
    // Forward transaction to appropriate target
    mp_mutex->lock();
    bool status = ( *mp_initiator_socket)->get_direct_mem_ptr( payload_, dmi_data_ );
    mp_mutex->unlock();

    return status;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// TLM-2 debug transaction method
// IN: 
// OUT: 
// RET: 
template<uint32_t N_INITIATORS>
uint32_t BMux<N_INITIATORS>::transport_dbg(tlm::tlm_generic_payload& payload_ )
{
    uint32_t ret  = 0;
    // Forward debug transaction to appropriate target
    mp_mutex->lock();
    ret = ( *mp_initiator_socket)->transport_dbg( payload_ );
    mp_mutex->unlock();
    return ret;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
template<uint32_t N_INITIATORS>
void BMux<N_INITIATORS>::invalidate_direct_mem_ptr(int32_t id, sc_dt::uint64 start_range_, sc_dt::uint64 end_range_)
{
fprintf(stderr, "FIXME! Not Implemented!\n");
exit(1);
/*
    // Reconstruct address range in system memory map
    sc_dt::uint64 bw_start_range_ = MemoryMapBuilder::GetInstance()->GetAbsoluteAddress( id, start_range_ );
    sc_dt::uint64 bw_end_range_   = MemoryMapBuilder::GetInstance()->GetAbsoluteAddress( id, end_range_ );
    (*mp_target_socket)->invalidate_direct_mem_ptr(bw_start_range_, bw_end_range_);
*/    
}
#endif // KOSIM_GC_GC_MUX_H

