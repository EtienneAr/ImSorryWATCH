#include "browser.hpp"
#include "button.hpp"
#include "HAL.hpp"

#include <Arduino.h>

volatile int Browser::_pageCursor;
volatile int Browser::_pageNbA;
volatile int Browser::_pageNbB;
volatile int Browser::_pageToPrint;
volatile pageCb *Browser::_pageCallbacksA;
volatile pageCb *Browser::_pageCallbacksB;
volatile bool Browser::_turnOff;

/*
 * This function is not fully robust to changes of variabl during it's execution (_pageToPrint)
 * But disabling all the interrupts for a while can cause problems to other libraries like HAL
 * (for blinking LED).
 * So the duration of the critical code is limited to just a couple of lines and not a full call 
 * to a function...
*/
void Browser::spinOnce() {
	if(_pageToPrint != 0) {
		volatile int __printedPage = _pageToPrint; 	// Save which page is being printed
													//because _pageToPrint can be change by an interrupt
													//while the callback is being executed
		HAL::on();

		int  timeOut_ms = -1;
		if(_pageToPrint > 0) {
			HAL::setLastLedNumber(__printedPage);
			timeOut_ms = ( Browser::_pageCallbacksA[_pageToPrint - 1] ) ();
		} else if (_pageToPrint < 0) {
			HAL::setLastLedNumber(-__printedPage);
			timeOut_ms = ( Browser::_pageCallbacksB[-1 - _pageToPrint] ) ();
		}
		
		HAL::auto_off(timeOut_ms, Browser::pointersReset);

		if(__printedPage == _pageToPrint) _pageToPrint = 0; //If the _pageToPrint haven't been changed
					// Then _pageToPrint can be set to 0 and nothing will be set at the next loop
	}
	if(_turnOff == true) {
		HAL::off();
		Browser::_turnOff = false;
	}
}

void Browser::init() {
	Browser::_pageNbA = 0;
	Browser::_pageNbB = 0;
	Browser::_turnOff = false;
	Browser::pointersReset();

	Button::setCallbacks(Browser::_callbackButtonA, Browser::_callbackButtonB);
}

void Browser::pointersReset() {
	Browser::_pageCursor = 0;
	Browser::_pageToPrint = 0;
}

void Browser::_callbackButtonA() {
	if(_pageCursor >= 0) {
		if(_pageCursor < _pageNbA) {
			_pageCursor++ ;
			_pageToPrint = _pageCursor;
		}
	} else {
		Browser::pointersReset();
		Browser::_turnOff = true;
	}
}

void Browser::_callbackButtonB() {
	if(_pageCursor <= 0) {
		if(_pageCursor > -_pageNbB) {
			_pageCursor--;
			_pageToPrint = _pageCursor;
		}
	} else {
		Browser::pointersReset();
		Browser::_turnOff = true;
	}
}

void Browser::setPagesCallbacksA(pageCb callbacksA[], int lenA) {
	Browser::_pageCallbacksA = callbacksA;
	Browser::_pageNbA = lenA;
}

void Browser::setPagesCallbacksB(pageCb callbacksB[], int lenB) {
	Browser::_pageCallbacksB = callbacksB;
	Browser::_pageNbB = lenB;
}