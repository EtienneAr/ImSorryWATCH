#include "button.hpp"
#include "Arduino.h"

volatile int Button::_pinButtonA = -1;
volatile int Button::_pinButtonB = -1;

volatile buttonCb Button::_callbackA;
volatile buttonCb Button::_callbackB;

void Button::init(int pin_button_A, int pin_button_B) {
	Button::_callbackA = NULL;
	Button::_callbackB = NULL;

	Button::_pinButtonA = pin_button_A;
	Button::_pinButtonB = pin_button_B;
	
	pinMode(pin_button_A, INPUT_PULLUP);
	pinMode(pin_button_B, INPUT_PULLUP);
	
	attachInterrupt(digitalPinToInterrupt(pin_button_A), Button::_callbackButtonA, CHANGE);
	attachInterrupt(digitalPinToInterrupt(pin_button_B), Button::_callbackButtonB, CHANGE);
}

void Button::setCallbacks(void (*callbackA)(), void (*callbackB)()) {
	Button::_callbackA = callbackA;
	Button::_callbackB = callbackB;
}

void Button::_callbackButtonA() {
	if(digitalRead(Button::_pinButtonA) == HIGH) {
		if(Button::_callbackA != NULL) {
			Button::_callbackA();
		}
	}
	Button::_debounce();
}

void Button::_callbackButtonB() {
	if(digitalRead(Button::_pinButtonB) == HIGH) {
		if(Button::_callbackB != NULL) {
			Button::_callbackB();
		}
	}
	Button::_debounce();
}

void Button::_debounce() {
	for(int i=0;i<BUTTON_DEBOUNCE_LEN;i++) {
		__asm__("nop\n\t");
	}
}