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
    case 2:
      setupRTC_d = (setupRTC_d + 1) % 31;
      HAL::setCombinedLed(Artist::decimalToLed(setupRTC_d+1));
      break;
     case 3:
      setupRTC_m = (setupRTC_m + 1) % 12;
      HAL::setCombinedLed(Artist::decimalToLed(setupRTC_m+1));
      break;
    case 4:
      setupRTC_y = (setupRTC_y + 1) % 10;
      HAL::setCombinedLed(Artist::decimalToLed(setupRTC_y+20));
      break;
  }
}

void cb_setupRTC_B() {
  setupRTC_step++;
  switch(setupRTC_step) {
    case 2:
      setupRTC_d = 0;
      HAL::setLastLedNumber(1);
      HAL::setCombinedLed(Artist::decimalToLed(setupRTC_d+1));
      break;
     case 3:
      setupRTC_m = 0;
      HAL::setLastLedNumber(2);
      HAL::setCombinedLed(Artist::decimalToLed(setupRTC_m+1));
      break;
    case 4:
      setupRTC_y = 0;
      HAL::setLastLedNumber(3);
      HAL::setCombinedLed(Artist::decimalToLed(setupRTC_y+20));
      break;
  } 
}

void setupRTC() {
  Wire.begin();

  Button::setCallbacks(cb_setupRTC_A, cb_setupRTC_B);

  setupRTC_hh = 0;
  setupRTC_mm = 0;
  HAL::setLastLedNumber(0);
  HAL::setBlinkingLed(Artist::hoursToLed(setupRTC_hh));
  
  while(setupRTC_step < 2) delay(100);
  
  Clock.setClockMode(true);
  Clock.setHour(setupRTC_hh);
  Clock.setMinute(setupRTC_mm);

  while(setupRTC_step < 5) delay(100);

  Clock.setDate(setupRTC_d);
  Clock.setMonth(setupRTC_m);
  Clock.setYear(setupRTC_y);
}