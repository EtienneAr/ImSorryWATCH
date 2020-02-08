#include "browser.hpp"

#include <Arduino.h>

const int Browser::_buttonPinA = 2;
const int Browser::_buttonPinB = 3;

volatile pageCb *Browser::_pageCallbacks;

volatile int Browser::_page;
volatile int Browser::_pageNb;

void Browser::init() {
	Browser::_page = 0;
	Browser::_pageNb = 0;
	attachInterrupt(digitalPinToInterrupt(_buttonPinA), Browser::_callback_A, RISING);
	attachInterrupt(digitalPinToInterrupt(_buttonPinB), Browser::_callback_B, RISING);
}

void Browser::_callback_A() {
	if(_page < _pageNb - 1) _page++ ;
	Serial.println(_page);
	(Browser::_pageCallbacks[_page])();
}

void Browser::_callback_B() {
	if(_page > 0) _page--;
	Serial.println(_page);
	(Browser::_pageCallbacks[_page])();
}

void Browser::setPagesCallbacks(pageCb callbacks[], int len) {
	Browser::_pageCallbacks = callbacks;
	Browser::_pageNb = len;
}