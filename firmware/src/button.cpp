#include "button.hpp"
#include "Arduino.h"

#define BUTTON_DEBOUNCE_TIMING_MS 150

volatile int Button::_pinButtonA = -1;
volatile int Button::_pinButtonB = -1;

volatile void (*Button::_callbackA)() = NULL;
volatile void (*Button::_callbackB)() = NULL;

volatile unsigned long Button::_lastPressA = 0;
volatile unsigned long Button::_lastPressB = 0;

void Button::init(int pin_button_A, int pin_button_B) {
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
	if(millis() - Button::_lastPressA < BUTTON_DEBOUNCE_TIMING_MS) return;
	Button::_lastPressA = millis();
	
	if(digitalRead(Button::_pinButtonA) == LOW) {
		if(Button::_callbackA != NULL) {
			Button::_callbackA();
		}
	}
}

void Button::_callbackButtonB() {
	if(millis() - Button::_lastPressB < BUTTON_DEBOUNCE_TIMING_MS) return;
	Button::_lastPressB = millis();
	
	if(digitalRead(Button::_pinButtonB) == LOW) {
		if(Button::_callbackB != NULL) {
			Button::_callbackB();
		}
	}
}