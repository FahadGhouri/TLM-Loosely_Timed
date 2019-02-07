#ifndef _SRC_H_
#define _SRC_H_

#define SC_INCLUDE_DYNAMIC_PROCESSES
#include <systemc>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
// #include <tlm_utils/simple_target_socket.h>

SC_MODULE(src_unit) {

  SC_CTOR(src_unit) {
    // register SystemC threads
    SC_THREAD(generate);
  }


  tlm_utils::simple_initiator_socket<src_unit, 32,
    tlm::tlm_base_protocol_types> init_socket;

  void generate();

}; // END SC_MODULE "src_unit"

#endif

