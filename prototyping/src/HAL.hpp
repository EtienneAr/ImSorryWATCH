#ifndef HAL_HPP
#define HAL_HPP

#include <stdint.h>

class HAL {

public:
	static void init();
	static void applyLed(uint16_t config);

private:
	static void _initLed();

};

#endif