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
	static void auto_off(unsigned int timeout_ms);
	static void auto_off(unsigned int timeout_ms, void (*callback)(void));

	static void applyLed(uint16_t config);
	static void setBlinkingLed(uint16_t config);
	static void setLastLedNumber(int n);

	static void clear();
private:
	static volatile uint16_t _onLed;
	static volatile uint16_t _blinkingLed;
	static volatile int 	 _lastLedN;
	static volatile long 	 _blinkCount;
	static volatile long 	 _autoOffCount;
	static volatile void 	 (*_autoOffCb)(void);

	static void _initLed();
	static void _initTimer();
	static void _blinker();

	static const int _ledPin[];
};

#endif