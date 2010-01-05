// Filename: tlm2_getting_started_4.cpp

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

// Version 2  19-June-2008 - updated for TLM-2.0


// Getting Started with TLM-2.0, Example 4

// Shows the non-blocking transport interface with the generic payload and simple sockets
// Shows nb_transport used with the forward and backward paths
// Both components are able to accept transactions on the return path,
// although neither component actually uses the return path (TLM_UPDATED)

// Shows the Approximately Timed coding style
// Models processing delay of initiator, latency of target, and request and response accept delays
// Uses payload event queues to manage both timing annotations and internal delays

// Shows the BEGIN_REQ exclusion rule at the initiator and BEGIN_RESP exclusion rule at the target
// In this example, the target allows two pipelined transactions in-flight

// Shows an explicit memory manager and reference counting

// No use of temporal decoupling, DMI or debug transport
// Nominal use of the blocking transport interface just to show the simple socket b/nb adapter


// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc"
using namespace sc_core;
using namespace sc_dt;
using namespace std;

#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/peq_with_cb_and_phase.h"

#include "tlm2_getting_started_4.h"
#define DEBUG

static ofstream fout("foo.txt");

// **************************************************************************************
// User-defined memory manager, which maintains a pool of transactions
// **************************************************************************************

class mm: public tlm::tlm_mm_interface
{
  typedef tlm::tlm_generic_payload gp_t;

public:
  mm() : free_list(0), empties(0)
  #ifdef DEBUG
  , count(0)
  #endif
  {}

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

  #ifdef DEBUG
  int     count;
  #endif
};

mm::gp_t* mm::allocate()
{
  #ifdef DEBUG
    fout << "----------------------------- Called allocate(), #trans = " << ++count << endl;
  #endif
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
  #ifdef DEBUG
    fout << "----------------------------- Called free(), #trans = " << --count << endl;
  #endif
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

      fout << hex << adr << " new, cmd=" << (cmd ? 'W' : 'R')
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
        fout << hex << trans.get_address() << " END_REQ at " << sc_time_stamp() << endl;
      else if (phase == tlm::BEGIN_RESP)
        fout << hex << trans.get_address() << " BEGIN_RESP at " << sc_time_stamp() << endl;
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

    fout<< hex << adr << " check, cmd=" << (cmd ? 'W' : 'R')
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
        fout << hex << trans.get_address() << " BEGIN_REQ at " << sc_time_stamp() << endl;
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
        fout << hex << trans.get_address() << " END_RESP at " << sc_time_stamp() << endl;
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
          fout << hex << adr << " Execute READ, data = " << *reinterpret_cast<int*>(ptr) << endl;
        }
        else if ( cmd == tlm::TLM_WRITE_COMMAND )
          fout << hex << adr << " Execute WRITE, data = " << *reinterpret_cast<int*>(ptr) << endl;

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


SC_MODULE(Top)
{
  Initiator *initiator;
  Target    *target;

  SC_CTOR(Top)
  {
    // Instantiate components
    initiator = new Initiator("initiator");
    target    = new Target   ("target");

    // One initiator is bound directly to one target with no intervening bus

    // Bind initiator socket to target socket
    initiator->socket.bind(target->socket);
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

  cout << "PASSED" << endl;
}

