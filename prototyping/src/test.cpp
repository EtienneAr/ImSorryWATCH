#include "test.h"
#include <Arduino.h>

const int lled[] = {4, A3, A2, A1, A0, 12, 11, 10, 9, 7, 6, 5, 8};

void applyLed(uint16_t config) {
  for(int i=0;i<13;i++) {
    digitalWrite(lled[i], (config & 1<<i) != 0 );
  }
}