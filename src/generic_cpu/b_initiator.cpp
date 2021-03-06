/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#include "b_initiator.h"
//#include "memory_map_builder.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: name_ - the name of the module 
// OUT: 
// RET: 
BInitiator::BInitiator(sc_module_name name_) : 
    sc_module(name_),
    socket("socket"),  // Construct and name socket
    m_is_dmi_ptr_valid(false)
{
    // Register callbacks for incoming interface method calls
    socket.register_invalidate_direct_mem_ptr(this, &BInitiator::invalidate_direct_mem_ptr);

    mp_payload     = new tlm::tlm_generic_payload;
    mp_dmi_payload = new tlm::tlm_generic_payload;
    mp_dbg_payload = new tlm::tlm_generic_payload;
    
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
BInitiator::~BInitiator()
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
BInitiator::Write   (const sc_dt::uint64 addr_, uint32_t data_)
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
//    cout << "trans = {  'W' , " << hex << addr_ << " } , data = " << hex << data_ << " at time " << sc_time_stamp() << endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// Uses TLM2 blocking interface to read 32 bit words
// IN:  addr_ - the address of the word to be read
// OUT: 
// RET:  the read value
uint32_t
BInitiator::Read    (const sc_dt::uint64 addr_)
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
BInitiator::DbgWrite(const sc_dt::uint64 addr_, uint32_t data_)
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
uint32_t 
BInitiator::DbgRead(const sc_dt::uint64 addr_)
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
//
// IN:  addr_    - address to write data to
//      p_data_  - reference to chunck of data to be written 
//      size_    - size of chunk of data in bytes 
// OUT: 
// RET:
void 
BInitiator::Write   (const sc_dt::uint64 addr_, uint32_t* const p_data_, const uint32_t size_)
{
    CheckAddressAlignment(addr_);
    CheckDataSize( size_);
    mp_payload->set_command        ( tlm::TLM_WRITE_COMMAND);
    mp_payload->set_address        ( addr_ );
    mp_payload->set_data_ptr       ( reinterpret_cast<uint8_t*>(p_data_) );
    mp_payload->set_data_length    ( size_ );
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
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN:  addr_    - address to read data from 
//      p_data_  - reference to where to store the data 
//      size_    - size of chunk of data in bytes  
// OUT: 
// RET:
void 
BInitiator::Read    (const sc_dt::uint64 addr_,       uint32_t* const p_data_, const uint32_t size_)
{
    CheckAddressAlignment(addr_);
    CheckDataSize( size_);
    mp_payload->set_command        ( tlm::TLM_READ_COMMAND);
    mp_payload->set_address        ( addr_ );
    mp_payload->set_data_ptr       ( reinterpret_cast<uint8_t*>(p_data_) );
    mp_payload->set_data_length    ( size_ );
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
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN:  addr_    - address to write data to
//      p_data_  - reference to chunck of data to be written 
//      size_    - size of chunk of data in bytes 
// OUT: 
// RET:
void 
BInitiator::DbgWrite(const sc_dt::uint64 addr_, uint32_t* const p_data_, const uint32_t size_)
{
    CheckAddressAlignment(addr_);
    CheckDataSize( size_);
    mp_dbg_payload->set_address(addr_);
    mp_dbg_payload->set_write();
    mp_dbg_payload->set_data_length(size_);

//    unsigned char* data = new unsigned char[256];
    mp_dbg_payload->set_data_ptr(reinterpret_cast<uint8_t*>(p_data_));

    uint32_t number_bytes_wr = socket->transport_dbg( *mp_dbg_payload );
    if (number_bytes_wr != size_) {
        fprintf(stderr, "%s transaction was not performed properly!\n", __PRETTY_FUNCTION__);
        exit(1);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN:  addr_    - address to read data from 
//      p_data_  - reference to where to store the data 
//      size_    - size of chunk of data in bytes  
// OUT: 
// RET:
void 
BInitiator::DbgRead (const sc_dt::uint64 addr_,       uint32_t* const p_data_, const uint32_t size_)
{
    CheckAddressAlignment(addr_);
    CheckDataSize( size_);
    mp_dbg_payload->set_address(addr_);
    mp_dbg_payload->set_read();
    mp_dbg_payload->set_data_length(size_);

    mp_dbg_payload->set_data_ptr(reinterpret_cast<uint8_t*>(p_data_));

    uint32_t number_bytes_rd = socket->transport_dbg( *mp_dbg_payload );
    if (number_bytes_rd != size_) {
        fprintf(stderr, "%s transaction was not performed properly!\n", __PRETTY_FUNCTION__);
        exit(1);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// TLM-2 backward DMI method, invalidates dmi access
// IN:  start_range_ - the start addr of the memory space that is dmi invalidated 
//      end_range_   - the end addr of the memory space that is dmi invalidated 
// OUT: 
// RET: 
void 
BInitiator::invalidate_direct_mem_ptr(sc_dt::uint64 start_range_, sc_dt::uint64 end_range_)
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
BInitiator::CheckAddressAlignment(const uint32_t addr_)
{
    if ((addr_ & 0x3) != 0) {
        fprintf(stderr, "ERROR! address must be multiple of 4, addr(0x%x)!\n", addr_);
        exit(1);
    }
} 
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN:  size_  - the data size that must be multiple of 4 bytes (32 bit word) 
// OUT: 
// RET: 
void 
BInitiator::CheckDataSize(const uint32_t size_)
{
    if ((size_ & 0x3) != 0) {
        fprintf(stderr, "ERROR! size must be multiple of 4, size(0x%x)!\n", size_);
        exit(1);
    }
}

