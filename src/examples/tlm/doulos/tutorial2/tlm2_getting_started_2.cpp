// Filename: tlm2_getting_started_2.cpp

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

// Version 2  18-June-2008 - updated for TLM-2.0
// Version 3   3-July-2008 - bug fix: call dmi_data.init()
// Version 4  12-Jan-2009  - fix bug in transport_dbg
// Version 5  26-Sep-2009  - fix bug with set_end_address

// Getting Started with TLM-2.0, Tutorial Example 2

// Shows the direct memory interfaces and the DMI hint.
// Shows the debug transaction interface
// Shows the proper use of response status

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
    for (int i = 0; i < 128; i += 4)
    {
      int data;
      tlm::tlm_command cmd = static_cast<tlm::tlm_command>(rand() % 2);
      if (cmd == tlm::TLM_WRITE_COMMAND) data = 0xFF000000 | i;

      // *********************************************
      // Use DMI if it is available, reusing same transaction object
      // *********************************************

      if (dmi_ptr_valid)
      {
        // Bypass transport interface and use direct memory interface
        // Implement target latency
        if ( cmd == tlm::TLM_READ_COMMAND )
        {
          assert( dmi_data.is_read_allowed() );
          memcpy(&data, dmi_data.get_dmi_ptr() + i, 4);
          wait( dmi_data.get_read_latency() );
        }
        else if ( cmd == tlm::TLM_WRITE_COMMAND )
        {
          assert( dmi_data.is_write_allowed() );
          memcpy(dmi_data.get_dmi_ptr() + i, &data, 4);
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

        socket->b_transport( *trans, delay  );  // Blocking transport call

        // Initiator obliged to check response status
        if ( trans->is_response_error() )
        {
          // *********************************************
          // Print response string
          // *********************************************

          char txt[100];
          sprintf(txt, "Error from b_transport, response status = %s",
                       trans->get_response_string().c_str());
          SC_REPORT_ERROR("TLM-2", txt);

        }

        // *********************************************
        // Check DMI hint
        // *********************************************

        if ( trans->is_dmi_allowed() )
        {
          // Re-user transaction object for DMI
          dmi_data.init();
          dmi_ptr_valid = socket->get_direct_mem_ptr( *trans, dmi_data );
        }

        cout << "trans = { " << (cmd ? 'W' : 'R') << ", " << hex << i
             << " } , data = " << hex << data << " at time " << sc_time_stamp()
             << " delay = " << delay << endl;
      }
    }

    // *********************************************
    // Use debug transaction interface to dump memory contents, reusing same transaction object
    // *********************************************

    trans->set_address(0);
    trans->set_read();
    trans->set_data_length(128);

    unsigned char* data = new unsigned char[128];
    trans->set_data_ptr(data);

    unsigned int n_bytes = socket->transport_dbg( *trans );

    for (unsigned int i = 0; i < n_bytes; i += 4)
    {
      cout << "mem[" << i << "] = "
           << *(reinterpret_cast<unsigned int*>( &data[i] )) << endl;
    }
  }

  // *********************************************
  // TLM-2 backward DMI method
  // *********************************************

  virtual void invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                         sc_dt::uint64 end_range)
  {
    // Ignore range and invalidate all DMI pointers regardless
    dmi_ptr_valid = false;
  }

  bool dmi_ptr_valid;
  tlm::tlm_dmi dmi_data;
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
      mem[i] = 0xAA000000 | (rand() % 256);

    SC_THREAD(invalidation_process);
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

    // *********************************************
    // Generate the appropriate error response
    // *********************************************

    if (adr >= sc_dt::uint64(SIZE)) {
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

    // Obliged to implement read and write commands
    if ( cmd == tlm::TLM_READ_COMMAND )
      memcpy(ptr, &mem[adr], len);
    else if ( cmd == tlm::TLM_WRITE_COMMAND )
      memcpy(&mem[adr], ptr, len);

    // Illustrates that b_transport may block
    wait(delay);

    // Reset timing annotation after waiting
    delay = SC_ZERO_TIME;

    // *********************************************
    // Set DMI hint to indicated that DMI is supported
    // *********************************************

    trans.set_dmi_allowed(true);

    // Obliged to set response status to indicate successful completion
    trans.set_response_status( tlm::TLM_OK_RESPONSE );
  }

  // *********************************************
  // TLM-2 forward DMI method
  // *********************************************

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

  void invalidation_process()
  {
    // Invalidate DMI pointers periodically
    for (int i = 0; i < 4; i++)
    {
      wait(LATENCY*8);
      socket->invalidate_direct_mem_ptr(0, SIZE-1);
    }
  }

  // *********************************************
  // TLM-2 debug transport method
  // *********************************************

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
};


SC_MODULE(Top)
{
  Initiator *initiator;
  Memory    *memory;

  SC_CTOR(Top)
  {
    // Instantiate components
    initiator = new Initiator("initiator");
    memory    = new Memory   ("memory");

    // One initiator is bound directly to one target with no intervening bus

    // Bind initiator socket to target socket
    initiator->socket.bind(memory->socket);
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

