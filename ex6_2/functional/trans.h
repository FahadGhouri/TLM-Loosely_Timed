#ifndef _TRANS_H_
#define _TRANS_H_

#include "dst.h"

class trans_unit {

  public:
  trans_unit() : items_in_buffer(0)
  {}

  void send(int value);

  private:
  dst_unit    destination;

  int    items_in_buffer;
  int    buffer[3];

}; // END CLASS "trans_unit"

#endif // _TRANS_H_

