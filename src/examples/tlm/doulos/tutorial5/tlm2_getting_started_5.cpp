// Filename: tlm2_getting_started_5.cpp

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

// Version 1, 26-June-2008
// Version 2,  3-July-2008 - fix bug: call dmi_data.init()
// Version 3  12-Jan-2009  - fix bug in transport_dbg
// Version 4  26-Sep-2009  - fix bug with set_end_address


// Getting Started with TLM-2.0, Example 5

// Shows two loosely-timed initiators both with temporal decoupling and quantum keeper

// Shows a bus with multiple initiators and multiple targets (four memories)
// Routes transactions to target and back using address decoding built into the bus
// Uses tagged interfaces and sockets to implement multiple fw/bw interfaces in a single module
// Propagates DMI calls on both forward and backward paths,
// with 'invalidate' being broadcast to every initiator

// Shows transaction pooling using a memory manager


#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/tlm_quantumkeeper.h"

#include "tlm2_getting_started_5.h"

using namespace sc_core;
using namespace std;


// **************************************************************************************
// User-defined memory manager, which maintains a pool of transactions
// **************************************************************************************

class mm: public tlm::tlm_mm_interface
{
  typedef tlm::tlm_generic_payload gp_t;

public:
  mm() : free_list(0), empties(0) {}

  gp_t* allocate();
  void  free(gp_t* trans);

private:
  struct access
  {
    gp_t* trans;
    access* next;
    access* prev;
  };

  access* free_list;
  access* empties;

};

mm::gp_t* mm::allocate()
{
  gp_t* ptr;
  if (free_list)
  {
    ptr = free_list->trans;
    empties = free_list;
    free_list = free_list->next;
  }
  else
  {
    ptr = new gp_t(this);
  }
  return ptr;
}

void mm::free(gp_t* trans)
{
  if (!empties)
  {
    empties = new access;
    empties->next = free_list;
    empties->prev = 0;
    if (free_list)
      free_list->prev = empties;
  }
  free_list = empties;
  free_list->trans = trans;
  empties = free_list->prev;
}


// *****************************************************************************************
// Initiator1 writes to all 4 memories, and demonstrates DMI and debug transport
// Does not use an explicit memory manager
// *****************************************************************************************

const int RUN_LENGTH = 256;

struct Initiator1: sc_module
{
  tlm_utils::simple_initiator_socket<Initiator1> socket;

  SC_CTOR(Initiator1) : socket("socket"), dmi_ptr_valid(false)
  {
    socket.register_invalidate_direct_mem_ptr(this, &Initiator1::invalidate_direct_mem_ptr);

    SC_THREAD(thread_process);

    // *************************************************************************
    // All initiators use a quantum of 1us, that is, they synchronize themselves
    // to simulation time every 1us using the quantum keeper
    // *************************************************************************

    m_qk.set_global_quantum( sc_time(1, SC_US) );
    m_qk.reset();
  }

  void thread_process() {
    // Use debug transaction interface to dump entire memory contents
    dump();

    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
    sc_time delay;

    for (int i = 0; i < RUN_LENGTH; i += 4)
    {
      data = i;
      delay = m_qk.get_local_time();

      if (dmi_ptr_valid && sc_dt::uint64(i) >= dmi_data.get_start_address()
                        && sc_dt::uint64(i) <= dmi_data.get_end_address())
      {
        // Bypass transport interface and use direct memory interface
        assert( dmi_data.is_write_allowed() );
        memcpy(dmi_data.get_dmi_ptr() + i - dmi_data.get_start_address(), &data, 4);

        // Accumulate memory latency into local time
        delay += dmi_data.get_write_latency();

        cout << "WRITE/DMI addr = " << hex << i << ", data = " << data
             << " at " << sc_time_stamp() << " delay = " << delay << "\n";
      }
      else
      {
        // No DMI, so use blocking transport interface
        trans->set_command( tlm::TLM_WRITE_COMMAND );
        trans->set_address( i );
        trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data) );
        trans->set_data_length( 4 );
        trans->set_streaming_width( 4 ); // = data_length to indicate no streaming
        trans->set_byte_enable_ptr( 0 ); // 0 indicates unused
        trans->set_dmi_allowed( false ); // Mandatory initial value
        trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value

        socket->b_transport( *trans, delay );

        cout << "WRITE     addr = " << hex << i << ", data = " << data
             << " at " << sc_time_stamp() << " delay = " << delay << "\n";

        // Initiator obliged to check response status
        if (trans->is_response_error())
          SC_REPORT_ERROR("TLM-2", trans->get_response_string().c_str());

        if ( trans->is_dmi_allowed() )
        {
          dmi_data.init();
          dmi_ptr_valid = socket->get_direct_mem_ptr( *trans, dmi_data );
        }
      }

      // Accumulate local time and synchronize when quantum is reached
      m_qk.set( delay );
      m_qk.inc( sc_time(100, SC_NS) ); // Model time used for additional processing
      if (m_qk.need_sync()) m_qk.sync();
    }

    // Use debug transaction interface to dump entire memory contents
    dump();
  }


  virtual void invalidate_direct_mem_ptr(sc_dt::uint64 start_range, sc_dt::uint64 end_range)
  {
    cout << "INVALIDATE DMI (" << start_range << ".." << end_range
         << ") for Initiator1 at " << sc_time_stamp() << "\n";

    // Ignore range and invalidate all DMI pointers regardless
    dmi_ptr_valid = false;
  }

  void dump()
  {
  unsigned char buffer[64];
    // Use debug transaction interface to dump memory contents

    cout << "\nDump memories at time " << sc_time_stamp() << "\n";

    for (unsigned int k = 0; k < 4; k++)
    {
      tlm::tlm_generic_payload dbg;
      sc_dt::uint64 A = 64 * k;
      dbg.set_address(A);
      dbg.set_read();
      dbg.set_data_length(64);
      dbg.set_data_ptr(buffer);

      unsigned int n_bytes = socket->transport_dbg( dbg );

      for (unsigned int i = 0; i < n_bytes; i += 4)
      {
        cout << "mem[" << hex << (A + i) << "] = "
             << *(reinterpret_cast<unsigned int*>( &buffer[i] )) << endl;
      }
    }
    cout << "\n";
  }

  int data; // Internal data buffer used by initiator with generic payload
  tlm_utils::tlm_quantumkeeper m_qk; // Quantum keeper for temporal decoupling
  bool dmi_ptr_valid;
  tlm::tlm_dmi dmi_data;
};


// *****************************************************************************************
// Initiator2 reads from all 4 memories, but does not use DMI or debug transport
// Uses an explicit memory manager and transaction pool
// *****************************************************************************************

struct Initiator2: sc_module
{
  tlm_utils::simple_initiator_socket<Initiator2> socket;

  SC_CTOR(Initiator2) : socket("socket")
  {
    // No callback methods registered with socket

    SC_THREAD(thread_process);
  }

  void thread_process()
  {
    tlm::tlm_generic_payload* trans;
    sc_time delay;

    // Reset the local quantum keeper
    m_qk.reset();
    wait(1, SC_US);

    for (int i = 0; i < RUN_LENGTH; i += 4)
    {
      // Grab a new transaction from the memory manager
      trans = m_mm.allocate();
      trans->acquire();

      data = i;

      trans->set_command( tlm::TLM_READ_COMMAND );
      trans->set_address( i );
      trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data) );
      trans->set_data_length( 4 );
      trans->set_streaming_width( 4 ); // = data_length to indicate no streaming
      trans->set_byte_enable_ptr( 0 ); // 0 indicates unused
      trans->set_dmi_allowed( false ); // Mandatory initial value
      trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value

      delay = m_qk.get_local_time();

      socket->b_transport( *trans, delay );

      // Initiator obliged to check response status
      if (trans->is_response_error())
        SC_REPORT_ERROR("TLM-2", trans->get_response_string().c_str());
      if (data != i)
        SC_REPORT_ERROR("TLM-2", "Mismatch in initiator when reading back data");

      cout << "READ     addr = " << hex << i << ", data = " << data
           << " at " << sc_time_stamp() << " delay = " << delay << "\n";
      trans->release();

      // Accumulate local time and synchronize when quantum is reached
      m_qk.set( delay );
      m_qk.inc( sc_time(100, SC_NS) );// Model time used for additional processing
      if (m_qk.need_sync()) m_qk.sync();
    }
  }

  int data; // Internal data buffer used by initiator with generic payload

  mm   m_mm;                         // Memory manager
  tlm_utils::tlm_quantumkeeper m_qk; // Quantum keeper for temporal decoupling
};


// ************************************************************************************
// Bus model supports multiple initiators and multiple targets
// Supports b_ and nb_ transport interfaces, although only b_transport is actually used
// It does no arbitration, but routes all transactions from initiators without blocking
// It uses a simple built-in routing algorithm
// ************************************************************************************

template<unsigned int N_INITIATORS, unsigned int N_TARGETS>
struct Bus: sc_module
{
  // Tagged sockets allow incoming transactions to be identified
  tlm_utils::simple_target_socket_tagged<Bus>*    targ_socket[N_INITIATORS];
  tlm_utils::simple_initiator_socket_tagged<Bus>* init_socket[N_TARGETS];

  SC_CTOR(Bus)
  {
    for (unsigned int i = 0; i < N_INITIATORS; i++)
    {
      char txt[20];
      sprintf(txt, "targ_socket_%d", i);
      targ_socket[i] = new tlm_utils::simple_target_socket_tagged<Bus>(txt);

      targ_socket[i]->register_nb_transport_fw(   this, &Bus::nb_transport_fw, i);
      targ_socket[i]->register_b_transport(       this, &Bus::b_transport, i);
      targ_socket[i]->register_get_direct_mem_ptr(this, &Bus::get_direct_mem_ptr, i);
      targ_socket[i]->register_transport_dbg(     this, &Bus::transport_dbg, i);
    }
    for (unsigned int i = 0; i < N_TARGETS; i++)
    {
      char txt[20];
      sprintf(txt, "init_socket_%d", i);
      init_socket[i] = new tlm_utils::simple_initiator_socket_tagged<Bus>(txt);

      init_socket[i]->register_nb_transport_bw(          this, &Bus::nb_transport_bw, i);
      init_socket[i]->register_invalidate_direct_mem_ptr(this, &Bus::invalidate_direct_mem_ptr, i);
    }
  }


  // Tagged non-blocking transport forward method
  virtual tlm::tlm_sync_enum nb_transport_fw(int id,
      tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& delay)
  {
    if (id < N_INITIATORS)
    {
      // Forward path
      m_id_map[ &trans ] = id;

      sc_dt::uint64 address = trans.get_address();
      sc_dt::uint64 masked_address;
      unsigned int target_nr = decode_address( address, masked_address);

      if (target_nr < N_TARGETS)
      {
        // Modify address within transaction
        trans.set_address( masked_address );

        // Forward transaction to appropriate target
        tlm::tlm_sync_enum status = (*init_socket[target_nr])->nb_transport_fw(trans, phase, delay);

        if (status == tlm::TLM_COMPLETED)
          // Put back original address
          trans.set_address( address );
        return status;
      }
      else
        return tlm::TLM_COMPLETED;
    }
    else
    {
      SC_REPORT_FATAL("TLM-2", "Invalid tagged socket id in bus");
      return tlm::TLM_COMPLETED;
    }
  }

  // Tagged non-blocking transport backward method
  virtual tlm::tlm_sync_enum nb_transport_bw(int id,
      tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& delay)
  {
    if (id < N_TARGETS)
    {
      // Backward path

      // Replace original address
      sc_dt::uint64 address = trans.get_address();
      trans.set_address( compose_address( id, address ) );

      return ( *(targ_socket[ m_id_map[ &trans ] ]) )->nb_transport_bw(trans, phase, delay);
    }
    else
    {
      SC_REPORT_FATAL("TLM-2", "Invalid tagged socket id in bus");
      return tlm::TLM_COMPLETED;
    }
  }

  // Tagged TLM-2 blocking transport method
  virtual void b_transport( int id, tlm::tlm_generic_payload& trans, sc_time& delay )
  {
    if (id < N_INITIATORS)
    {
      // Forward path
      sc_dt::uint64 address = trans.get_address();
      sc_dt::uint64 masked_address;
      unsigned int target_nr = decode_address( address, masked_address);

      if (target_nr < N_TARGETS)
      {
        // Modify address within transaction
        trans.set_address( masked_address );

        // Forward transaction to appropriate target
        (*init_socket[target_nr])->b_transport(trans, delay);

        // Replace original address
        trans.set_address( address );
      }
    }
    else
      SC_REPORT_FATAL("TLM-2", "Invalid tagged socket id in bus");
  }

  // Tagged TLM-2 forward DMI method
  virtual bool get_direct_mem_ptr(int id,
                                  tlm::tlm_generic_payload& trans,
                                  tlm::tlm_dmi&  dmi_data)
  {
    sc_dt::uint64 masked_address;
    unsigned int target_nr = decode_address( trans.get_address(), masked_address );
    if (target_nr >= N_TARGETS)
      return false;

    trans.set_address( masked_address );

    bool status = ( *init_socket[target_nr] )->get_direct_mem_ptr( trans, dmi_data );

    // Calculate DMI address of target in system address space
    dmi_data.set_start_address( compose_address( target_nr, dmi_data.get_start_address() ));
    dmi_data.set_end_address  ( compose_address( target_nr, dmi_data.get_end_address() ));

    return status;
  }


  // Tagged debug transaction method
  virtual unsigned int transport_dbg(int id, tlm::tlm_generic_payload& trans)
  {
    sc_dt::uint64 masked_address;
    unsigned int target_nr = decode_address( trans.get_address(), masked_address );
    if (target_nr >= N_TARGETS)
      return 0;
    trans.set_address( masked_address );

    // Forward debug transaction to appropriate target
    return ( *init_socket[target_nr] )->transport_dbg( trans );
  }


  // Tagged backward DMI method
  virtual void invalidate_direct_mem_ptr(int id,
                                         sc_dt::uint64 start_range,
                                         sc_dt::uint64 end_range)
  {
    // Reconstruct address range in system memory map
    sc_dt::uint64 bw_start_range = compose_address( id, start_range );
    sc_dt::uint64 bw_end_range   = compose_address( id, end_range );

    // Propagate call backward to all initiators
    for (unsigned int i = 0; i < N_INITIATORS; i++)
      (*targ_socket[i])->invalidate_direct_mem_ptr(bw_start_range, bw_end_range);
  }

  // Simple fixed address decoding
  inline unsigned int decode_address( sc_dt::uint64 address, sc_dt::uint64& masked_address )
  {
    unsigned int target_nr = static_cast<unsigned int>( (address >> 6) & 0x3 );
    masked_address = address & 0x3F;
    return target_nr;
  }

  inline sc_dt::uint64 compose_address( unsigned int target_nr, sc_dt::uint64 address)
  {
    return (target_nr << 6) | (address & 0x3F);
  }

  std::map <tlm::tlm_generic_payload*, unsigned int> m_id_map;
};


// *****************************************************************************************
// Target memory implements b_transport, DMI and debug
// *****************************************************************************************

struct Memory: sc_module
{
  tlm_utils::simple_target_socket<Memory> socket;

  enum { SIZE = 64 };
  const sc_time LATENCY;

  SC_CTOR(Memory)
  : socket("socket"), LATENCY(10, SC_NS)
  {
    socket.register_b_transport(       this, &Memory::b_transport);
    socket.register_get_direct_mem_ptr(this, &Memory::get_direct_mem_ptr);
    socket.register_transport_dbg(     this, &Memory::transport_dbg);

    // Initialize memory with random data
    for (int i = 0; i < SIZE; i++)
      mem[i] = 0xAA000000 | (mem_nr << 20) | (rand() % 256);

    // Each instance is given identifiable contents to help debug
    ++mem_nr;

    SC_THREAD(invalidation_process);
  }

  virtual void b_transport( tlm::tlm_generic_payload& trans, sc_time& delay )
  {
    tlm::tlm_command cmd = trans.get_command();
    sc_dt::uint64    adr = trans.get_address() / 4;
    unsigned char*   ptr = trans.get_data_ptr();
    unsigned int     len = trans.get_data_length();
    unsigned char*   byt = trans.get_byte_enable_ptr();
    unsigned int     wid = trans.get_streaming_width();

    if (adr > sc_dt::uint64(SIZE)) {
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

    if (trans.get_command() == tlm::TLM_READ_COMMAND)
      memcpy(ptr, &mem[adr], len);
    else if (cmd == tlm::TLM_WRITE_COMMAND)
      memcpy(&mem[adr], ptr, len);

    // Use temporal decoupling: add memory latency to delay argument
    delay += LATENCY;

    trans.set_dmi_allowed(true);
    trans.set_response_status( tlm::TLM_OK_RESPONSE );
  }


  // TLM-2 DMI method
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

  void invalidation_process()
  {
    // Invalidate DMI pointers once just as an example of routing a call back to initiators
    wait(3, SC_US);
    socket->invalidate_direct_mem_ptr(0, SIZE-1);
  }

  int mem[SIZE];
  static unsigned int mem_nr;  // Unique memory number to help debug
};

unsigned int Memory::mem_nr = 0;


// *****************************************************************************************
// Top-level module instantiates 2 initiators, a bus, and 4 memories
// *****************************************************************************************

SC_MODULE(Top)
{
  Initiator1* init1;
  Initiator2* init2;
  Bus<2,4>*   bus;
  Memory*     memory[4];

  SC_CTOR(Top)
  {
    init1 = new Initiator1("init1");
    init2 = new Initiator2("init2");
    bus   = new Bus<2,4>  ("bus");

    init1->socket.bind( *(bus->targ_socket[0]) );
    init2->socket.bind( *(bus->targ_socket[1]) );

    for (int i = 0; i < 4; i++)
    {
      char txt[20];
      sprintf(txt, "memory_%d", i);
      memory[i] = new Memory(txt);

      ( *(bus->init_socket[i]) ).bind( memory[i]->socket );
    }
  }
};

int sc_main( int argc, char* argv[])
{
    Top top("top");
    sc_start();
    return 0;
}

void run_sim()
{
    Top top("top");
    sc_start();
    return 0;
}
