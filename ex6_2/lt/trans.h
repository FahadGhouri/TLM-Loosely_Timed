#ifndef _TRANS_H_
#define _TRANS_H_

#define SC_INCLUDE_DYNAMIC_PROCESSES
#include <systemc>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

SC_MODULE(trans_unit) {

 // tlm_utils::simple_target_socket<trans_unit> targ_socket;
 //tlm_utils::simple_initiator_socket<trans_unit> init_socket;

 SC_CTOR(trans_unit) : targ_socket("targ_socket"),
init_socket("init_socket")
 {
 //targ_socket.register_nb_transport_fw(this, &trans_unit::nb_transport_fw);
 targ_socket.register_b_transport(this, &trans_unit::b_transport);
 //targ_socket.register_get_direct_mem_ptr(this, &trans_unit::get_direct_mem_ptr);
 //targ_socket.register_transport_dbg(this, &trans_unit::transport_dbg);
 //init_socket.register_nb_transport_bw(this, &trans_unit::nb_transport_bw);
 //init_socket.register_invalidate_direct_mem_ptr(this,&trans_unit::invalidate_direct_mem_ptr);
 }

  void b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);
  
    tlm_utils::simple_initiator_socket<trans_unit, 32,
    tlm::tlm_base_protocol_types> init_socket;

    tlm_utils::simple_target_socket<trans_unit, 32,
    tlm::tlm_base_protocol_types> targ_socket;

  int    items_in_buffer=0;
  int    buffer[3];

}; // END SC_MODULE "trans_unit"

#endif // _TRANS_H_

