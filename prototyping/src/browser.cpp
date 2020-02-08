#include "browser.hpp"

#include <Arduino.h>

const int Browser::_buttonPinA = 2;
const int Browser::_buttonPinB = 3;

void Browser::init() {
	attachInterrupt(digitalPinToInterrupt(_buttonPinA), Browser::callback_A, RISING);
	attachInterrupt(digitalPinToInterrupt(_buttonPinB), Browser::callback_B, RISING);
}

void Browser::callback_A() {
	Serial.println("A");
}

void Browser::callback_B() {
	Serial.println("B");
}