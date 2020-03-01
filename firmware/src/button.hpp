#ifndef BUTTON_HPP
#define BUTTON_HPP

#define BUTTON_DEBOUNCE_LEN 1024

class Button {
public:
	static void init(int pin_button_A, int pin_button_B);
	static void setCallbacks(void (*callbackA)(), void (*callbackB)());

private:
	static volatile int _pinButtonA;
	static volatile int _pinButtonB;
	static volatile void (*_callbackA)();
	static volatile void (*_callbackB)();
	static void _callbackButtonA();
	static void _callbackButtonB();
	static void _debounce();
};

#endif