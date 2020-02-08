#ifndef BROWSER_HPP
#define BROWSER_HPP

class Browser {
public:
	static void init();

private:
	static const int _buttonPinA;
	static const int _buttonPinB;

	static void callback_A();
	static void callback_B();
};

#endif