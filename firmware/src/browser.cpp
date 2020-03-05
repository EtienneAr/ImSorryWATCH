#include "browser.hpp"
#include "button.hpp"
#include "HAL.hpp"

#include <Arduino.h>

volatile int Browser::_pageCursor;
volatile int Browser::_pageNb;
volatile int Browser::_pageToPrint;
volatile pageCb *Browser::_pageCallbacks;

/*
 * This function is not fully robust to changes of variabl during it's execution (_pageToPrint)
 * But disabling all the interrupts for a while can cause problems to other libraries like HAL
 * (for blinking LED).
 * So the duration of the critical code is limited to just a couple of lines and not a full call 
 * to a function...
*/
void Browser::spinOnce() {
	if(_pageToPrint != -1) {
		volatile int __printedPage = _pageToPrint; 	// Save which page is being printed
													//because _pageToPrint can be change by an interrupt
													//while the callback is being executed
		HAL::on();
  		HAL::setLastLedNumber(__printedPage + 1);

		int  timeOut_ms = ( Browser::_pageCallbacks[_pageToPrint] ) ();
		
		if(timeOut_ms != -1) HAL::auto_off(timeOut_ms, Browser::pointersReset);

		if(__printedPage == _pageToPrint) _pageToPrint = -1; //If the _pageToPrint haven't been changed
					// Then _pageToPrint can be set to -1 and nothing will be set at the next loop
	}
}

void Browser::init() {
	Browser::_pageNb = 0;
	Browser::pointersReset();

	Button::setCallbacks(Browser::_callbackButtonA, Browser::_callbackButtonB);
}

void Browser::pointersReset() {
	Browser::_pageCursor = -1;
	Browser::_pageToPrint = -1;
	Serial.println("Pointers reset");
}

void Browser::_callbackButtonA() {
	if(_pageCursor < _pageNb - 1) {
		_pageCursor++ ;
		_pageToPrint = _pageCursor;
	}
}

void Browser::_callbackButtonB() {
	if(_pageCursor > 0) {
		_pageCursor--;
		_pageToPrint = _pageCursor;
	}
}

void Browser::setPagesCallbacks(pageCb callbacks[], int len) {
	Browser::_pageCallbacks = callbacks;
	Browser::_pageNb = len;
}