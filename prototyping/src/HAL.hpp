#ifndef HAL_HPP
#define HAL_HPP

#include <stdint.h>

#define HAL_ULTRAFAST_BLINK_PERIOD 100000 //us
#define HAL_FAST_BLINK_SUB_PERIOD 2
#define HAL_SLOW_BLINK_SUB_PERIOD 8 

class HAL {

public:
	static void init();
	static void applyLed(uint16_t config);

	static void setSlowBlinkingLed(uint16_t config);
	static void setFastBlinkingLed(uint16_t config);

private:
	static uint16_t _slowBlinkingLed;
	static uint16_t _fastBlinkingLed;
	static int 		_blinkCount;

	static void _initLed();
	static void _initTimer();
	static void _blinker();
};

#endif