#include "src/HAL.hpp"
#include "src/artist.hpp"
#include "src/button.hpp"
#include "DS3231.h"

volatile int setupRTC_step = 0;
volatile int setupRTC_h, setupRTC_m = 0;

void cb_setupRTC_A() {
  switch(setupRTC_step) {
    case 0:
      setupRTC_h++;
      HAL::setBlinkingLed(Artist::hoursToLed(setupRTC_h));
      break;
    case 1:
      setupRTC_m++;
      HAL::setStaticLed(Artist::minutesToLed(setupRTC_m));
      break;
  } 
}

void cb_setupRTC_B() {
  setupRTC_step++;
}

void setupRTC() {
  Wire.begin();

  Button::setCallbacks(cb_setupRTC_A, cb_setupRTC_B);

  setupRTC_h = 0;
  setupRTC_m = 0;
  while(setupRTC_step < 2) {

  }
}