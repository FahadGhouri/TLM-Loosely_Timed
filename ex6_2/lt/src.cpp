#include "src.h"

#define SC_INCLUDE_DYNAMIC_PROCESSES
#include <systemc>
#include <tlm.h>


using namespace sc_core;
using namespace tlm;
using namespace std;
void src_unit::generate() {

  tlm_generic_payload trans;
  tlm_generic_payload trans2;
  sc_time t;

  unsigned char* pData;

  // prepare data to read the number of words to be processed
    int data=0;
    pData = reinterpret_cast<unsigned char*>(&data);
    trans.set_data_ptr(pData);
    trans.set_data_length(4);
    trans.set_address(0);
    trans.set_read();
    trans.set_response_status(TLM_INCOMPLETE_RESPONSE);
    t = SC_ZERO_TIME;
// <-- enter your implementation here
    init_socket_2->b_transport(trans, t);
    
    pData = trans.get_data_ptr(); 
    int mem_size = *(reinterpret_cast<int*>(pData)); 
    
    cout<<"MEM "<<mem_size<<endl;

// <-- enter your implementation here
// loop to read word from MEM and forward it to T 
    
    for(int index =1;index<mem_size+1;index++)
  {
    pData = reinterpret_cast<unsigned char*>(&data);
    trans.set_data_ptr(pData);
    trans.set_data_length(4);
    trans.set_address(index);
    trans.set_read();
    trans.set_response_status(TLM_INCOMPLETE_RESPONSE);
    t = SC_ZERO_TIME;
    init_socket_2->b_transport(trans, t);
    
    pData = trans.get_data_ptr(); 
    data = *(reinterpret_cast<int*>(pData)); 
    if(index==1){    
        cout<<"Data on index 1: "<<data<<endl;
    }
    pData = reinterpret_cast<unsigned char*>(&data);
    trans2.set_data_ptr(pData);
    trans2.set_data_length(4);
    trans2.set_write();
    trans2.set_response_status(TLM_INCOMPLETE_RESPONSE);
    t = SC_ZERO_TIME;
    init_socket->b_transport(trans2, t);
  }


    std::cout << "end of the simulation @" << sc_time_stamp()<< std::endl;
} 
// <-- enter your implementation here

