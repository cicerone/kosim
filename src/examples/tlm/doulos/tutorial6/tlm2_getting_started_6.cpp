// Filename: tlm2_getting_started_6.cpp

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
// Version 2,  7-July-2008  Remove N_INITIATORS, N_TARGETS template parameters from Bus


// Getting Started with TLM-2.0, Example 6

// Shows the use of multi-sockets in an interconnect component,
// that is, multi_passthrough_initiator_socket and multi_passthrough_target_socket

// This example combines the AT initiator and target from example 4 with the bus from
// example 5, modified to use multi-sockets instead of tagged sockets
// Uses the forward and backward non-blocking transport interfaces of the bus interconnect


#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/multi_passthrough_initiator_socket.h"
#include "tlm_utils/multi_passthrough_target_socket.h"
#include "tlm_utils/peq_with_cb_and_phase.h"

#include "tlm2_getting_started_6.h"

using namespace sc_core;
using namespace std;

#define DEBUG

static ofstream fout("foo.txt");

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


// Generate a random delay (with power-law distribution) to aid testing and stress the protocol
int rand_ps()
{
  int n = rand() % 100;
  n = n * n * n;
  return n / 100;
}


// **************************************************************************************
// Initiator module generating multiple pipelined generic payload transactions
// **************************************************************************************

struct Initiator: sc_module
{
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_initiator_socket<Initiator> socket;

  SC_CTOR(Initiator)
  : socket("socket")  // Construct and name socket
  , request_in_progress(0)
  , m_peq(this, &Initiator::peq_cb)
  {
    // Register callbacks for incoming interface method calls
    socket.register_nb_transport_bw(this, &Initiator::nb_transport_bw);

    SC_THREAD(thread_process);
  }

  void thread_process()
  {
    tlm::tlm_generic_payload* trans;
    tlm::tlm_phase phase;
    sc_time delay;

    // Generate a sequence of random transactions
    for (int i = 0; i < 1000; i++)
    {
      int adr = rand();
      tlm::tlm_command cmd = static_cast<tlm::tlm_command>(rand() % 2);
      if (cmd == tlm::TLM_WRITE_COMMAND) data[i % 16] = rand();

      // Grab a new transaction from the memory manager
      trans = m_mm.allocate();
      trans->acquire();

      // Set all attributes except byte_enable_length and extensions (unused)
      trans->set_command( cmd );
      trans->set_address( adr );
      trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data[i % 16]) );
      trans->set_data_length( 4 );
      trans->set_streaming_width( 4 ); // = data_length to indicate no streaming
      trans->set_byte_enable_ptr( 0 ); // 0 indicates unused
      trans->set_dmi_allowed( false ); // Mandatory initial value
      trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value

      // Initiator must honor BEGIN_REQ/END_REQ exclusion rule
      if (request_in_progress)
        wait(end_request_event);
      request_in_progress = trans;
      phase = tlm::BEGIN_REQ;

      // Timing annotation models processing time of initiator prior to call
      delay = sc_time(rand_ps(), SC_PS);

      fout << hex << adr << " " << name() << " new, cmd=" << (cmd ? 'W' : 'R')
           << ", data=" << hex << data[i % 16] << " at time " << sc_time_stamp() << endl;

      // Non-blocking transport call on the forward path
      tlm::tlm_sync_enum status;
      status = socket->nb_transport_fw( *trans, phase, delay );

      // Check value returned from nb_transport_fw
      if (status == tlm::TLM_UPDATED)
      {
        // The timing annotation must be honored
        m_peq.notify( *trans, phase, delay );
      }
      else if (status == tlm::TLM_COMPLETED)
      {
        // The completion of the transaction necessarily ends the BEGIN_REQ phase
        request_in_progress = 0;

        // The target has terminated the transaction
        check_transaction( *trans );
      }
      wait( sc_time(rand_ps(), SC_PS) );
    }

    wait(100, SC_NS);

    // Allocate a transaction for one final, nominal call to b_transport
    trans = m_mm.allocate();
    trans->acquire();
    trans->set_command( tlm::TLM_WRITE_COMMAND );
    trans->set_address( 0 );
    trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data[0]) );
    trans->set_data_length( 4 );
    trans->set_streaming_width( 4 ); // = data_length to indicate no streaming
    trans->set_byte_enable_ptr( 0 ); // 0 indicates unused
    trans->set_dmi_allowed( false ); // Mandatory initial value
    trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value

    delay = sc_time(rand_ps(), SC_PS);

    fout << "Calling b_transport at " << sc_time_stamp() << " with delay = " << delay << endl;

    // Call b_transport to demonstrate the b/nb conversion by the simple_target_socket
    socket->b_transport( *trans, delay );
    check_transaction( *trans );
  }

  // TLM-2 backward non-blocking transport method

  virtual tlm::tlm_sync_enum nb_transport_bw( tlm::tlm_generic_payload& trans,
                                              tlm::tlm_phase& phase, sc_time& delay )
  {
    // The timing annotation must be honored
    m_peq.notify( trans, phase, delay );
    return tlm::TLM_ACCEPTED;
  }

  // Payload event queue callback to handle transactions from target
  // Transaction could have arrived through return path or backward path

  void peq_cb(tlm::tlm_generic_payload& trans, const tlm::tlm_phase& phase)
  {
    #ifdef DEBUG
      if (phase == tlm::END_REQ)
        fout << hex << trans.get_address() << " " << name() << " END_REQ at " << sc_time_stamp() << endl;
      else if (phase == tlm::BEGIN_RESP)
        fout << hex << trans.get_address() << " " << name() << " BEGIN_RESP at " << sc_time_stamp() << endl;
    #endif

    if (phase == tlm::END_REQ || (&trans == request_in_progress && phase == tlm::BEGIN_RESP))
    {
      // The end of the BEGIN_REQ phase
      request_in_progress = 0;
      end_request_event.notify();
    }
    else if (phase == tlm::BEGIN_REQ || phase == tlm::END_RESP)
      SC_REPORT_FATAL("TLM-2", "Illegal transaction phase received by initiator");

    if (phase == tlm::BEGIN_RESP)
    {
      check_transaction( trans );

      // Send final phase transition to target
      tlm::tlm_phase fw_phase = tlm::END_RESP;
      sc_time delay = sc_time(rand_ps(), SC_PS);
      socket->nb_transport_fw( trans, fw_phase, delay );
      // Ignore return value
    }
  }

  // Called on receiving BEGIN_RESP or TLM_COMPLETED
  void check_transaction(tlm::tlm_generic_payload& trans)
  {
    if ( trans.is_response_error() )
    {
      char txt[100];
      sprintf(txt, "Transaction returned with error, response status = %s",
                   trans.get_response_string().c_str());
      SC_REPORT_ERROR("TLM-2", txt);
    }

    tlm::tlm_command cmd = trans.get_command();
    sc_dt::uint64    adr = trans.get_address();
    int*             ptr = reinterpret_cast<int*>( trans.get_data_ptr() );

    fout << hex << adr << " " << name() << " check, cmd=" << (cmd ? 'W' : 'R')
         << ", data=" << hex << *ptr << " at time " << sc_time_stamp() << endl;

    // Allow the memory manager to free the transaction object
    trans.release();
  }

  mm   m_mm;
  int  data[16];
  tlm::tlm_generic_payload* request_in_progress;
  sc_event end_request_event;
  tlm_utils::peq_with_cb_and_phase<Initiator> m_peq;
};


// ************************************************************************************
// Bus model supports multiple initiators and multiple targets
// Supports b_ and nb_ transport interfaces, DMI and debug
// It does no arbitration, but routes all transactions from initiators without blocking
// It uses a simple built-in routing algorithm
// ************************************************************************************

struct Bus: sc_module
{
  // ***********************************************************
  // Each multi-socket can be bound to multiple sockets
  // No need for an array-of-sockets
  // ***********************************************************

  tlm_utils::multi_passthrough_target_socket<Bus>    targ_socket;
  tlm_utils::multi_passthrough_initiator_socket<Bus> init_socket;

  SC_CTOR(Bus)
  : targ_socket("targ_socket"), init_socket("init_socket")
  {
    targ_socket.register_nb_transport_fw(   this, &Bus::nb_transport_fw);
    targ_socket.register_b_transport(       this, &Bus::b_transport);
    targ_socket.register_get_direct_mem_ptr(this, &Bus::get_direct_mem_ptr);
    targ_socket.register_transport_dbg(     this, &Bus::transport_dbg);

    init_socket.register_nb_transport_bw(          this, &Bus::nb_transport_bw);
    init_socket.register_invalidate_direct_mem_ptr(this, &Bus::invalidate_direct_mem_ptr);
  }


  // Tagged non-blocking transport forward method
  virtual tlm::tlm_sync_enum nb_transport_fw(int id,
      tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& delay)
  {
    assert (id < targ_socket.size());

    // Forward path
    m_id_map[ &trans ] = id;

    sc_dt::uint64 address = trans.get_address();
    sc_dt::uint64 masked_address;
    unsigned int target_nr = decode_address( address, masked_address);

    if (target_nr < init_socket.size())
    {
      // Modify address within transaction
      trans.set_address( masked_address );

      // Forward transaction to appropriate target
      tlm::tlm_sync_enum status = init_socket[target_nr]->nb_transport_fw(trans, phase, delay);

      if (status == tlm::TLM_COMPLETED)
        // Put back original address
        trans.set_address( address );
      return status;
    }
    else
      return tlm::TLM_COMPLETED;
  }

  // Tagged non-blocking transport backward method
  virtual tlm::tlm_sync_enum nb_transport_bw(int id,
      tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& delay)
  {
    assert (id < init_socket.size());

    // Backward path

    // Replace original address
    sc_dt::uint64 address = trans.get_address();
    trans.set_address( compose_address( id, address ) );

    return targ_socket[ m_id_map[ &trans ] ]->nb_transport_bw(trans, phase, delay);
  }

  // Tagged TLM-2 blocking transport method
  virtual void b_transport( int id, tlm::tlm_generic_payload& trans, sc_time& delay )
  {
    assert (id < targ_socket.size());

    // Forward path
    sc_dt::uint64 address = trans.get_address();
    sc_dt::uint64 masked_address;
    unsigned int target_nr = decode_address( address, masked_address);

    if (target_nr < init_socket.size())
    {
      // Modify address within transaction
      trans.set_address( masked_address );

      // Forward transaction to appropriate target
      init_socket[target_nr]->b_transport(trans, delay);

      // Replace original address
      trans.set_address( address );
    }
  }

  // Tagged TLM-2 forward DMI method
  virtual bool get_direct_mem_ptr(int id,
                                  tlm::tlm_generic_payload& trans,
                                  tlm::tlm_dmi&  dmi_data)
  {
    sc_dt::uint64 masked_address;
    unsigned int target_nr = decode_address( trans.get_address(), masked_address );
    if (target_nr >= init_socket.size())
      return false;

    trans.set_address( masked_address );

    bool status = init_socket[target_nr]->get_direct_mem_ptr( trans, dmi_data );

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
    if (target_nr >= init_socket.size())
      return 0;
    trans.set_address( masked_address );

    // Forward debug transaction to appropriate target
    return init_socket[target_nr]->transport_dbg( trans );
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
    for (unsigned int i = 0; i < targ_socket.size(); i++)
      targ_socket[i]->invalidate_direct_mem_ptr(bw_start_range, bw_end_range);
  }

  // Simple fixed address decoding
  // In this example, for clarity, the address is passed through unmodified to the target
  inline unsigned int decode_address( sc_dt::uint64 address, sc_dt::uint64& masked_address )
  {
    unsigned int target_nr = static_cast<unsigned int>( address & 0x3 );
    masked_address = address;
    return target_nr;
  }

  inline sc_dt::uint64 compose_address( unsigned int target_nr, sc_dt::uint64 address)
  {
    return address;
  }

  std::map <tlm::tlm_generic_payload*, unsigned int> m_id_map;
};


// **************************************************************************************
// Target module able to handle two pipelined transactions
// **************************************************************************************

DECLARE_EXTENDED_PHASE(internal_ph);

struct Target: sc_module
{
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_target_socket<Target> socket;

  SC_CTOR(Target)
  : socket("socket")
  , n_trans(0)
  , response_in_progress(false)
  , next_response_pending(0)
  , end_req_pending(0)
  , m_peq(this, &Target::peq_cb)
  {
    // Register callbacks for incoming interface method calls
    socket.register_nb_transport_fw(this, &Target::nb_transport_fw);
  }

  // TLM-2 non-blocking transport method

  virtual tlm::tlm_sync_enum nb_transport_fw( tlm::tlm_generic_payload& trans,
                                              tlm::tlm_phase& phase, sc_time& delay )
  {
    sc_dt::uint64    adr = trans.get_address();
    unsigned int     len = trans.get_data_length();
    unsigned char*   byt = trans.get_byte_enable_ptr();
    unsigned int     wid = trans.get_streaming_width();

    // Obliged to check the transaction attributes for unsupported features
    // and to generate the appropriate error response
    if (byt != 0) {
      trans.set_response_status( tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE );
      return tlm::TLM_COMPLETED;
    }
    if (len > 4 || wid < len) {
      trans.set_response_status( tlm::TLM_BURST_ERROR_RESPONSE );
      return tlm::TLM_COMPLETED;
    }

    // Now queue the transaction until the annotated time has elapsed
    m_peq.notify( trans, phase, delay);
    return tlm::TLM_ACCEPTED;
  }

  void peq_cb(tlm::tlm_generic_payload& trans, const tlm::tlm_phase& phase)
  {
    tlm::tlm_sync_enum status;
    sc_time delay;

    switch (phase) {
    case tlm::BEGIN_REQ:

      #ifdef DEBUG
        fout << hex << trans.get_address() << " " << name() << " BEGIN_REQ at " << sc_time_stamp() << endl;
      #endif

      // Increment the transaction reference count
      trans.acquire();

      // Put back-pressure on initiator by deferring END_REQ until pipeline is clear
      if (n_trans == 2)
        end_req_pending = &trans;
      else
      {
        status = send_end_req(trans);
        if (status == tlm::TLM_COMPLETED) // It is questionable whether this is valid
          break;
      }

      break;

    case tlm::END_RESP:
      // On receiving END_RESP, the target can release the transaction
      // and allow other pending transactions to proceed

      #ifdef DEBUG
        fout << hex << trans.get_address() << " " << name() << " END_RESP at " << sc_time_stamp() << endl;
      #endif

      if (!response_in_progress)
        SC_REPORT_FATAL("TLM-2", "Illegal transaction phase END_RESP received by target");

      trans.release();
      n_trans--;

      // Target itself is now clear to issue the next BEGIN_RESP
      response_in_progress = false;
      if (next_response_pending)
      {
        send_response( *next_response_pending );
        next_response_pending = 0;
      }

      // ... and to unblock the initiator by issuing END_REQ
      if (end_req_pending)
      {
        status = send_end_req( *end_req_pending );
        end_req_pending = 0;
      }

      break;

    case tlm::END_REQ:
    case tlm::BEGIN_RESP:
      SC_REPORT_FATAL("TLM-2", "Illegal transaction phase received by target");
      break;

    default:
      if (phase == internal_ph)
      {
        // Execute the read or write commands

        tlm::tlm_command cmd = trans.get_command();
        sc_dt::uint64    adr = trans.get_address();
        unsigned char*   ptr = trans.get_data_ptr();
        unsigned int     len = trans.get_data_length();

        if ( cmd == tlm::TLM_READ_COMMAND )
        {
          *reinterpret_cast<int*>(ptr) = rand();
          fout << hex << adr << " " << name() << " Execute READ, target = " << name()
               << " data = " << *reinterpret_cast<int*>(ptr) << endl;
        }
        else if ( cmd == tlm::TLM_WRITE_COMMAND )
          fout << hex << adr << " " << name() << " Execute WRITE, target = " << name()
               << " data = " << *reinterpret_cast<int*>(ptr) << endl;

        trans.set_response_status( tlm::TLM_OK_RESPONSE );

        // Target must honor BEGIN_RESP/END_RESP exclusion rule
        // i.e. must not send BEGIN_RESP until receiving previous END_RESP or BEGIN_REQ
        if (response_in_progress)
        {
          // Target allows only two transactions in-flight
          if (next_response_pending)
            SC_REPORT_FATAL("TLM-2", "Attempt to have two pending responses in target");
          next_response_pending = &trans;
        }
        else
          send_response(trans);
        break;
      }
    }
  }

  tlm::tlm_sync_enum send_end_req(tlm::tlm_generic_payload& trans)
  {
    tlm::tlm_sync_enum status;
    tlm::tlm_phase bw_phase;
    tlm::tlm_phase int_phase = internal_ph;
    sc_time delay;

    // Queue the acceptance and the response with the appropriate latency
    bw_phase = tlm::END_REQ;
    delay = sc_time(rand_ps(), SC_PS); // Accept delay
    status = socket->nb_transport_bw( trans, bw_phase, delay );
    if (status == tlm::TLM_COMPLETED)
    {
      // Transaction aborted by the initiator
      // (TLM_UPDATED cannot occur at this point in the base protocol, so need not be checked)
      trans.release();
      return status;
    }

    // Queue internal event to mark beginning of response
    delay = delay + sc_time(rand_ps(), SC_PS); // Latency
    m_peq.notify( trans, int_phase, delay );
    n_trans++;

    return status;
  }

  void send_response(tlm::tlm_generic_payload& trans)
  {
    tlm::tlm_sync_enum status;
    tlm::tlm_phase bw_phase;
    sc_time delay;

    response_in_progress = true;
    bw_phase = tlm::BEGIN_RESP;
    delay = SC_ZERO_TIME;
    status = socket->nb_transport_bw( trans, bw_phase, delay );

    if (status == tlm::TLM_UPDATED)
    {
      // The timing annotation must be honored
      m_peq.notify( trans, bw_phase, delay);
    }
    else if (status == tlm::TLM_COMPLETED)
    {
      // The initiator has terminated the transaction
      trans.release();
      n_trans--;
      response_in_progress = false;
    }
  }

  int   n_trans;
  bool  response_in_progress;
  tlm::tlm_generic_payload*  next_response_pending;
  tlm::tlm_generic_payload*  end_req_pending;
  tlm_utils::peq_with_cb_and_phase<Target> m_peq;
};


// *****************************************************************************************
// Top-level module instantiates 4 initiators, a bus, and 4 targets
// *****************************************************************************************

SC_MODULE(Top)
{
  Initiator* init[4];
  Bus*       bus;
  Target*    target[4];

  SC_CTOR(Top)
  {
    bus   = new Bus("bus");

    // ***************************************************************************
    // bus->init_socket and bus->targ_socket are multi-sockets, each bound 4 times
    // ***************************************************************************

    for (int i = 0; i < 4; i++)
    {
      char txt[20];
      sprintf(txt, "init_%d", i);
      init[i] = new Initiator(txt);
      init[i]->socket.bind( bus->targ_socket );
    }

    for (int i = 0; i < 4; i++)
    {
      char txt[20];
      sprintf(txt, "target_%d", i);
      target[i] = new Target(txt);

      bus->init_socket.bind( target[i]->socket );
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

    cout << "PASSED" << endl;
}
