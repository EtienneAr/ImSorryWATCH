#ifndef BROWSER_HPP
#define BROWSER_HPP

typedef int (*pageCb)();

class Browser {
public:
	static void init();
	static void pointersReset();
	static void setPagesCallbacksA(pageCb callbacksA[], int lenA);
	static void setPagesCallbacksB(pageCb callbacksB[], int lenB);
	static void spinOnce();

private:
	static void _callbackButtonA();
	static void _callbackButtonB();

	static volatile int _pageCursor;
	static volatile int _pageNbA;
	static volatile int _pageNbB;
	static volatile int _pageToPrint;
	static volatile pageCb *_pageCallbacksA;
	static volatile pageCb *_pageCallbacksB;
	static volatile bool _turnOff;
};

#endif