#include "HAL.hpp"

#include <Arduino.h>

static const int led[] = {4, A3, A2, A1, A0, 12, 11, 10, 9, 7, 6, 5, 8};

void _HAL_initLed() {
  for(int i=0;i<13;i++) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], HIGH);
  }
}

void HAL_init() {
	_HAL_initLed();
}

void HAL_applyLed(uint16_t config) {
  for(int i=0;i<13;i++) {
    digitalWrite(led[i], (config & 1<<i) != 0 );
  }
}