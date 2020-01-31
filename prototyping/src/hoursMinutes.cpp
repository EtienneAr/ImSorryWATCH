#include <Arduino.h>
#include "hoursMinutes.hpp"
#include "HAL.hpp"

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