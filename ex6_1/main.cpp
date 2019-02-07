#define SC_INCLUDE_DYNAMIC_PROCESSES
#include <systemc>
#include <tlm.h>

#include "src.h"
#include "dst.h"
#include "src_simple.h"
#include "dst_simple.h"

using namespace sc_core;
//using namespace tlm;

int sc_main(int argc, char* argv[]) {

  // instantiate units with base sockets
  src_unit    source("source");
  dst_unit    destination("destination");

  //// instantiate units with simple sockets
  //src_unit_simple    source("source");
  //dst_unit_simple    destination("destination");

  // Here, we bind the initiator socket to target socket
  source.init_socket(destination.tgt_socket);

  // start the simulation
  sc_start();

  return 0;

} // END MAIN

