#ifndef BROWSER_HPP
#define BROWSER_HPP

#define BROWSER_PAGE_MAX 10

class Browser {
public:
	static void init();
	static void setPagesCallbacks(void (*callback)());

private:
	static const int _buttonPinA;
	static const int _buttonPinB;

	static void _callback_A();
	static void _callback_B();

	static volatile int _page;

	static void (*_userCallback)();
};

#endif