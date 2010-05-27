/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#include "b_target.h"
#include "memory_map_builder.h"
#include "memory_map.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;


// BTarget - blocking target (the target that used TLM2 blocking interface)


/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
BTarget::BTarget(sc_module_name name_, uint32_t id_) : 
    sc_module(name_),
    socket("gc_target_socket"), 
    DMI_LATENCY(10, SC_NS),
    mp_memory_map(0),
    m_id(id_)
{
    // Register callbacks for incoming interface method calls
    socket.register_b_transport(       this, &BTarget::b_transport);
    socket.register_get_direct_mem_ptr(this, &BTarget::get_direct_mem_ptr);
    socket.register_transport_dbg(     this, &BTarget::transport_dbg);

    mp_memory_map = MemoryMapBuilder::GetInstance()->GetMemoryMap(m_id);
    
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// TLM-2 blocking transport method
// IN: 
// OUT: 
// RET: 
void 
BTarget::b_transport( tlm::tlm_generic_payload& payload_, sc_time& delay_ )
{
    tlm::tlm_command command   = payload_.get_command();
//    uint64_t      mem_address  = payload_.get_address() / sizeof(mem[0]);
    uint64_t      mem_address  = payload_.get_address();
    uint8_t*      data_ptr     = payload_.get_data_ptr();
    uint32_t      data_length  = payload_.get_data_length();
    uint8_t*      byte_enable  = payload_.get_byte_enable_ptr();
    uint32_t      stream_width = payload_.get_streaming_width();

    // Generate the appropriate error response
    if (mem_address >= mp_memory_map->get_memory_space()) {
      payload_.set_response_status( tlm::TLM_ADDRESS_ERROR_RESPONSE );
      return;
    }
    if (byte_enable != 0) {
      payload_.set_response_status( tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE );
      return;
    }
//   if (data_length > sizeof(uint32_t) || stream_width < data_length) {
//     payload_.set_response_status( tlm::TLM_BURST_ERROR_RESPONSE );
//     return;
//   }
    
//#define IGNORE_RDL    
#ifdef IGNORE_RDL    
    if ( command == tlm::TLM_READ_COMMAND ) {
        memcpy(data_ptr, mp_memory_map->GetPhysicalAddress(mem_address), data_length);
    }
    else if ( command == tlm::TLM_WRITE_COMMAND ) {
         memcpy(mp_memory_map->GetPhysicalAddress(mem_address), data_ptr, data_length);
    }
#else    
    uint64_t hw_resource_id = mem_address >> 2;
    //NOTE: Here is where we "force" registers to be first and no gap between memory and registers
    if (hw_resource_id < mp_memory_map->get_number_regs()) // the hw_resource_id points to a register
    {
        if (data_length != sizeof(uint32_t)) {
            //NOTE: to not make extra computations of addresses all the registers MUST be accesseed using one word read/write methods
            fprintf(stderr, "FATAL! Try to use a block read/write of size(%d) bytes to read/write registers!\n", data_length);
            exit(1);
        }
        uint32_t data_val = 0;
        if ( command == tlm::TLM_READ_COMMAND ) {
            data_val = mp_memory_map->ReadSwRDL(hw_resource_id);
            memcpy(data_ptr, &data_val, sizeof(uint32_t));
        }
        else if ( command == tlm::TLM_WRITE_COMMAND ) {
            memcpy(&data_val, data_ptr, data_length);
            mp_memory_map->WriteSwRDL(hw_resource_id, data_val);
        }
    }
    else
    {  
        if ( command == tlm::TLM_READ_COMMAND ) {
            memcpy(data_ptr, mp_memory_map->GetPhysicalAddress(mem_address), data_length);
        }
        else if ( command == tlm::TLM_WRITE_COMMAND ) {
            memcpy(mp_memory_map->GetPhysicalAddress(mem_address), data_ptr, data_length);
        }
    }
#endif //  IGNORE_RDL
  
    // Set DMI hint to indicated that DMI is supported
    payload_.set_dmi_allowed(true);

    // Obliged to set response status to indicate successful completion
    payload_.set_response_status( tlm::TLM_OK_RESPONSE );
    
    m_io_event.notify();
    wait(delay_);
    delay_ = SC_ZERO_TIME;

}
/////////////////////////////////////////////////////////////////////////////////////////////////
// TLM-2 forward DMI method
// IN: 
// OUT: 
// RET: 
bool 
BTarget::get_direct_mem_ptr(tlm::tlm_generic_payload& payload_, tlm::tlm_dmi& dmi_data_)
{
/*
    // Permit read and write access
    dmi_data_.allow_read_write();

    // Set other details of DMI region
    dmi_data_.set_dmi_ptr( reinterpret_cast<unsigned char*>( &mem[0] ) );
    dmi_data_.set_start_address( 0 );
    dmi_data_.set_end_address( SIZE * sizeof(mem[0]) - 1 );
    dmi_data_.set_read_latency( DMI_LATENCY );
    dmi_data_.set_write_latency( DMI_LATENCY );
    return true;
*/
    return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// TLM-2 debug transaction method
// IN: 
// OUT: 
// RET: 
unsigned int 
BTarget::transport_dbg(tlm::tlm_generic_payload& payload_)
{
    tlm::tlm_command command = payload_.get_command();
    uint64_t     mem_address = payload_.get_address();
    uint8_t*     data_ptr    = payload_.get_data_ptr();
    uint32_t     data_length = payload_.get_data_length();

    // Calculate the number of bytes to be actually copied
    uint64_t  length_to_end = mp_memory_map->get_memory_space() - mem_address;
    uint64_t  num_bytes = data_length < length_to_end ? data_length : length_to_end ;
    if ( command == tlm::TLM_READ_COMMAND ) {
        memcpy(data_ptr, mp_memory_map->GetPhysicalAddress(mem_address), data_length);
    }
    else if ( command == tlm::TLM_WRITE_COMMAND ) {
        memcpy(mp_memory_map->GetPhysicalAddress(mem_address), data_ptr, data_length);
    }
    return num_bytes;
}
