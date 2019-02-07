#ifndef _DST_SIMPLE_H_
#define _DST_SIMPLE_H_

#define SC_INCLUDE_DYNAMIC_PROCESSES
#include <systemc>
#include <tlm.h>
#include <tlm_utils/simple_target_socket.h>

SC_MODULE(dst_unit_simple) {

  SC_CTOR(dst_unit_simple) {
    // register TLM callback methods
    tgt_socket.register_b_transport(this, &dst_unit_simple::b_transport_my);
  }

  void b_transport_my(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);

  tlm_utils::simple_target_socket<dst_unit_simple, 32,
    tlm::tlm_base_protocol_types> tgt_socket;


}; // END SC_MODULE "dst_unit"

#endif // _DST_SIMPLE_H_

