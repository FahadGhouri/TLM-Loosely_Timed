#include "src.h"

#define SC_INCLUDE_DYNAMIC_PROCESSES
#include <systemc>
#include <tlm.h>

using namespace sc_core;
using namespace tlm;

void src_unit::generate() {

  tlm_generic_payload trans;
  sc_time t;

  unsigned char* pData;

  int data[] = {
        0x00000037,0x00000012,0x0000005f,0xffffffd8,0x0000003a,
        0x00000012,0x0000005d,0x000000d3,0x0000003d,0x00000011,
        0x0000005d,0xffffffd5,0x0000003d,0x00000110,0x0000005a,
        0xffffffd7,0x0000003d,0x00000013,0x00000059,0x000000d5,
        0x0000003b,0x00000013,0x0000005c,0xffffffd9,0x00000039,
        0x00000110,0x0000005d,0xffffffd9,0x00000036,0xffffffbf,
        0x000000b3,0xffffffd8,0x00000036,0xfffffffd,0x00000166,
        0xfffffeea,0x00000035,0xfffffffd,0x00000257,0xfffffe34,
        0x000000e8,0xffffff0e,0x00000257,0xfffffe33,0x000001d9,
        0xfffffe5a,0x0000030d,0xfffffd43,0x000001d8,0xfffffe5b,
        0x000003fc,0xfffffc8f,0x0000028d,0xfffffd69,0x000003fd,
        0xfffffc8d,0x00000380,0xfffffc1f,0x00000454,0xfffffc90,
        0x000003b9,0xfffffbe4,0x00000453,0xfffffd81,0x000003c7,
        0xfffffbe2,0x00000452,0xfffffd76,0x000002d9,0xfffffccf,
        0x00000461,0xfffffd76,0x000002d7,0xfffffcc2,0x00000374,
        0xfffffe65,0x000002e3,0xfffffcc2,0x00000374,0xfffffe57,
        0x000001f4,0xfffffdb1,0x00000383,0xfffffe54,0x000001f5,
        0xfffffda5,0x0000023b,0xfffffeac,0x000001f6,0xfffffe94,
        0x0000014a,0xfffffeaf,0x00000231,0xfffffe56,0x00000246,
        0xfffffeb0,0x00000171,0xffffff15,0x00000189,0xfffffe71,
        0x00000171,0xffffff17,0x000001c6,0xfffffe34,0x000001ad,
        0xfffffedc,0x000001c3,0xfffffe34,0x000001ea,0xfffffea1,
        0x000001fe,0xfffffdfa,0x000001e9,0xfffffe9f,0x0000023d,
        0xfffffd63,0x00000242,0xfffffe9e,0x0000023e,0xfffffe55,
        0x0000018c,0xffffff5e,0x0000017f,0xffffff0a,0x0000009b,
        0xffffff5e,0x0000017e,0xfffffffc,0x000000a7,0xffffff5b,
        0x000000be,0x000000b3,0xfffffff2,0x0000001c,0x000000bc,
        0x000000b2,0xffffff34,0x000000d0,0x00000007,0x00000171,
        0xffffff34,0x000000d2,0xffffff48,0x000000dd,0xffffff8b,
        0x000000d2,0xffffff49,0x000000dd,0xffffff8b,0x0000010b,
        0xffffff0f,0x000000db,0x0000007c,0x00000117,0xffffff0e,
        0x000000de,0x00000070,0x00000025,0xffffff10,0x000000dd,
        0x0000006f,0x00000063,0xfffffed3,0x000000de,0x0000015e,
        0x00000070,0xfffffed3,0x000000dc,0x00000152,0xffffff27,
        0xffffff2c,0x000000dd,0x00000152,0xffffff25,0xffffff2d,
        0x000001cc,0x00000064,0xffffff23,0xffffff6c,0x0000018e,
        0x0000015f,0xffffff25,0xfffffeac,0x0000024d,0x00000065,
        0xffffff24,0xffffffa7,0x00000242,0xffffff76,0xffffff21,
        0xffffffe4,0x00000205,0xffffff79,0xffffff21,0x00000020,
        0x0000016f,0xffffffd2,0xffffff21,0x00000020,0x0000016d,
        0xffffffd5,0xffffff21,0x0000010f,0x000000b8,0x00000097,
        0xfffffe61,0x000001c2,0xffffffc8,0x00000098,0xfffffe5f,
        0x000002b4,0xffffff14,0x0000014c,0xfffffd6d,0x000003a3,
        0xfffffe62,0x0000020d,0xfffffd6b,0x000003a3,0xfffffda3,
        0x00000178,0xfffffdc4,0x000003a3,0xfffffda1,0x00000179,
        0xfffffdc4,0x000003a4,0xfffffda2,0x00000176,0xfffffe00,
        0x0000036b,0xfffffda2,0x00000263,0xfffffe0d,0x0000036a,
        0xfffffce5,0x00000224,0xfffffe0f,0x00000459,0xfffffcf3,
        0x00000221,0xfffffe10,0x0000044e,0xfffffbac,0x00000278,
        0xfffffe11,0x0000044d,0xfffffbac,0x00000276,0xfffffe14,
        0x0000044a,0xfffffbae,0x00000365,0xfffffd26,0x00000449,
        0xfffffbea,0x00000327,0xfffffe22,0x0000043e,0xfffffaf9,
        0x00000328,0xfffffe5e,0x00000404,0xfffffaf7,0x00000329,
        0xfffffe98,0x00000370,0xfffffb52,0x00000328,0xfffffe98,
        0x00000370,0xfffffb52,0x00000329,0xfffffe96,0x00000371,
        0xfffffb51,0x00000418,0xfffffde2,0x00000434,0xfffffa8e,
        0x000004cf,0xfffffcef,0x00000526,0xfffff9d8,0x00000592,
        0xfffffced,0x00000527,0xfffff919,0x000004fc,0xfffffd47,
        0x00000524,0xfffff91b,0x000004fa,0xfffffd4a,0x00000524,
        0xfffff91b,0x000004fa,0xfffffd47,0x00000526,0xfffff91b,
        0x00000536,0xfffffd09,0x00000526,0xfffffa0c,0x00000542,
        0xfffffd0a,0x00000526,0xfffff9ff,0x000003fb,0xfffffd62,
        0x00000526,0xfffff9fe,0x000003fc,0xfffffd60,0x00000527,
        0xfffff9fe,0x000003fc,0xfffffd62,0x00000524,0xfffffa01,
        0x000004ec,0xfffffc6f,0x00000525,0xfffffa3f,0x000004ad,
        0xfffffc70,0x00000526,0xfffffa7c,0x00000417,0xfffffcc7,
        0x00000527,0xfffffa7e,0x00000415,0xfffffcc8,0x00000525,
        0xfffffa80,0x00000413,0xfffffcca,0x00000523,0xfffffa83,
        0x00000410,0xfffffdbc,0x0000046d,0xfffffb45,0x00000410,
        0xfffffdbc,0x000003ae,0xfffffaae,0x00000411,0xfffffd93
      };

  int x=33;

  int arraylen = sizeof(data)/sizeof(int);

  for(int index =0;index<arraylen;index++)
  {
    // init payload and time argument
    pData = reinterpret_cast<unsigned char*>(&data[index]);
   // pData = reinterpret_cast<unsigned char*>(&x);
    trans.set_data_ptr(pData);
    trans.set_data_length(4);
    trans.set_write();
    trans.set_response_status(TLM_INCOMPLETE_RESPONSE);
    t = SC_ZERO_TIME;
    init_socket->b_transport(trans, t);
  }

} // END SC_THREAD "generate"

