/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_GC_GC_ROUTER_H
#define KOSIM_GC_GC_ROUTER_H

#include <stdint.h>
#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

#include "memory_map_builder.h"


/////////////////////////////////////////////////////////////////////////////////////////////////
// BRouter implemtents a generic blocking transport router that connects one initiator with 
// N_TARGETS
/////////////////////////////////////////////////////////////////////////////////////////////////

template<uint32_t N_INITIATORS, uint32_t N_TARGETS>
class BRouter: sc_module
{
public:
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_target_socket<BRouter>*  mp_target_socket[N_INITIATORS];
  // Use tagged sockets to be able to distinguish incoming backward path calls
  tlm_utils::simple_initiator_socket_tagged<BRouter>* mp_initiator_socket[N_TARGETS];

  SC_HAS_PROCESS(BRouter);
  BRouter(sc_module_name name_);
  ~BRouter();

private:
  // FORWARD path methods 
  void b_transport( tlm::tlm_generic_payload& payload_, sc_time& delay_ );
  bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data_);
  uint32_t transport_dbg(tlm::tlm_generic_payload& paylaod_);

  // BACKWARD path methods 

  // Tagged backward DMI method
  void invalidate_direct_mem_ptr(int id, sc_dt::uint64 start_range_, sc_dt::uint64 end_range_);
  
  sc_mutex* mp_mutex[N_TARGETS];

};
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
template <uint32_t N_INITIATORS, uint32_t N_TARGETS>
BRouter<N_INITIATORS, N_TARGETS>::BRouter(sc_module_name name_) : 
    sc_module(name_)
{

    char name[30];
     
    for (uint32_t i = 0; i < N_INITIATORS; i++)
    {  
        sprintf(name, "target_socket_%d", i);
        mp_target_socket[i] = new tlm_utils::simple_target_socket<BRouter>(name);

        // Register callbacks for incoming interface method calls
        mp_target_socket[i]->register_b_transport(       this, &BRouter::b_transport);
        mp_target_socket[i]->register_get_direct_mem_ptr(this, &BRouter::get_direct_mem_ptr);
        mp_target_socket[i]->register_transport_dbg(     this, &BRouter::transport_dbg);
    }
    
    for (uint32_t i = 0; i < N_TARGETS; i++)
    {
        sprintf(name, "initiator_socket_%d", i);
        mp_initiator_socket[i] = new tlm_utils::simple_initiator_socket_tagged<BRouter>(name);

        // Register callbacks for incoming interface method calls, including tags
        mp_initiator_socket[i]->register_invalidate_direct_mem_ptr(this, &BRouter::invalidate_direct_mem_ptr, i);
        
        sprintf(name, "initiator_mutex_%d", i);
        mp_mutex[i] = new sc_mutex(name);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
template <uint32_t N_INITIATORS, uint32_t N_TARGETS>
BRouter<N_INITIATORS, N_TARGETS>::~BRouter() 
{
    for (uint32_t i = 0; i < N_INITIATORS; i++)
    {  
        delete mp_target_socket[i];
    }
    
    for (uint32_t i = 0; i < N_TARGETS; i++) {
        delete mp_initiator_socket[i];
        delete mp_mutex[i];
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// TLM-2 blocking transport method
// IN: 
// OUT: 
// RET: 
template<uint32_t N_INITIATORS, uint32_t N_TARGETS>
void BRouter<N_INITIATORS, N_TARGETS>::b_transport( tlm::tlm_generic_payload& payload_, sc_time& delay_ )
{
    sc_dt::uint64 address = payload_.get_address();
    sc_dt::uint64 masked_address;
    uint32_t target_nr = MemoryMapBuilder::GetInstance()->FindTarget(address, &masked_address);

    // Modify address within transaction
    payload_.set_address( masked_address );

    // Forward transaction to appropriate target
    mp_mutex[target_nr]->lock();
    ( *mp_initiator_socket[target_nr] )->b_transport( payload_, delay_ );
    mp_mutex[target_nr]->unlock();
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// TLM-2 forward DMI method
// IN: 
// OUT: 
// RET: 
template<uint32_t N_INITIATORS, uint32_t N_TARGETS>
bool BRouter<N_INITIATORS, N_TARGETS>::get_direct_mem_ptr(tlm::tlm_generic_payload& payload_, tlm::tlm_dmi& dmi_data_)
{
    sc_dt::uint64 masked_address;
    uint32_t target_nr = MemoryMapBuilder::GetInstance()->FindTarget(payload_.get_address(), &masked_address);

    payload_.set_address( masked_address );

    mp_mutex[target_nr]->lock();
    bool status = ( *mp_initiator_socket[target_nr] )->get_direct_mem_ptr( payload_, dmi_data_ );
    mp_mutex[target_nr]->unlock();

    // Calculate DMI address of target in system address space
    dmi_data_.set_start_address( MemoryMapBuilder::GetInstance()->GetAbsoluteAddress( target_nr, dmi_data_.get_start_address() ));
    dmi_data_.set_end_address  ( MemoryMapBuilder::GetInstance()->GetAbsoluteAddress( target_nr, dmi_data_.get_end_address() ));
    

    return status;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// TLM-2 debug transaction method
// IN: 
// OUT: 
// RET: 
template<uint32_t N_INITIATORS, uint32_t N_TARGETS>
uint32_t BRouter<N_INITIATORS, N_TARGETS>::transport_dbg(tlm::tlm_generic_payload& payload_ )
{
    uint32_t ret = 0;
    sc_dt::uint64 masked_address;
    uint32_t target_nr = MemoryMapBuilder::GetInstance()->FindTarget(payload_.get_address(), &masked_address);
    payload_.set_address( masked_address );

    // Forward debug transaction to appropriate target
    mp_mutex[target_nr]->lock();
    ret = ( *mp_initiator_socket[target_nr] )->transport_dbg( payload_ );
    mp_mutex[target_nr]->unlock();
    return ret;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
template<uint32_t N_INITIATORS, uint32_t N_TARGETS>
void BRouter<N_INITIATORS, N_TARGETS>::invalidate_direct_mem_ptr(int32_t id, sc_dt::uint64 start_range_, sc_dt::uint64 end_range_)
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
#endif // KOSIM_GC_GC_ROUTER_H

