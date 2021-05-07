// libmulti_thread.cpp: Contains source for the thread that manages the window.

#include "stdafx.h"
#include "libmulti.h"

DWORD WINAPI libmulti_window_thread(LPVOID lpThreadParameter) {
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	std::pair<HWND, int>* startup = reinterpret_cast<std::pair<HWND, int>*>(lpThreadParameter);
	HWND window = startup->first;
	int ncmdshow = startup->second;
	delete startup;
	startup = nullptr;

	// show the window and do all the window stuff on a separate thread...
	ShowWindow(window, ncmdshow);
	UpdateWindow(window);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (GetMessage(&msg, window, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	CoUninitialize();
	return static_cast<DWORD>(msg.wParam);
}
