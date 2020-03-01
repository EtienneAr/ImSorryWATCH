#ifndef BROWSER_HPP
#define BROWSER_HPP

typedef void (*pageCb)();

class Browser {
public:
	static void init();
	static void pointersReset();
	static void setPagesCallbacks(pageCb callbacks[], int len);
	static void spinOnce();

private:
	static void _callbackButtonA();
	static void _callbackButtonB();

	static volatile int _pageCursor;
	static volatile int _pageNb;
	static volatile int _pageToPrint;
	static volatile pageCb *_pageCallbacks;
};

#endif