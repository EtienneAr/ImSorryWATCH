#ifndef BROWSER_HPP
#define BROWSER_HPP

 typedef void (*pageCb)();

class Browser {
public:
	static void init();
	static void setPagesCallbacks(pageCb callbacks[], int len);

private:
	static const int _buttonPinA;
	static const int _buttonPinB;

	static void _callback_A();
	static void _callback_B();

	static volatile int _page;
	static volatile int _pageNb;
	
	static volatile pageCb *_pageCallbacks;
};

#endif