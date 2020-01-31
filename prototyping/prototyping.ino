#include "src/HAL.hpp"
#include "src/hoursMinutes.hpp"

void setup() {
  HAL::init();
  Serial.begin(115200);
  randomSeed(analogRead(A7));
}

int random_test;

void loop() {
  random_test = int(random(60));
  displayMinute(random_test);
  while(!Serial.available()){ }
  int verif = int(Serial.parseInt());
  Serial.println("You typed : " + String(verif) + ". Answer is : " + String(random_test));
  while(Serial.available()) {Serial.read();}
}
