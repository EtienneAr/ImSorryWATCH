#include "src/HAL.hpp"
#include "src/artist.hpp"
#include "DS3231.h"

volatile int setupRTC_step = -1;
volatile int setupRTC_h, setupRTC_m = 0;

#define SETUP_DEBOUNCE_LOOP 1024

inline void setupRTC_debounce() { 
  for(int i=0;i<SETUP_DEBOUNCE_LOOP;i++) {
    __asm__("nop\n\t");
  }
}

void cb_setupRTC_A() {
  if(digitalRead(PIN_BUTTON_A) == HIGH) {
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
  setupRTC_debounce();
}

void cb_setupRTC_B() {
  if(digitalRead(PIN_BUTTON_B) == HIGH) {
    setupRTC_step++;
  }
  setupRTC_debounce();
}

void setupRTC() {
  Wire.begin();

  pinMode(PIN_BUTTON_A, INPUT_PULLUP);
  pinMode(PIN_BUTTON_B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_A), cb_setupRTC_A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_B), cb_setupRTC_B, CHANGE);

  setupRTC_h = 0;
  setupRTC_m = 0;
  while(setupRTC_step < 2) {

  }
}