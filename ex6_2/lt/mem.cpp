
#include "mem.h"

#define SC_INCLUDE_DYNAMIC_PROCESSES
#include <systemc>
#include <tlm.h>

#include <cstdio>
#include <iostream>

using namespace std;
using namespace sc_core;
using namespace tlm;

const sc_time MEM_DELAY(1,SC_MS);

void mem_unit::b_transport(tlm_generic_payload& trans, sc_time& t) {

  unsigned char* pData;
  int*           pValue;
  sc_dt::uint64  address;


  // check time argument
  if (t != SC_ZERO_TIME)          // no support for temporal decoupling yet
  {
    SC_REPORT_ERROR("memory","temporal decoupling not supported");
  }

  // extract info from the payload structure
  pData = trans.get_data_ptr();
  pValue = reinterpret_cast<int*>(pData);
  address = trans.get_address();

  //cout << sc_time_stamp() << ": MEM: received ";
  //if (trans.is_read()) {
  //  cout << "READ";
  //}
  //else if (trans.is_write()) {
  //  cout << "WRITE";
  //}
  //else {
  //  cout << "IGNORE";
  //}
  //printf(" transaction for address 0x%05x\n", address);

  // address check
  if (address < 8192) {
    // address check passed

    // check for the requested transaction size:
    // BURSTs (i.e. operations on multiple cells) are not supported, as well
    // as "fragmented" operations, i.e. operations that act only on a part of a
    // memory cell
    if (trans.get_data_length() != 4) {
      // set BURST error
      trans.set_response_status(TLM_BURST_ERROR_RESPONSE);
    }

    // size is ok - continue
    else {
      // process the annotated command
      if (trans.is_read()) {
	// process READ request:
	// read value from memory into payload
	*pValue = storage[address];
	// set the response status
    wait(10,SC_NS);
	trans.set_response_status(TLM_OK_RESPONSE);

      } // END IF: READ request

      else if (trans.is_write()) {
	// process WRITE request
	// write value from payload into memory
	storage[address] = *pValue;
	// set the response status
    wait(20,SC_NS);
	trans.set_response_status(TLM_OK_RESPONSE);

      } // END IF: WRITE request

      else {
	// set the response status
	trans.set_response_status(TLM_COMMAND_ERROR_RESPONSE);
      } // END IF: unknown request

    } // END IF: transaction size is ok
  } // END IF: address check passed

  // address check failed
  else {
    // set the response status
    trans.set_response_status(TLM_ADDRESS_ERROR_RESPONSE);
  }

} // END METHOD "b_transport"


void mem_unit::print_mem_content(sc_dt::uint64 address) {

  // print out the contents until a NULL byte occurs
  while ((storage[address] != 0) && (address < 8192)) {
    // print the ASCII value
    printf("%c",storage[address]);
    address++;
  } // END WHILE: print until NULL

  printf("\n\n");

} // END METHOD: "print_mem_content"

