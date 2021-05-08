// libmulti_focus.cpp: Focus/Active related functions.

#include "stdafx.h"
#include "libmulti.h"

static HWND MainGameWindow{ nullptr };

LIBMULTI_DOUBLE libmulti_set_game_window(char* hwnd) {
	EnterVector();
	HWND old = MainGameWindow;
	MainGameWindow = reinterpret_cast<HWND>(hwnd);
	LeaveVector();
	return MainGameWindow != old;
}

LIBMULTI_DOUBLE libmulti_set_game_window_real(double hwnd) {
	EnterVector();
	HWND old = MainGameWindow;
	MainGameWindow = reinterpret_cast<HWND>(static_cast<LONG_PTR>(hwnd));
	LeaveVector();
	return MainGameWindow != old;
}

LIBMULTI_DOUBLE libmulti_get_active_window(void) {
	double ret = -2.0; // -2 - active window is not a window that we're aware of.

	EnterVector();
	HWND h = GetActiveWindow();
	if (h == MainGameWindow)
		ret = -1.0; // -1 - game's window is active
	else {
		for (std::size_t i = 0; i < vecWindows.size(); i++) {
			HWND window = vecWindows[i].first;
			if (window == nullptr) continue; // nope.
			if (h == window) {
				ret = static_cast<double>(i);
				break;
			}
		}
	}
	LeaveVector();

	return ret;
}

LIBMULTI_DOUBLE libmulti_get_foreground_window(void) {
	double ret = -2.0; // -2 - active window is not a window that we're aware of.

	EnterVector();
	HWND h = GetForegroundWindow();
	if (h == MainGameWindow)
		ret = -1.0; // -1 - game's window is active
	else {
		for (std::size_t i = 0; i < vecWindows.size(); i++) {
			HWND window = vecWindows[i].first;
			if (window == nullptr) continue; // nope.
			if (h == window) {
				ret = static_cast<double>(i);
				break;
			}
		}
	}
	LeaveVector();

	return ret;
}

LIBMULTI_DOUBLE libmulti_set_active_window(double index) {
	if (index < 0.0) // anything below 0 means Game's window (not using any engine names here hehe)
		SetActiveWindow(MainGameWindow);
	else {
		if (!_libmulti_exists(index)) return 0.0;
		EnterVector();
		SetActiveWindow(vecWindows[static_cast<std::size_t>(index)].first);
		LeaveVector();
	}

	return 1.0;
}

LIBMULTI_DOUBLE libmulti_set_foreground_window(double index) {
	if (index < 0.0) // anything below 0 means Game's window (not using any engine names here hehe)
		SetForegroundWindow(MainGameWindow);
	else {
		if (!_libmulti_exists(index)) return 0.0;
		EnterVector();
		SetForegroundWindow(vecWindows[static_cast<std::size_t>(index)].first);
		LeaveVector();
	}

	return 1.0;
}

LIBMULTI_DOUBLE libmulti_has_focus(double index) {
	if (index < 0.0)
		return MainGameWindow == GetForegroundWindow();
	else {
		BOOL has = FALSE;
		EnterVector();
		has = vecWindows[static_cast<std::size_t>(index)].first == GetForegroundWindow();
		LeaveVector();

		return has;
	}
}
