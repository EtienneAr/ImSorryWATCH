#include "src/HAL.hpp"
#include "src/hoursMinutes.hpp"

void setup() {
  Serial.begin(115200);
  HAL::init();
  randomSeed(analogRead(A7));
  HAL::setSlowBlinkingLed(0xAAA);
  HAL::setFastBlinkingLed(0x555);
}

int random_test;

void loop() {
  /*
  random_test = int(random(60));
  displayMinute(random_test);
  while(!Serial.available()){ }
  int verif = int(Serial.parseInt());
  Serial.println("You typed : " + String(verif) + ". Answer is : " + String(random_test));
  while(Serial.available()) {Serial.read();}
  */
}
