#include "src/HAL.hpp"

void displayHour(int h) {
  h = h%12;
  HAL_applyLed(1<<h);
}

void displayMinute(int m) {
  int five = (m%30) / 5;
  five = (1<<(five + 1)) - 1;

  int ones = ~((1<<(12 - m%5)) - 1);
  
  if(m > 30) {
    five = five << 6;

    ones = ((1<<(m%5)) -1)<<1;
  }
  
  HAL_applyLed((five | ones) & 0xFFF);
}

void setup() {
  HAL_init();
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
