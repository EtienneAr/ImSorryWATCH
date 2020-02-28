#include "src/HAL.hpp"
#include "src/hoursMinutes.hpp"
#include "src/browser.hpp"

#include <Wire.h>
#include "DS3231.h"

void test0() {
  Serial.println(0);
}

void test1() {
  Serial.println("OFF");
  HAL::off();
}

void test2() {
  Serial.println("ON");
  HAL::on();
}

void test3() {
  Serial.println("SetSlowBlink");
  HAL::setBlinkingLed(0xAAA);
}

void test4() {
  Serial.println("Clear");
  HAL::clear();
}

void test5() {
  Serial.println("setFastBlink");
  HAL::applyLed(0x555);
  HAL::setBlinkingLed(0x555);
}

pageCb mycallbacks[] = {test0, test1, test2, test3, test4, test5};

void cbtest() {
  Serial.println("COUCOU");
}

void setupRTC() {
  Wire.begin();
}

DS3231 Clock;

void setup() {
  Serial.begin(115200);
  setupRTC();
  Serial.println("0. Sec : ");
  Serial.println(Clock.getSecond());
  HAL::init();
  //Browser::init();
  //Browser::setPagesCallbacks(mycallbacks, 6);
  //randomSeed(analogRead(A7));
  HAL::applyLed(0x555);
  HAL::setBlinkingLed(0xFFF);
  //HAL::applyLed(0xFFF);
  HAL::setLastLedNumber(4);
  //HAL::auto_off(2000, cbtest);
  Serial.println("1. Sec : ");
  Serial.println(Clock.getSecond());

}

void loop() {
  //Browser::spinOnce();
}
