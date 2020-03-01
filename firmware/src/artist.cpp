#include "artist.hpp"

uint16_t Artist::hoursToLed(int h) {
  h = h%12;
  return 1<<h;
}

uint16_t Artist::minutesToLed(int m) {
  int five, ones = 0;
  
  five = (m%30) / 5;          // Number of led to light up
  five = (1<<(five + 1)) - 1; // Light all the led before

  // Insert #ifdef here
    ones = ~((1<<(12 - m%5)) - 1);
    
    if(m > 30) {
      five = five << 6;

      ones = ((1<<(m%5)) -1)<<1;
    }
  // Insert #endif here
  
  return (five | ones) & 0xFFF;
}

uint32_t Artist::decimalToLed(int d) {
  int dd = abs(d);
  bool isNeg = d < 0;

  uint16_t tens, ones;
  
  tens = dd / 10;
  tens = (1<<tens);

  ones = dd % 10;
  ones = (1<<(ones + 1)) - 1;
  ones &= 0xFFE;
  
  if(isNeg) ones |= (1<<11);

  return ( ((uint32_t) tens) << 16) | ones;
}