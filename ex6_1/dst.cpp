
#include "dst.h"

#define SC_INCLUDE_DYNAMIC_PROCESSES
#include <cstdio>
#include <systemc>
#include <tlm.h>

using namespace std;
using namespace sc_core;
using namespace tlm;

void dst_unit::b_transport(tlm_generic_payload& trans, sc_time& t) {

  char* text;
  int   text_length;
  int   index;


  // Parse the passed payload structure:
  // 1.) this target only supports WRITE commands, so abort all transaction
  //     requests cannot be handled
  if (!(trans.is_write())) {
    // return an "unsupported command" response
    trans.set_response_status(TLM_COMMAND_ERROR_RESPONSE);
    return;
  }

  // 2.) this target supports only accesses to address 0
  if (trans.get_address() != 0) {
    // return an "illegal address" response
    trans.set_response_status(TLM_ADDRESS_ERROR_RESPONSE);
    return;
  }

  // 3.) check the timing annotation
  if (t != SC_ZERO_TIME) {
    // If the timing annotation is greater than SC_ZERO_TIME, we have to
    // act like the transaction was received at the current simulation time
    // plus the timing annotation - in blocking transport, this can simply be
    // achieved by waiting:
    wait(t);
    t = SC_ZERO_TIME;
  }

  // 4.) get a pointer to the payload data, extract the payload data length
  text = reinterpret_cast<char*>(trans.get_data_ptr());
  text_length = trans.get_data_length();

  // Finally, process the transaction - here, we just print the received
  // string:
  // As we may only access as many bytes as specified in the payload, we
  // need to abort after the payload length:
  for (index = 0; index < text_length; index++) {
    if (*(text+index) == 0) break;     // abort on NULL character
    printf("%c",*(text+index));
  }
  printf("\n");

  // 5.) As the transaction was processed successfully, we need to update its
  //     "response" field before returning:
  trans.set_response_status(TLM_OK_RESPONSE);

} // END METHOD "b_transport"

  tlm::tlm_sync_enum dst_unit:: nb_transport_fw(tlm::tlm_generic_payload& trans,tlm::tlm_phase& phase,sc_core::sc_time& t){}
  bool dst_unit:: get_direct_mem_ptr(tlm::tlm_generic_payload& trans,tlm::tlm_dmi&  dmi_data){}
  unsigned int dst_unit:: transport_dbg(tlm::tlm_generic_payload& trans){}


