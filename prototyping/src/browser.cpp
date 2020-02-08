#include "browser.hpp"

#include <Arduino.h>

const int Browser::_buttonPinA = 2;
const int Browser::_buttonPinB = 3;

volatile int Browser::_page;

void Browser::init() {
	Browser::_page = 0;
	attachInterrupt(digitalPinToInterrupt(_buttonPinA), Browser::_callback_A, RISING);
	attachInterrupt(digitalPinToInterrupt(_buttonPinB), Browser::_callback_B, RISING);
}

void Browser::_callback_A() {
	_page++;
	if(_page > BROWSER_PAGE_MAX) _page = BROWSER_PAGE_MAX;
	Serial.println(_page);
}

void Browser::_callback_B() {
	_page--;
	if(_page < 0) _page = 0;
	Serial.println(_page);
}