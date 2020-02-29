#include "src/HAL.hpp"
#include "src/hoursMinutes.hpp"
#include "src/browser.hpp"

#include <Wire.h>
#include "DS3231.h"

DS3231 Clock;


void displayTime();
void blinkTest();

pageCb buttonAcb[] = {displayTime, blinkTest};
#define callbackA_N 2

void setupRTC() {
  Wire.begin();
}

void setup() {
  Serial.begin(115200);
  
  setupRTC();
  
  HAL::init();
  
  Browser::init();
  Browser::setPagesCallbacks(buttonAcb, callbackA_N);
}

void loop() {
  Browser::spinOnce();
}
