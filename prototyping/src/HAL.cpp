#include "HAL.hpp"

#include <Arduino.h>
#include <TimerOne.h>

const int HAL::_ledPin[] = {4, A3, A2, A1, A0, 12, 11, 10, 9, 7, 6, 5, 8};

volatile uint16_t HAL::_onLed = 0;
volatile uint16_t HAL::_blinkingLed = 0;
volatile int 	  HAL::_lastLedN = 0;
volatile long 	  HAL::_blinkCount = 0;
volatile long 	  HAL::_autoOffCount = -1;
volatile void 	  (*HAL::_autoOffCb)(void) = NULL;

void HAL::init() {
	HAL::_initLed();
	HAL::_initTimer();
}

void HAL::_initLed() {
  for(int i=0;i<13;i++) {
    pinMode(_ledPin[i], OUTPUT);
    digitalWrite(_ledPin[i], HIGH);
  }
}

void HAL::_initTimer() {
	Timer1.initialize(HAL_ULTRAFAST_BLINK_PERIOD);
	HAL::on();
}

void HAL::on() {
	Timer1.attachInterrupt(HAL::_blinker);
	HAL::_blinkCount = 0;
}

void HAL::off() {
	Timer1.detachInterrupt();
	HAL::clear();
}

void HAL::auto_off(unsigned int timeout_ms) {
	HAL::auto_off(timeout_ms, NULL);
}

void HAL::auto_off(unsigned int timeout_ms, void (*callback)(void)) {
	HAL::_autoOffCount = ((long) 1000 * timeout_ms) / HAL_ULTRAFAST_BLINK_PERIOD;
	HAL::_autoOffCb = callback;
}

void HAL::clear() {
	HAL::_onLed 	= 	(uint16_t) 0x0;
	HAL::_blinkingLed = (uint16_t) 0x0;
	HAL::_lastLedN	= 	(uint16_t) 0x0;
	for(int i=0;i<13;i++) {
		digitalWrite(HAL::_ledPin[i], LOW);
	}
}

void HAL::applyLed(uint16_t config) {
  HAL::_onLed = config;
  for(int i=0;i<13;i++) {
    digitalWrite(_ledPin[i], (config & 1<<i) != 0 );
  }
}

void HAL::setBlinkingLed(uint16_t config) {
	_blinkingLed = config;

}

void HAL::setLastLedNumber(int n) {
	_lastLedN = n;
}

void HAL::_blinker() {
	HAL::_blinkCount++;

	// Normal blinking
	if(    !(_blinkCount %  HAL_FAST_BLINK_SUB_PERIOD     )
		|| !(_blinkCount % (HAL_FAST_BLINK_SUB_PERIOD /2) )
		|| !(_blinkCount %  HAL_SLOW_BLINK_SUB_PERIOD     )
		|| !(_blinkCount % (HAL_SLOW_BLINK_SUB_PERIOD /2) )
	) {
		for(int i=0;i<13;i++) {
			if(HAL::_blinkingLed & 1<<i) {
				if(HAL::_onLed & 1<<i) {
					digitalWrite(_ledPin[i], (_blinkCount % HAL_FAST_BLINK_SUB_PERIOD) >= HAL_FAST_BLINK_SUB_PERIOD/2);
				} else {
					digitalWrite(_ledPin[i], (_blinkCount % HAL_SLOW_BLINK_SUB_PERIOD) >= HAL_SLOW_BLINK_SUB_PERIOD/2);
				}
			}
		}
	}

	// Number display on the last led
	if(_blinkCount % (HAL_LAST_LED_PAUSE_PERIOD + _lastLedN * 2) <= _lastLedN * 2) {
		digitalWrite(_ledPin[12], _blinkCount % 2);
	}

	//Auto off
	if(HAL::_autoOffCount == 0) {
		HAL::off();
		HAL::_autoOffCount = -1;
		if(HAL::_autoOffCb != NULL) HAL::_autoOffCb();
	}

	if(HAL::_autoOffCount > 0) HAL::_autoOffCount--;
}