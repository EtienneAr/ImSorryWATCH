#include "HAL.hpp"

#include <Arduino.h>

static const int led[] = {4, A3, A2, A1, A0, 12, 11, 10, 9, 7, 6, 5, 8};

void HAL::_initLed() {
  for(int i=0;i<13;i++) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], HIGH);
  }
}

void HAL::init() {
	HAL::_initLed();
}

void HAL::applyLed(uint16_t config) {
  for(int i=0;i<13;i++) {
    digitalWrite(led[i], (config & 1<<i) != 0 );
  }
}