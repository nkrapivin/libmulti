// libmulti_pos.cpp: Getters/Setters for position (x,y,w,h) and so on.

#include "stdafx.h"
#include "libmulti.h"

dllx double libmulti_get_x(double index) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		double coord = -1.0;

		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		RECT rc{ 0, 0, 0, 0 };
		BOOL ok = GetClientRect(window, &rc);
		LastError = GetLastError();
		if (ok == TRUE) {
			POINT p{ rc.left, rc.top };
			ok = ClientToScreen(window, &p);
			LastError = GetLastError();
			if (ok == TRUE) {
				coord = p.x;
			}
		}
		LeaveVector();

		return coord;
	}
}

dllx double libmulti_get_y(double index) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		double coord = -1.0;

		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		RECT rc{ 0, 0, 0, 0 };
		BOOL ok = GetClientRect(window, &rc);
		LastError = GetLastError();
		if (ok == TRUE) {
			POINT p{ rc.left, rc.top };
			ok = ClientToScreen(window, &p);
			LastError = GetLastError();
			if (ok == TRUE) {
				coord = p.y;
			}
		}
		LeaveVector();

		return coord;
	}
}

dllx double libmulti_get_width(double index) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		double coord = -1.0;

		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		RECT rc{ 0, 0, 0, 0 };
		BOOL ok = GetClientRect(window, &rc);
		LastError = GetLastError();
		if (ok == TRUE) {
			coord = rc.right;
		}
		LeaveVector();

		return coord;
	}
}

dllx double libmulti_get_height(double index) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		double coord = -1.0;

		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		RECT rc{ 0, 0, 0, 0 };
		BOOL ok = GetClientRect(window, &rc);
		LastError = GetLastError();
		if (ok == TRUE) {
			coord = rc.bottom;
		}
		LeaveVector();

		return coord;
	}
}

dllx double libmulti_set_x(double index, double x) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		int coord = static_cast<int>(x);
		BOOL ok = FALSE;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;

		RECT empty; SetRectEmpty(&empty);
		AdjustWindowRectEx(&empty, static_cast<DWORD>(GetWindowLongPtrW(window, GWL_STYLE)), GetMenu(window) != nullptr, static_cast<DWORD>(GetWindowLongPtrW(window, GWL_EXSTYLE)));
		RECT client;
		GetClientRect(window, &client);
		POINT p{ 0, client.top };
		ClientToScreen(window, &p);

		ok = SetWindowPos(window, HWND_TOP, coord + empty.left, p.y + empty.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		LeaveVector();
		return ok;
	}
}

dllx double libmulti_set_y(double index, double y) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		int coord = static_cast<int>(y);
		BOOL ok = FALSE;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;

		RECT empty; SetRectEmpty(&empty);
		AdjustWindowRectEx(&empty, static_cast<DWORD>(GetWindowLongPtrW(window, GWL_STYLE)), GetMenu(window) != nullptr, static_cast<DWORD>(GetWindowLongPtrW(window, GWL_EXSTYLE)));
		RECT client;
		GetClientRect(window, &client);
		POINT p{ 0, client.top };
		ClientToScreen(window, &p);

		ok = SetWindowPos(window, HWND_TOP, p.x + empty.left, coord + empty.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		LeaveVector();
		return ok;
	}
}

dllx double libmulti_set_position(double index, double x, double y) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		int coord = static_cast<int>(x);
		int coord2 = static_cast<int>(y);
		BOOL ok = FALSE;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;

		// get the offsets of the non-client area
		RECT rc;
		SetRectEmpty(&rc);
		AdjustWindowRectEx(&rc, static_cast<DWORD>(GetWindowLongPtrW(window, GWL_STYLE)), GetMenu(window) != nullptr, static_cast<DWORD>(GetWindowLongPtrW(window, GWL_EXSTYLE)));

		// I have zero idea how it works, really. I don't understand how these calculations make it work.
		coord += rc.left;
		coord2 += rc.top;

		ok = SetWindowPos(window, HWND_TOP, coord, coord2, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		LastError = GetLastError();
		LeaveVector();
		return ok;
	}
}

dllx double libmulti_set_width(double index, double w) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		int coord = static_cast<int>(w);
		BOOL ok = FALSE;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;

		RECT empty; SetRectEmpty(&empty);
		AdjustWindowRectEx(&empty, static_cast<DWORD>(GetWindowLongPtrW(window, GWL_STYLE)), GetMenu(window) != nullptr, static_cast<DWORD>(GetWindowLongPtrW(window, GWL_EXSTYLE)));
		RECT rwindow;
		GetWindowRect(window, &rwindow);

		ok = SetWindowPos(window, HWND_TOP, 0, 0, coord + empty.right - empty.left, rwindow.bottom - rwindow.top, SWP_NOMOVE | SWP_NOZORDER);
		LeaveVector();
		return ok;
	}
}

dllx double libmulti_set_height(double index, double h) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		int coord = static_cast<int>(h);
		BOOL ok = FALSE;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;

		RECT empty; SetRectEmpty(&empty);
		AdjustWindowRectEx(&empty, static_cast<DWORD>(GetWindowLongPtrW(window, GWL_STYLE)), GetMenu(window) != nullptr, static_cast<DWORD>(GetWindowLongPtrW(window, GWL_EXSTYLE)));
		RECT rwindow;
		GetWindowRect(window, &rwindow);

		ok = SetWindowPos(window, HWND_TOP, 0, 0, rwindow.right - rwindow.left, coord + empty.bottom - empty.top, SWP_NOMOVE | SWP_NOZORDER);
		LeaveVector();
		return ok;
	}
}

dllx double libmulti_set_size(double index, double w, double h) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		int coord = static_cast<int>(w);
		int coord2 = static_cast<int>(h);
		BOOL ok = FALSE;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;

		RECT rc;
		SetRectEmpty(&rc);
		AdjustWindowRectEx(&rc, static_cast<DWORD>(GetWindowLongPtrW(window, GWL_STYLE)), GetMenu(window) != nullptr, static_cast<DWORD>(GetWindowLongPtrW(window, GWL_EXSTYLE)));
		
		// I have zero idea how it works, really.
		coord += rc.right - rc.left;
		coord2 += rc.bottom - rc.top;

		ok = SetWindowPos(window, HWND_TOP, 0, 0, coord, coord2, SWP_NOMOVE | SWP_NOZORDER);
		LastError = GetLastError();
		LeaveVector();
		return ok;
	}
}

dllx double libmulti_set_rectangle(double index, double x, double y, double w, double h) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		int ix = static_cast<int>(x),
			iy = static_cast<int>(y),
			iw = static_cast<int>(w),
			ih = static_cast<int>(h);

		BOOL ok = FALSE;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		RECT rc{ ix,iy,iw,ih };
		RECT empty; SetRectEmpty(&empty);
		AdjustWindowRectEx(&empty, static_cast<DWORD>(GetWindowLongPtrW(window, GWL_STYLE)), GetMenu(window) != nullptr, static_cast<DWORD>(GetWindowLongPtrW(window, GWL_EXSTYLE)));
		ok = SetWindowPos(window, HWND_TOP, rc.left + empty.left, rc.top + empty.top, rc.right + empty.right - empty.left, rc.bottom + empty.bottom - empty.top, SWP_NOZORDER);
		LastError = GetLastError();
		LeaveVector();

		return ok;
	}
}

dllx double libmulti_get_nonclient_left(double index) {
	if (!_libmulti_exists(index)) return 0.0;
	else {
		double v = 0.0;
		BOOL ok = FALSE;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		RECT rc;
		ok = SetRectEmpty(&rc) && AdjustWindowRectEx(&rc, static_cast<DWORD>(GetWindowLongPtrW(window, GWL_STYLE)), GetMenu(window) != nullptr, static_cast<DWORD>(GetWindowLongPtrW(window, GWL_EXSTYLE)));
		if (ok == TRUE) v = rc.left;
		LeaveVector();
		return v;
	}
}

dllx double libmulti_get_nonclient_top(double index) {
	if (!_libmulti_exists(index)) return 0.0;
	else {
		double v = 0.0;
		BOOL ok = FALSE;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		RECT rc;
		ok = SetRectEmpty(&rc) && AdjustWindowRectEx(&rc, static_cast<DWORD>(GetWindowLongPtrW(window, GWL_STYLE)), GetMenu(window) != nullptr, static_cast<DWORD>(GetWindowLongPtrW(window, GWL_EXSTYLE)));
		if (ok == TRUE) v = rc.top;
		LeaveVector();
		return v;
	}
}

dllx double libmulti_get_nonclient_right(double index) {
	if (!_libmulti_exists(index)) return 0.0;
	else {
		double v = 0.0;
		BOOL ok = FALSE;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		RECT rc;
		ok = SetRectEmpty(&rc) && AdjustWindowRectEx(&rc, static_cast<DWORD>(GetWindowLongPtrW(window, GWL_STYLE)), GetMenu(window) != nullptr, static_cast<DWORD>(GetWindowLongPtrW(window, GWL_EXSTYLE)));
		if (ok == TRUE) v = rc.right;
		LeaveVector();
		return v;
	}
}

dllx double libmulti_get_nonclient_bottom(double index) {
	if (!_libmulti_exists(index)) return 0.0;
	else {
		double v = 0.0;
		BOOL ok = FALSE;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		RECT rc;
		ok = SetRectEmpty(&rc) && AdjustWindowRectEx(&rc, static_cast<DWORD>(GetWindowLongPtrW(window, GWL_STYLE)), GetMenu(window) != nullptr, static_cast<DWORD>(GetWindowLongPtrW(window, GWL_EXSTYLE)));
		if (ok == TRUE) v = rc.bottom;
		LeaveVector();
		return v;
	}
}

dllx double libmulti_set_min_width(double index, double width) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		BOOL ok = FALSE;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		intptr_t* userdata = reinterpret_cast<intptr_t*>(GetWindowLongPtrW(window, GWLP_USERDATA));
		if (userdata != nullptr) {
			ok = TRUE;
			userdata[1] = static_cast<intptr_t>(width);
		}
		LeaveVector();
		return ok;
	}
}

dllx double libmulti_set_min_height(double index, double height) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		BOOL ok = FALSE;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		intptr_t* userdata = reinterpret_cast<intptr_t*>(GetWindowLongPtrW(window, GWLP_USERDATA));
		if (userdata != nullptr) {
			ok = TRUE;
			userdata[2] = static_cast<intptr_t>(height);
		}
		LeaveVector();
		return ok;
	}
}

dllx double libmulti_set_max_width(double index, double width) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		BOOL ok = FALSE;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		intptr_t* userdata = reinterpret_cast<intptr_t*>(GetWindowLongPtrW(window, GWLP_USERDATA));
		if (userdata != nullptr) {
			ok = TRUE;
			userdata[3] = static_cast<intptr_t>(width);
		}
		LeaveVector();
		return ok;
	}
}

dllx double libmulti_set_max_height(double index, double height) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		BOOL ok = FALSE;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		intptr_t* userdata = reinterpret_cast<intptr_t*>(GetWindowLongPtrW(window, GWLP_USERDATA));
		if (userdata != nullptr) {
			ok = TRUE;
			userdata[4] = static_cast<intptr_t>(height);
		}
		LeaveVector();
		return ok;
	}
}

dllx double libmulti_set_min_size(double index, double width, double height) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		BOOL ok = FALSE;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		intptr_t* userdata = reinterpret_cast<intptr_t*>(GetWindowLongPtrW(window, GWLP_USERDATA));
		if (userdata != nullptr) {
			ok = TRUE;
			userdata[1] = static_cast<intptr_t>(width);
			userdata[2] = static_cast<intptr_t>(height);
		}
		LeaveVector();
		return ok;
	}
}

dllx double libmulti_set_max_size(double index, double width, double height) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		BOOL ok = FALSE;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		intptr_t* userdata = reinterpret_cast<intptr_t*>(GetWindowLongPtrW(window, GWLP_USERDATA));
		if (userdata != nullptr) {
			ok = TRUE;
			userdata[3] = static_cast<intptr_t>(width);
			userdata[4] = static_cast<intptr_t>(height);
		}
		LeaveVector();
		return ok;
	}
}

dllx double libmulti_get_min_width(double index) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		double ret = -1.0;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		intptr_t* userdata = reinterpret_cast<intptr_t*>(GetWindowLongPtrW(window, GWLP_USERDATA));
		if (userdata != nullptr) ret = static_cast<double>(userdata[1]);
		LeaveVector();
		return ret;
	}
}

dllx double libmulti_get_min_height(double index) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		double ret = -1.0;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		intptr_t* userdata = reinterpret_cast<intptr_t*>(GetWindowLongPtrW(window, GWLP_USERDATA));
		if (userdata != nullptr) ret = static_cast<double>(userdata[2]);
		LeaveVector();
		return ret;
	}
}

dllx double libmulti_get_max_width(double index) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		double ret = -1.0;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		intptr_t* userdata = reinterpret_cast<intptr_t*>(GetWindowLongPtrW(window, GWLP_USERDATA));
		if (userdata != nullptr) ret = static_cast<double>(userdata[3]);
		LeaveVector();
		return ret;
	}
}

dllx double libmulti_get_max_height(double index) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		double ret = -1.0;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		intptr_t* userdata = reinterpret_cast<intptr_t*>(GetWindowLongPtrW(window, GWLP_USERDATA));
		if (userdata != nullptr) ret = static_cast<double>(userdata[4]);
		LeaveVector();
		return ret;
	}
}

dllx double libmulti_mouse_get_x(double index) {
	if (!_libmulti_exists(index)) return 0.0;
	else {
		double coord = 0.0;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		intptr_t* userdata = reinterpret_cast<intptr_t*>(GetWindowLongPtrW(window, GWLP_USERDATA));
		if (userdata != nullptr) coord = static_cast<double>(userdata[6]);
		LeaveVector();
		return coord;
	}
}

dllx double libmulti_mouse_get_y(double index) {
	if (!_libmulti_exists(index)) return 0.0;
	else {
		double coord = 0.0;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		intptr_t* userdata = reinterpret_cast<intptr_t*>(GetWindowLongPtrW(window, GWLP_USERDATA));
		if (userdata != nullptr) coord = static_cast<double>(userdata[7]);
		LeaveVector();
		return coord;
	}
}
