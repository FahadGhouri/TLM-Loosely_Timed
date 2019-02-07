#include "trans.h"

#define SC_INCLUDE_DYNAMIC_PROCESSES
#include <systemc>
#include <tlm.h>

using namespace sc_core;
using namespace tlm;

// <-- enter your implementation here

void trans_unit::b_transport(tlm_generic_payload& trans, sc_time& t) {

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
  //for (index = 0; index < text_length; index++) {
  //  if (*(text+index) == 0) break;     // abort on NULL character
  //  printf("%c",*(text+index));
  //}
  //printf("\n");

  // 5.) As the transaction was processed successfully, we need to update its
  //     "response" field before returning:
  unsigned char* pData;
  int*           pValue;
  int            value;
 
  pData = trans.get_data_ptr();
  pValue = reinterpret_cast<int*>(pData);
  value = *pValue;
  
  int sum;

  if (items_in_buffer < 3) {
    buffer[items_in_buffer] = value;
    items_in_buffer++;
    } // END IF: fill buffer

  else {
    // transformation 
    sum = value;
    for (int i = 0; i <= 2; i++) {
      sum = sum + buffer[i];
    }

    // send the calculated average to the destination unit
    //destination.send(sum/4);
    //printf("%c",sum/4);

    // buffer rotation
    for (int i = 0; i <= 1; i++) {
      buffer[i] = buffer[i+1];
    }

    buffer[2] = value;

  }  
  int x=sum/4;
  unsigned char* pRata;
  pRata = reinterpret_cast<unsigned char*>(&x);
  trans.set_data_ptr(pRata);

  init_socket->b_transport(trans, t);

  wait(8,SC_NS);
  trans.set_response_status(TLM_OK_RESPONSE);
  
}
