#ifndef _DST_H_
#define _DST_H_

#define SC_INCLUDE_DYNAMIC_PROCESSES
#include <systemc>
#include <tlm.h>

class dst_unit : sc_core::sc_module, tlm::tlm_fw_transport_if<> { 
public:
  SC_CTOR(dst_unit) {
    tgt_socket.bind(*this);
  }


  tlm::tlm_target_socket<> tgt_socket;
  void b_transport(tlm::tlm_generic_payload&, sc_core::sc_time&); 

  virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans,tlm::tlm_phase& phase,sc_core::sc_time& t);
  virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans,tlm::tlm_dmi&  dmi_data);
  virtual unsigned int transport_dbg(tlm::tlm_generic_payload& trans);


}; // END SC_MODULE "dst_unit"

#endif // _DST_H_

