#ifndef HAL_HPP
#define HAL_HPP

#include <stdint.h>

#define HAL_ULTRAFAST_BLINK_PERIOD 100000 //us
#define HAL_FAST_BLINK_SUB_PERIOD 2
#define HAL_SLOW_BLINK_SUB_PERIOD 8 
#define HAL_LAST_LED_PAUSE_PERIOD 4 

class HAL {

public:
	static void init();

	static void on();
	static void off();

	static void applyLed(uint16_t config);
	static void setSlowBlinkingLed(uint16_t config);
	static void setFastBlinkingLed(uint16_t config);
	static void setLastLedNumber(int n);

private:
	static uint16_t _slowBlinkingLed;
	static uint16_t _fastBlinkingLed;
	static int 		_lastLedN;
	static int 		_blinkCount;

	static void _initLed();
	static void _initTimer();
	static void _blinker();

	static int _ledPin[];
};

#endif