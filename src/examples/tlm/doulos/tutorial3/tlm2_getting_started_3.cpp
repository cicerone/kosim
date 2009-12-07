// Filename: tlm2_getting_started_3.cpp

//----------------------------------------------------------------------
//  Copyright (c) 2007-2008 by Doulos Ltd.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//----------------------------------------------------------------------

// Version 2 - fix warnings that only showed up using g++
// Version 3  18-June-2008 - updated for TLM-2.0
// Version 4  12-Jan-2009  - fix bug in transport_dbg
// Version 5  26-Sep-2009  - fix bug with set_end_address


// Getting Started with TLM-2.0, Tutorial Example 3


// Shows a router modeled as an interconnect component between the initiator and the target
// The router decodes the address to select a target, and masks the address in the transaction
// Shows the router passing transport, DMI and debug transactions along forward and backward paths
// and doing address translation in both directions


// Define the following macro to invoke an error response from the target
// #define INJECT_ERROR

// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc"
using namespace sc_core;
using namespace sc_dt;
using namespace std;

#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

// Initiator module generating generic payload transactions

struct Initiator: sc_module
{
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_initiator_socket<Initiator> socket;

  SC_CTOR(Initiator)
  : socket("socket"),  // Construct and name socket
    dmi_ptr_valid(false)
  {
    // Register callbacks for incoming interface method calls
    socket.register_invalidate_direct_mem_ptr(this, &Initiator::invalidate_direct_mem_ptr);

    SC_THREAD(thread_process);
  }

  void thread_process()
  {
    // TLM-2 generic payload transaction, reused across calls to b_transport, DMI and debug
    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
    sc_time delay = sc_time(10, SC_NS);

    // Generate a random sequence of reads and writes
    for (int i = 256-64; i < 256+64; i += 4)
    {
      int data;
      tlm::tlm_command cmd = static_cast<tlm::tlm_command>(rand() % 2);
      if (cmd == tlm::TLM_WRITE_COMMAND) data = 0xFF000000 | i;

      // Use DMI if it is available
      if (dmi_ptr_valid && sc_dt::uint64(i) >= dmi_data.get_start_address()
                        && sc_dt::uint64(i) <= dmi_data.get_end_address())
      {
        // Bypass transport interface and use direct memory interface
        // Implement target latency
        if ( cmd == tlm::TLM_READ_COMMAND )
        {
          assert( dmi_data.is_read_allowed() );
          memcpy(&data, dmi_data.get_dmi_ptr() + i - dmi_data.get_start_address(), 4);
          wait( dmi_data.get_read_latency() );
        }
        else if ( cmd == tlm::TLM_WRITE_COMMAND )
        {
          assert( dmi_data.is_write_allowed() );
          memcpy(dmi_data.get_dmi_ptr() + i - dmi_data.get_start_address(), &data, 4);
          wait( dmi_data.get_write_latency() );
        }

        cout << "DMI   = { " << (cmd ? 'W' : 'R') << ", " << hex << i
             << " } , data = " << hex << data << " at time " << sc_time_stamp() << endl;
      }
      else
      {
        trans->set_command( cmd );
        trans->set_address( i );
        trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data) );
        trans->set_data_length( 4 );
        trans->set_streaming_width( 4 ); // = data_length to indicate no streaming
        trans->set_byte_enable_ptr( 0 ); // 0 indicates unused
        trans->set_dmi_allowed( false ); // Mandatory initial value
        trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value


#ifdef INJECT_ERROR
        if (i > 90) trans->set_streaming_width(2);
#endif

        // Other fields default: byte enable = 0, streaming width = 0, DMI_hint = false, no extensions

        socket->b_transport( *trans, delay );  // Blocking transport call

        // Initiator obliged to check response status
        if ( trans->is_response_error() )
        {
          // Print response string
          char txt[100];
          sprintf(txt, "Error from b_transport, response status = %s",
                       trans->get_response_string().c_str());
          SC_REPORT_ERROR("TLM-2", txt);

        }

        // Check DMI hint
        if ( trans->is_dmi_allowed() )
        {
          // *********************************************
          // Re-use transaction object for DMI. Reset the address because it could
          // have been modified by the interconnect on the previous transport call
          // *********************************************

          trans->set_address( i );
          dmi_ptr_valid = socket->get_direct_mem_ptr( *trans, dmi_data );
        }

        cout << "trans = { " << (cmd ? 'W' : 'R') << ", " << hex << i
             << " } , data = " << hex << data << " at time " << sc_time_stamp() << endl;
      }
    }

    // Use debug transaction interface to dump memory contents, reusing same transaction object
    sc_dt::uint64 A = 128;
    trans->set_address(A);
    trans->set_read();
    trans->set_data_length(256);

    unsigned char* data = new unsigned char[256];
    trans->set_data_ptr(data);

    unsigned int n_bytes = socket->transport_dbg( *trans );

    for (unsigned int i = 0; i < n_bytes; i += 4)
    {
      cout << "mem[" << (A + i) << "] = "
           << *(reinterpret_cast<unsigned int*>( &data[i] )) << endl;
    }

    A = 256;
    trans->set_address(A);
    trans->set_data_length(128);

    n_bytes = socket->transport_dbg( *trans );

    for (unsigned int i = 0; i < n_bytes; i += 4)
    {
      cout << "mem[" << (A + i) << "] = "
           << *(reinterpret_cast<unsigned int*>( &data[i] )) << endl;
    }
  }

  // TLM-2 backward DMI method
  virtual void invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                         sc_dt::uint64 end_range)
  {
    // Ignore range and invalidate all DMI pointers regardless
    dmi_ptr_valid = false;
  }

  bool dmi_ptr_valid;
  tlm::tlm_dmi dmi_data;
};


// *********************************************
// Generic payload blocking transport router
// *********************************************

template<unsigned int N_TARGETS>
struct Router: sc_module
{
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_target_socket<Router>            target_socket;

  // *********************************************
  // Use tagged sockets to be able to distinguish incoming backward path calls
  // *********************************************

  tlm_utils::simple_initiator_socket_tagged<Router>* initiator_socket[N_TARGETS];

  SC_CTOR(Router)
  : target_socket("target_socket")
  {
    // Register callbacks for incoming interface method calls
    target_socket.register_b_transport(       this, &Router::b_transport);
    target_socket.register_get_direct_mem_ptr(this, &Router::get_direct_mem_ptr);
    target_socket.register_transport_dbg(     this, &Router::transport_dbg);

    for (unsigned int i = 0; i < N_TARGETS; i++)
    {
      char txt[20];
      sprintf(txt, "socket_%d", i);
      initiator_socket[i] = new tlm_utils::simple_initiator_socket_tagged<Router>(txt);

      // *********************************************
      // Register callbacks for incoming interface method calls, including tags
      // *********************************************
      initiator_socket[i]->register_invalidate_direct_mem_ptr(this, &Router::invalidate_direct_mem_ptr, i);
    }
  }

  // ****************
  // FORWARD PATH
  // ****************

  // TLM-2 blocking transport method
  virtual void b_transport( tlm::tlm_generic_payload& trans, sc_time& delay )
  {
    sc_dt::uint64 address = trans.get_address();
    sc_dt::uint64 masked_address;
    unsigned int target_nr = decode_address( address, masked_address);

    // Modify address within transaction
    trans.set_address( masked_address );

    // Forward transaction to appropriate target
    ( *initiator_socket[target_nr] )->b_transport( trans, delay );
  }

  // TLM-2 forward DMI method
  virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans,
                                  tlm::tlm_dmi& dmi_data)
  {
    sc_dt::uint64 masked_address;
    unsigned int target_nr = decode_address( trans.get_address(), masked_address );
    trans.set_address( masked_address );

    bool status = ( *initiator_socket[target_nr] )->get_direct_mem_ptr( trans, dmi_data );

    // Calculate DMI address of target in system address space
    dmi_data.set_start_address( compose_address( target_nr, dmi_data.get_start_address() ));
    dmi_data.set_end_address  ( compose_address( target_nr, dmi_data.get_end_address() ));

    return status;
  }

  // TLM-2 debug transaction method
  virtual unsigned int transport_dbg(tlm::tlm_generic_payload& trans)
  {
    sc_dt::uint64 masked_address;
    unsigned int target_nr = decode_address( trans.get_address(), masked_address );
    trans.set_address( masked_address );

    // Forward debug transaction to appropriate target
    return ( *initiator_socket[target_nr] )->transport_dbg( trans );
  }

  // ****************
  // BACKWARD PATH
  // ****************

  // **************************
  // Tagged backward DMI method
  // **************************

  virtual void invalidate_direct_mem_ptr(int id,
                                         sc_dt::uint64 start_range,
                                         sc_dt::uint64 end_range)
  {
    // Reconstruct address range in system memory map
    sc_dt::uint64 bw_start_range = compose_address( id, start_range );
    sc_dt::uint64 bw_end_range   = compose_address( id, end_range );
    target_socket->invalidate_direct_mem_ptr(bw_start_range, bw_end_range);
  }

  // ****************
  // ROUTER INTERNALS
  // ****************

  // Simple fixed address decoding
  inline unsigned int decode_address( sc_dt::uint64 address, sc_dt::uint64& masked_address )
  {
    unsigned int target_nr = static_cast<unsigned int>( (address >> 8) & 0x3 );
    masked_address = address & 0xFF;
    return target_nr;
  }

  inline sc_dt::uint64 compose_address( unsigned int target_nr, sc_dt::uint64 address)
  {
    return (target_nr << 8) | (address & 0xFF);
  }
};


// Target module representing a simple memory

struct Memory: sc_module
{
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_target_socket<Memory> socket;

  enum { SIZE = 256 };
  const sc_time LATENCY;

  SC_CTOR(Memory)
  : socket("socket"), LATENCY(10, SC_NS)
  {
    // Register callbacks for incoming interface method calls
    socket.register_b_transport(       this, &Memory::b_transport);
    socket.register_get_direct_mem_ptr(this, &Memory::get_direct_mem_ptr);
    socket.register_transport_dbg(     this, &Memory::transport_dbg);

    // Initialize memory with random data
    for (int i = 0; i < SIZE; i++)
      mem[i] = 0xAA000000 | (mem_nr << 20) | (rand() % 256);

    ++mem_nr;
  }

  // TLM-2 blocking transport method
  virtual void b_transport( tlm::tlm_generic_payload& trans, sc_time& delay )
  {
    tlm::tlm_command cmd = trans.get_command();
    sc_dt::uint64    adr = trans.get_address() / 4;
    unsigned char*   ptr = trans.get_data_ptr();
    unsigned int     len = trans.get_data_length();
    unsigned char*   byt = trans.get_byte_enable_ptr();
    unsigned int     wid = trans.get_streaming_width();

    // Obliged to check address range and check for unsupported features,
    //   i.e. byte enables, streaming, and bursts
    // Can ignore extensions

    // Generate the appropriate error response
    if (adr >= SIZE) {
      trans.set_response_status( tlm::TLM_ADDRESS_ERROR_RESPONSE );
      return;
    }
    if (byt != 0) {
      trans.set_response_status( tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE );
      return;
    }
    if (len > 4 || wid < len) {
      trans.set_response_status( tlm::TLM_BURST_ERROR_RESPONSE );
      return;
    }

    wait(delay);
    delay = SC_ZERO_TIME;

    // Obliged to implement read and write commands
    if ( cmd == tlm::TLM_READ_COMMAND )
      memcpy(ptr, &mem[adr], len);
    else if ( cmd == tlm::TLM_WRITE_COMMAND )
      memcpy(&mem[adr], ptr, len);

    // Set DMI hint to indicated that DMI is supported
    trans.set_dmi_allowed(true);

    // Obliged to set response status to indicate successful completion
    trans.set_response_status( tlm::TLM_OK_RESPONSE );
  }

  // TLM-2 forward DMI method
  virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans,
                                  tlm::tlm_dmi& dmi_data)
  {
    // Permit read and write access
    dmi_data.allow_read_write();

    // Set other details of DMI region
    dmi_data.set_dmi_ptr( reinterpret_cast<unsigned char*>( &mem[0] ) );
    dmi_data.set_start_address( 0 );
    dmi_data.set_end_address( SIZE*4-1 );
    dmi_data.set_read_latency( LATENCY );
    dmi_data.set_write_latency( LATENCY );

    return true;
  }

  // TLM-2 debug transaction method
  virtual unsigned int transport_dbg(tlm::tlm_generic_payload& trans)
  {
    tlm::tlm_command cmd = trans.get_command();
    sc_dt::uint64    adr = trans.get_address() / 4;
    unsigned char*   ptr = trans.get_data_ptr();
    unsigned int     len = trans.get_data_length();

    // Calculate the number of bytes to be actually copied
    unsigned int num_bytes = (len < (SIZE - adr) * 4) ? len : (SIZE - adr) * 4;

    if ( cmd == tlm::TLM_READ_COMMAND )
      memcpy(ptr, &mem[adr], num_bytes);
    else if ( cmd == tlm::TLM_WRITE_COMMAND )
      memcpy(&mem[adr], ptr, num_bytes);

    return num_bytes;
  }

  int mem[SIZE];
  static unsigned int mem_nr;
};

unsigned int Memory::mem_nr = 0;


SC_MODULE(Top)
{
  Initiator* initiator;
  Router<4>* router;
  Memory*    memory[4];

  SC_CTOR(Top)
  {
    // Instantiate components
    initiator = new Initiator("initiator");
    router    = new Router<4>("router");
    for (int i = 0; i < 4; i++)
    {
      char txt[20];
      sprintf(txt, "memory_%d", i);
      memory[i]   = new Memory(txt);
    }

    // Bind sockets
    initiator->socket.bind( router->target_socket );
    for (int i = 0; i < 4; i++)
      router->initiator_socket[i]->bind( memory[i]->socket );
  }
};


int sc_main(int argc, char* argv[])
{
  Top top("top");
  sc_start();
  return 0;
}

void run_sim()
{
  Top top("top");
  sc_start();
}

