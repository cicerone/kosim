/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosym@kotys.biz 
===============================================================================================*/

#include "gc_memory.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;


unsigned int GCMemory::mem_nr = 0;
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
GCMemory::GCMemory(sc_module_name name_) : 
    sc_module(name_),
    socket("gc_memory_socket"), 
    LATENCY(10, SC_NS)
{
    // Register callbacks for incoming interface method calls
    socket.register_b_transport(       this, &GCMemory::b_transport);
    socket.register_get_direct_mem_ptr(this, &GCMemory::get_direct_mem_ptr);
    socket.register_transport_dbg(     this, &GCMemory::transport_dbg);

    for (int32_t i = 0; i < SIZE; i++)
      mem[i] = 0xcccccccc;

    ++mem_nr;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// TLM-2 blocking transport method
// IN: 
// OUT: 
// RET: 
void 
GCMemory::b_transport( tlm::tlm_generic_payload& payload_, sc_time& delay_ )
{
    tlm::tlm_command command   = payload_.get_command();
    uint64_t      mem_address  = payload_.get_address() / sizeof(mem[0]);
    uint8_t*      data_ptr     = payload_.get_data_ptr();
    uint32_t      data_length  = payload_.get_data_length();
    uint8_t*      byte_enable  = payload_.get_byte_enable_ptr();
    uint32_t      stream_width = payload_.get_streaming_width();


    // Generate the appropriate error response
    if (mem_address >= SIZE) {
      payload_.set_response_status( tlm::TLM_ADDRESS_ERROR_RESPONSE );
      return;
    }
    if (byte_enable != 0) {
      payload_.set_response_status( tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE );
      return;
    }
    if (data_length > sizeof(mem[0]) || stream_width < data_length) {
      payload_.set_response_status( tlm::TLM_BURST_ERROR_RESPONSE );
      return;
    }

    wait(delay_);
    delay_ = SC_ZERO_TIME;

    // Obliged to implement read and write commands
    if ( command == tlm::TLM_READ_COMMAND )
      memcpy(data_ptr, &mem[mem_address], data_length);
    else if ( command == tlm::TLM_WRITE_COMMAND )
      memcpy(&mem[mem_address], data_ptr, data_length);

    // Set DMI hint to indicated that DMI is supported
    payload_.set_dmi_allowed(true);

    // Obliged to set response status to indicate successful completion
    payload_.set_response_status( tlm::TLM_OK_RESPONSE );
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// TLM-2 forward DMI method
// IN: 
// OUT: 
// RET: 
bool 
GCMemory::get_direct_mem_ptr(tlm::tlm_generic_payload& payload_, tlm::tlm_dmi& dmi_data_)
{
    // Permit read and write access
    dmi_data_.allow_read_write();

    // Set other details of DMI region
    dmi_data_.set_dmi_ptr( reinterpret_cast<unsigned char*>( &mem[0] ) );
    dmi_data_.set_start_address( 0 );
    dmi_data_.set_end_address( SIZE * sizeof(mem[0]) - 1 );
    dmi_data_.set_read_latency( LATENCY );
    dmi_data_.set_write_latency( LATENCY );

    return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// TLM-2 debug transaction method
// IN: 
// OUT: 
// RET: 
unsigned int 
GCMemory::transport_dbg(tlm::tlm_generic_payload& payload_)
{
    tlm::tlm_command command = payload_.get_command();
    uint64_t     mem_address = payload_.get_address() / sizeof(mem[0]);
    uint8_t*     data_ptr    = payload_.get_data_ptr();
    uint32_t     data_length = payload_.get_data_length();

    // Calculate the number of bytes to be actually copied
    uint32_t  num_bytes = (data_length < (SIZE - mem_address) * sizeof(mem[0])) ? data_length : (SIZE - mem_address) * sizeof(mem[0]);

    if ( command == tlm::TLM_READ_COMMAND )
      memcpy(data_ptr, &mem[mem_address], num_bytes);
    else if ( command == tlm::TLM_WRITE_COMMAND )
      memcpy(&mem[mem_address], data_ptr, num_bytes);

    return num_bytes;
}

