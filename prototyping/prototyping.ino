#include "src/HAL.hpp"
#include "src/hoursMinutes.hpp"
#include "src/browser.hpp"

void setup() {
  Serial.begin(115200);
  HAL::init();
  Browser::init();
  randomSeed(analogRead(A7));
  HAL::setSlowBlinkingLed(0xAAA);
  HAL::setFastBlinkingLed(0x555);
  //HAL::applyLed(0xFFF);
  HAL::setLastLedNumber(4);
}

int random_test;


uint16_t i = 1;

void loop() {
  /*
  random_test = int(random(60));
  displayMinute(random_test);
  while(!Serial.available()){ }
  int verif = int(Serial.parseInt());
  Serial.println("You typed : " + String(verif) + ". Answer is : " + String(random_test));
  while(Serial.available()) {Serial.read();}
  */
  delay(2000);
  HAL::off();
  delay(2000);
  HAL::on();
  delay(2000);
  HAL::setFastBlinkingLed(i);
  i++;
}
