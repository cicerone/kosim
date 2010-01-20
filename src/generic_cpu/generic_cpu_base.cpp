/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#include "generic_cpu.h"
#include "memory_map_builder.h"
#include "gen_from_sysrdl.h"

using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: name_ - the name of the module 
// OUT: 
// RET: 
GenericCPUBase::GenericCPUBase(sc_module_name name_) : 
    sc_module(name_),
    socket("socket"),  // Construct and name socket
    m_is_dmi_ptr_valid(false)
{
    // Register callbacks for incoming interface method calls
    socket.register_invalidate_direct_mem_ptr(this, &GenericCPUBase::invalidate_direct_mem_ptr);

//    SC_THREAD(STMain);

    mp_payload     = new tlm::tlm_generic_payload;
    mp_dmi_payload = new tlm::tlm_generic_payload;
    mp_dbg_payload = new tlm::tlm_generic_payload;
    
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
GenericCPUBase::~GenericCPUBase()
{
    delete mp_payload;
    delete mp_dmi_payload;
    delete mp_dbg_payload;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// Uses TLM2 blocking interface to write 32 bit words
// IN:  addr_ - the address of the 32 bit word to be written
//      data_ - the data to be written
// OUT: 
// RET: 
void
GenericCPUBase::Write32BitWord   (const uint64_t addr_, int32_t data_)
{
    CheckAddressAlignment(addr_);
    mp_payload->set_command        ( tlm::TLM_WRITE_COMMAND);
    mp_payload->set_address        ( addr_ );
    mp_payload->set_data_ptr       ( reinterpret_cast<unsigned char*>(&data_) );
    mp_payload->set_data_length    ( sizeof(int32_t) );
    mp_payload->set_streaming_width( sizeof(int32_t) );
    mp_payload->set_byte_enable_ptr( 0               ); // 0 indicates unused
    mp_payload->set_dmi_allowed    ( false           ); // mandatory initial value
    mp_payload->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // mandatory initial value

    sc_time delay = sc_time(0, SC_NS);
    socket->b_transport( *mp_payload, delay );  // Blocking transport call

    if ( mp_payload->is_response_error() ) {
        string error("Error from b_transport, response status = ");
        error += mp_payload->get_response_string();
        SC_REPORT_ERROR("TLM-2", error.c_str());
    }
    cout << "trans = {  'W' , " << hex << addr_ << " } , data = " << hex << data_ << " at time " << sc_time_stamp() << endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// Uses TLM2 blocking interface to read 32 bit words
// IN:  addr_ - the address of the word to be read
// OUT: 
// RET:  the read value
int32_t
GenericCPUBase::Read32BitWord    (const uint64_t addr_)
{
    int32_t read_data = 0;
    CheckAddressAlignment(addr_);
    mp_payload->set_command        ( tlm::TLM_READ_COMMAND);
    mp_payload->set_address        ( addr_ );
    mp_payload->set_data_ptr       ( reinterpret_cast<unsigned char*>(&read_data) );
    mp_payload->set_data_length    ( sizeof(int32_t) );
    mp_payload->set_streaming_width( sizeof(int32_t) );
    mp_payload->set_byte_enable_ptr( 0               ); // 0 indicates unused
    mp_payload->set_dmi_allowed    ( false           ); // mandatory initial value
    mp_payload->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // mandatory initial value

    sc_time delay = sc_time(0, SC_NS);
    socket->b_transport( *mp_payload, delay );  // Blocking transport call

    if ( mp_payload->is_response_error() ) {
        string error("Error from b_transport, response status = ");
        error += mp_payload->get_response_string();
        SC_REPORT_ERROR("TLM-2", error.c_str());
    }
    return read_data;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// Uses dbg interface to write 32 bit words
// IN:  addr_ - the address of the 32 bit word to be written
//      data_ - the data to be written
// OUT: 
// RET: 
void    
GenericCPUBase::DbgWrite32BitWord(const uint64_t addr_, int32_t data_)
{
    CheckAddressAlignment(addr_);
    uint32_t xfer_size = sizeof(int32_t);
    mp_dbg_payload->set_address(addr_);
    mp_dbg_payload->set_write();
    mp_dbg_payload->set_data_length(xfer_size);

//    unsigned char* data = new unsigned char[256];
    mp_dbg_payload->set_data_ptr(reinterpret_cast<uint8_t*>(&data_));

    uint32_t number_bytes_wr = socket->transport_dbg( *mp_dbg_payload );
    if (number_bytes_wr != xfer_size) {
        fprintf(stderr, "%s transaction was not performed properly!\n", __PRETTY_FUNCTION__);
        exit(1);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// Uses dbg interface to read 32 bit words
// IN:  addr_ - the address of the word to be read
// OUT: 
// RET: the read value   
int32_t 
GenericCPUBase::DbgRead32BitWord(const uint64_t addr_)
{
    CheckAddressAlignment(addr_);
    uint32_t xfer_size = sizeof(int32_t);
    mp_dbg_payload->set_address(addr_);
    mp_dbg_payload->set_read();
    mp_dbg_payload->set_data_length(xfer_size);

    int32_t read_data = 0;
    mp_dbg_payload->set_data_ptr(reinterpret_cast<uint8_t*>(&read_data));

    uint32_t number_bytes_rd = socket->transport_dbg( *mp_dbg_payload );
    if (number_bytes_rd != xfer_size) {
        fprintf(stderr, "%s transaction was not performed properly!\n", __PRETTY_FUNCTION__);
        exit(1);
    }
    return read_data;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// TLM-2 backward DMI method, invalidates dmi access
// IN:  start_range_ - the start addr of the memory space that is dmi invalidated 
//      end_range_   - the end addr of the memory space that is dmi invalidated 
// OUT: 
// RET: 
void 
GenericCPUBase::invalidate_direct_mem_ptr(sc_dt::uint64 start_range_, sc_dt::uint64 end_range_)
{
    // Ignore range and invalidate all DMI pointers regardless
    m_is_dmi_ptr_valid = false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// Exits with error if the address is not 32 bit aligned
// IN:  addr_  - the address that must be 32 bit aligned 
// OUT: 
// RET: 
void
GenericCPUBase::CheckAddressAlignment(const uint32_t addr_)
{
    if (addr_ % sizeof(int32_t) != 0) {
        fprintf(stderr, "ERROR! address must be multiple of 4, addr(0x%x)!\n", addr_);
        exit(1);
    }
} 

