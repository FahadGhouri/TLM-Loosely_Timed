#include "src.h"

#define SC_INCLUDE_DYNAMIC_PROCESSES
#include <systemc>
#include <tlm.h>

#include <cstring>
#include <iostream>

using namespace sc_core;
using namespace tlm;
using namespace std;

void src_unit::generate() {

  tlm_generic_payload trans;
  sc_time t;

  char text[] = "This is a demonstration of the simple_socket class.";


  // Initialize the payload object:
  // 1.) set the pointer to the payload data
  trans.set_data_ptr(reinterpret_cast<unsigned char*>(text));
  // 2.) set the length of the payload data
  trans.set_data_length(strlen(text)+1);    // include trailing zero terminator
  // 3.) set the command
  trans.set_write();
  // 4.) set the address inside the target where the command should operate
  //     on
  trans.set_address(0);
  // 5.) initialize the response status with INCOMPLETE as the transaction
  //     hasn't been processed yet
  trans.set_response_status(TLM_INCOMPLETE_RESPONSE);

  // Initialize the timing annotation ("delay argument") with "no delay":
  sc_time p(100,SC_NS);
  t = p;

  // print the simulation time before the initiation of the transaction
  cout << "simulation time BEFORE transport call: " << sc_time_stamp()
       << ", timing annotation = " << t << endl;

  // now call the blocking transport method of the target socket
  init_socket->b_transport(trans, t);

  // print the simulation time when the transport call returned
  cout << "simulation time AFTER transport call: " << sc_time_stamp()
       << ", timing annotation = " << t << endl;

  // After the call, we need to check the status of the response status, as
  // this indicates if the transaction was processed successfully:
  if (trans.is_response_error()) {
    // If an error happened, we should act on that - here, we just print out
    // a message:
    cout << "transaction failed, target returned response status: "
         << trans.get_response_string()
         << endl;
  }

} // END SC_THREAD "generate"


tlm_sync_enum src_unit:: nb_transport_bw(tlm_generic_payload& trans,tlm_phase& phase,sc_core::sc_time& t){

}
/*
void src_unit::invalidate_direct_mem_ptr(tlm_generic_payload& trans,tlm_phase& phase,sc_core::sc_time& t){

}
*/
void src_unit:: invalidate_direct_mem_ptr(sc_dt::uint64 start_range, sc_dt::uint64 end_range){

}

