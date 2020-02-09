#include "src/HAL.hpp"
#include "src/hoursMinutes.hpp"
#include "src/browser.hpp"

void test0() {
  Serial.println("TEST 0");
}

void test1() {
  Serial.println("TEST 1 ... ");
  for(int i=0;i<10000;i++) {
    for(int j=0;j<100;j++) {
      asm("NOP  ");
    }
  }
  Serial.println("DONE");
}

void test2() {
  Serial.println("TEST 2");
}

void test3() {
  Serial.println("TEST 3");
}

void test4() {
  Serial.println("TEST 4");
}

pageCb mycallbacks[] = {test0, test1, test2, test3, test4};


void setup() {
  Serial.begin(115200);
  HAL::init();
  Browser::init();
  Browser::setPagesCallbacks(mycallbacks, 5);
  randomSeed(analogRead(A7));
  HAL::setSlowBlinkingLed(0xAAA);
  HAL::setFastBlinkingLed(0x555);
  //HAL::applyLed(0xFFF);
  HAL::setLastLedNumber(4);
}

void loop() {
  Browser::spinOnce();
}
