#include <Arduino.h>
#include "hoursMinutes.hpp"
#include "HAL.hpp"

uint16_t hoursToLed(int h) {
  h = h%12;
  return 1<<h;
}

uint16_t minutesToLed(int m) {
  int five = (m%30) / 5;
  five = (1<<(five + 1)) - 1;

  int ones = ~((1<<(12 - m%5)) - 1);
  
  if(m > 30) {
    five = five << 6;

    ones = ((1<<(m%5)) -1)<<1;
  }
  
  return (five | ones) & 0xFFF;
}