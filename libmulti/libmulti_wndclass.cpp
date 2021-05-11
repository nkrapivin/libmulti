// libmulti_class.cpp: Contains a function used to register the window class.

#include "stdafx.h"
#include "libmulti.h"

BOOL unregister_window_class(ATOM c, HINSTANCE hi) {
	return UnregisterClass(reinterpret_cast<LPCTSTR>(c), hi);
}

ATOM register_window_class(WNDPROC p) {
	WNDCLASSEX wnd;
	wnd.cbSize = sizeof(wnd);
	wnd.style = CS_HREDRAW | CS_VREDRAW;
	wnd.lpfnWndProc = p;
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hInstance = hModule;
	wnd.hIcon = nullptr;
	wnd.hCursor = libmulti_cursor_get_from_gm(0);
	wnd.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOWFRAME);
	wnd.lpszMenuName = nullptr;
	wnd.lpszClassName = TEXT("LibMultiNikIsAFool");
	wnd.hIconSm = nullptr;
	return RegisterClassEx(&wnd);
}
