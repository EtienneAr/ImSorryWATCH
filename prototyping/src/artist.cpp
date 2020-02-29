#include "artist.hpp"

uint16_t Artist::hoursToLed(int h) {
  h = h%12;
  return 1<<h;
}

uint16_t Artist::minutesToLed(int m) {
  int five, ones = 0;
  
  five = (m%30) / 5;          // Number of led to light up
  five = (1<<(five + 1)) - 1; // Light all the led before

  #ifdef ETIENNE_SPECIALS
    ones = ~((1<<(12 - m%5)) - 1);
    
    if(m > 30) {
      five = five << 6;

      ones = ((1<<(m%5)) -1)<<1;
    }
  #endif
  
  return (five | ones) & 0xFFF;
}