#ifndef _SRC_SIMPLE_H_
#define _SRC_SIMPLE_H_

#define SC_INCLUDE_DYNAMIC_PROCESSES
#include <systemc>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>

SC_MODULE(src_unit_simple) {

  SC_CTOR(src_unit_simple) {
    // register SystemC threads
    SC_THREAD(generate);
  }


  tlm_utils::simple_initiator_socket<src_unit_simple, 32,
    tlm::tlm_base_protocol_types> init_socket;

  void generate();

}; // END SC_MODULE "src_unit_simple"

#endif

