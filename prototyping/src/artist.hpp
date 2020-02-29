#ifndef ARTIST_HPP
#define ARTIST_HPP

#include <Arduino.h>

#define ETIENNE_SPECIALS

class Artist {
public:
	static uint16_t hoursToLed(int h);
	static uint16_t minutesToLed(int m);

};

#endif