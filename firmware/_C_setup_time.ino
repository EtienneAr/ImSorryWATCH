#include "src/HAL.hpp"
#include "src/artist.hpp"
#include "src/button.hpp"
#include "DS3231.h"

volatile int setTimeRTC_step = 0;
volatile int setTimeRTC_hh, setTimeRTC_mm, setTimeRTC_d, setTimeRTC_m, setTimeRTC_y;

void cb_setTimeRTC_A() {
  switch(setTimeRTC_step) {
    case 0:
      setTimeRTC_hh = (setTimeRTC_hh + 1) % 12;
      HAL::setBlinkingLed(Artist::hoursToLed(setTimeRTC_hh));
      break;
    case 1:
      setTimeRTC_mm = (setTimeRTC_mm + 1) % 60;
      HAL::setStaticLed(Artist::minutesToLed(setTimeRTC_mm));
      break;
    case 2:
      setTimeRTC_d = (setTimeRTC_d + 1) % 31;
      HAL::setCombinedLed(Artist::decimalToLed(setTimeRTC_d+1));
      break;
     case 3:
      setTimeRTC_m = (setTimeRTC_m + 1) % 12;
      HAL::setCombinedLed(Artist::decimalToLed(setTimeRTC_m+1));
      break;
    case 4:
      setTimeRTC_y = (setTimeRTC_y + 1) % 10;
      HAL::setCombinedLed(Artist::decimalToLed(setTimeRTC_y+20));
      break;
  }
}

void cb_setTimeRTC_B() {
  setTimeRTC_step++;
  switch(setTimeRTC_step) {
    case 2:
      setTimeRTC_d = 0;
      HAL::setLastLedNumber(1);
      HAL::setCombinedLed(Artist::decimalToLed(setTimeRTC_d+1));
      break;
     case 3:
      setTimeRTC_m = 0;
      HAL::setLastLedNumber(2);
      HAL::setCombinedLed(Artist::decimalToLed(setTimeRTC_m+1));
      break;
    case 4:
      setTimeRTC_y = 0;
      HAL::setLastLedNumber(3);
      HAL::setCombinedLed(Artist::decimalToLed(setTimeRTC_y+20));
      break;
  } 
}

void setTimeRTC() {
  Button::setCallbacks(cb_setTimeRTC_A, cb_setTimeRTC_B);

  setTimeRTC_hh = 0;
  setTimeRTC_mm = 0;
  HAL::clear();
  HAL::on();
  
  HAL::setLastLedNumber(0);
  HAL::setBlinkingLed(Artist::hoursToLed(setTimeRTC_hh));
  
  while(setTimeRTC_step < 2) delay(100);
  
  Clock.setClockMode(true);
  Clock.setHour(setTimeRTC_hh);
  Clock.setMinute(setTimeRTC_mm);

  while(setTimeRTC_step < 5) delay(100);

  Clock.setDate(setTimeRTC_d);
  Clock.setMonth(setTimeRTC_m);
  Clock.setYear(setTimeRTC_y); 
}