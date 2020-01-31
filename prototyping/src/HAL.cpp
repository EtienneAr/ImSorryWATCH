#include "HAL.hpp"

#include <Arduino.h>
#include <TimerOne.h>

int HAL::_ledPin[] = {4, A3, A2, A1, A0, 12, 11, 10, 9, 7, 6, 5, 8};

uint16_t HAL::_slowBlinkingLed = 0;
uint16_t HAL::_fastBlinkingLed = 0;
int 	 HAL::_lastLedN = 0;
int 	 HAL::_blinkCount = 0;

void HAL::_initLed() {
  for(int i=0;i<13;i++) {
    pinMode(_ledPin[i], OUTPUT);
    digitalWrite(_ledPin[i], HIGH);
  }
}

void HAL::_initTimer() {
	Timer1.initialize(HAL_ULTRAFAST_BLINK_PERIOD);
	Timer1.attachInterrupt(HAL::_blinker);
}

void HAL::init() {
	HAL::_initLed();
	HAL::_initTimer();
}

void HAL::applyLed(uint16_t config) {
  for(int i=0;i<13;i++) {
    digitalWrite(_ledPin[i], (config & 1<<i) != 0 );
  }
}

void HAL::setSlowBlinkingLed(uint16_t config) {
	_slowBlinkingLed = config;
}

void HAL::setFastBlinkingLed(uint16_t config) {
	_fastBlinkingLed = config;
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
			if(HAL::_fastBlinkingLed & 1<<i) {
				digitalWrite(_ledPin[i], (_blinkCount % HAL_FAST_BLINK_SUB_PERIOD) >= HAL_FAST_BLINK_SUB_PERIOD/2);
			} else if(HAL::_slowBlinkingLed & 1<<i) {
				digitalWrite(_ledPin[i], (_blinkCount % HAL_SLOW_BLINK_SUB_PERIOD) >= HAL_SLOW_BLINK_SUB_PERIOD/2);
			}
		}
	}

	// Number display on the last led
	if(_blinkCount % (HAL_LAST_LED_PAUSE_PERIOD + _lastLedN * 2) <= _lastLedN * 2) {
		digitalWrite(_ledPin[12], _blinkCount % 2);
	}
}