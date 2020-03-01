#ifndef ARTIST_HPP
#define ARTIST_HPP

#include <Arduino.h>

class Artist {
public:
	static uint16_t hoursToLed(int h);
	static uint16_t minutesToLed(int m);
	static uint32_t decimalToLed(int d);
};

#endif