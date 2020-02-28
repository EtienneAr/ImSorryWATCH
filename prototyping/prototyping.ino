#include "src/HAL.hpp"
#include "src/hoursMinutes.hpp"
#include "src/browser.hpp"

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
  HAL::setSlowBlinkingLed(0xAAA);
}

void test4() {
  Serial.println("Clear");
  HAL::clear();
}

void test5() {
  Serial.println("setFastBlink");
  HAL::setFastBlinkingLed(0x555);
}

pageCb mycallbacks[] = {test0, test1, test2, test3, test4, test5};


void setup() {
  Serial.begin(115200);
  HAL::init();
  //Browser::init();
  //Browser::setPagesCallbacks(mycallbacks, 6);
  //randomSeed(analogRead(A7));
  HAL::setSlowBlinkingLed(0xAAA);
  HAL::setFastBlinkingLed(0x555);
  //HAL::applyLed(0xFFF);
  HAL::setLastLedNumber(4);
  HAL::auto_off(2000);
}

void loop() {
  //Browser::spinOnce();
}
