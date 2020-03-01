#include "src/HAL.hpp"
#include "src/artist.hpp"
#include "src/button.hpp"
#include "DS3231.h"

volatile int setupRTC_step = 0;
volatile int setupRTC_hh, setupRTC_mm, setupRTC_d, setupRTC_m, setupRTC_y;

void cb_setupRTC_A() {
  switch(setupRTC_step) {
    case 0:
      setupRTC_hh = (setupRTC_hh + 1) % 12;
      HAL::setBlinkingLed(Artist::hoursToLed(setupRTC_hh));
      break;
    case 1:
      setupRTC_mm = (setupRTC_mm + 1) % 60;
      HAL::setStaticLed(Artist::minutesToLed(setupRTC_mm));
      break;
  } 
}

void cb_setupRTC_B() {
  setupRTC_step++;
}

void setupRTC() {
  Wire.begin();

  Button::setCallbacks(cb_setupRTC_A, cb_setupRTC_B);

  setupRTC_hh = 0;
  setupRTC_mm = 0;
  HAL::setBlinkingLed(Artist::hoursToLed(setupRTC_hh));
  
  while(setupRTC_step < 2) delay(100);
  
  Clock.setClockMode(true);
  Clock.setHour(setupRTC_hh);
  Clock.setMinute(setupRTC_mm);
}