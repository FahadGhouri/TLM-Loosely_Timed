#include "trans.h"

void trans_unit::send(int value) {

  int sum;

  if (items_in_buffer < 3) {
    buffer[items_in_buffer] = value;
    items_in_buffer++;
  } // END IF: fill buffer

  else {
    // transformation 
    sum = value;
    for (int i = 0; i <= 2; i++) {
      sum = sum + buffer[i];
    }

    // send the calculated average to the destination unit
    destination.send(sum/4);

    // buffer rotation
    for (int i = 0; i <= 1; i++) {
      buffer[i] = buffer[i+1];
    }

    buffer[2] = value;

  } // END IF: calculate the average of the last four sent values

} // END METHOD "start"

