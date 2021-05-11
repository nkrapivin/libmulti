// libmulti.cpp: Core libMulti functions.

#include "stdafx.h"
#include "libmulti.h"

HMODULE hModule{ nullptr };
static ATOM nikWindowClass{ 0 };

std::vector<std::pair<HWND, CMultiD2D*>> vecWindows{ };
DWORD LastError{ ERROR_SUCCESS };
static char* LastString{ nullptr };
static CRITICAL_SECTION* Mutex{ nullptr };
static bool IsLegacy{ false };
bool AltRGBMode{ false };

void EnterVector() { EnterCriticalSection(Mutex); }
void LeaveVector() { LeaveCriticalSection(Mutex); }

bool _libmulti_exists(double index) {
	bool ret = true;
	EnterVector();
	// out of bounds check
	if (index < 0.0 || index >= vecWindows.size())
		ret = false;
	// already freed check
	if (ret) {
		const auto& p = vecWindows[static_cast<std::size_t>(index)];
		if (p.first == nullptr || p.second == nullptr)
			ret = false;
	}
	LeaveVector();
	// it's ok
	return ret;
}

static void _libmulti_free() {
	EnterVector();
	if (LastString != nullptr) {
		delete[] LastString;
		LastString = nullptr;
	}
	LeaveVector();
}

CBDispatch_t CBDispatch{ nullptr };
CBCreateDsMap_t CBCreateDsMap{ nullptr };
CBDsMapAddReal_t CBDsMapAddReal{ nullptr };
CBDsMapAddString_t CBDsMapAddString{ nullptr };

static std::size_t _libmulti_find_free() {
	std::size_t ret = 0;

	EnterVector();
	ret = vecWindows.size();
	for (std::size_t i = 0; i < ret; i++) {
		const auto& p = vecWindows[i];
		if (p.first == nullptr || p.second == nullptr) {
			ret = i;
			break;
		}
	}
	LeaveVector();

	return ret;
}

static double _winapi_to_gm_mouse(UINT Msg) {
	switch (Msg) {
		case WM_LBUTTONUP:
		case WM_LBUTTONDOWN:
			return 1.0; // mb_left
		case WM_RBUTTONUP:
		case WM_RBUTTONDOWN:
			return 2.0; // mb_right
		case WM_MBUTTONUP:
		case WM_MBUTTONDOWN:
			return 3.0; // mb_middle
		default:
			return -1.0;
	}
}

static const char* _winapi_msg_to_name(UINT Msg) {
	switch (Msg) {
		case WM_LBUTTONDOWN: return "libmulti_leftdown";
		case WM_LBUTTONUP: return "libmulti_leftup";
		case WM_RBUTTONDOWN: return "libmulti_rightdown";
		case WM_RBUTTONUP: return "libmulti_rightup";
		case WM_MBUTTONDOWN: return "libmulti_middledown";
		case WM_MBUTTONUP: return "libmulti_middleup";
		default: return nullptr;
	}
}

static void _winapi_gm_mouse_event(double window, UINT Msg, WPARAM wParam, LPARAM lParam) {
	double mcode = _winapi_to_gm_mouse(Msg);
	double zero = 0.0;
	if (mcode != -1.0) {
		double xpos = GET_X_LPARAM(lParam);
		double ypos = GET_Y_LPARAM(lParam);
		int async_load = CBCreateDsMap(4,
			"event_type", zero, _winapi_msg_to_name(Msg),
			"window", window, nullptr,
			"x", xpos, nullptr,
			"y", ypos, nullptr
		);
		CBDispatch(async_load, EVENT_OTHER_SOCIAL);
	}
}

static bool _winapi_gm_paste_event(HWND hWnd, double window) {
	const double zero = 0.0;
	if (IsClipboardFormatAvailable(CF_UNICODETEXT) == TRUE) {
		char* mbclipdata = nullptr;
		int need = 0;
		LPCWSTR clipdata = nullptr;
		BOOL ok = FALSE;

		ok = OpenClipboard(hWnd);
		if (ok == TRUE) {
			clipdata = reinterpret_cast<LPCWSTR>(GetClipboardData(CF_UNICODETEXT));
			if (clipdata != nullptr) {
				need = WideCharToMultiByte(IsLegacy ? CP_OEMCP : CP_UTF8, 0, clipdata, -1, nullptr, 0, nullptr, nullptr);
				if (need > 0) {
					mbclipdata = new char[need];
					need = WideCharToMultiByte(IsLegacy ? CP_OEMCP : CP_UTF8, 0, clipdata, -1, mbclipdata, need, nullptr, nullptr);
				}
			}
			ok = CloseClipboard();
		}

		if (ok == TRUE) {
			int async_load = CBCreateDsMap(3,
				"event_type", zero, "libmulti_pastetext",
				"window", window, nullptr,
				"contents", zero, mbclipdata // TODO!
			);
			CBDispatch(async_load, EVENT_OTHER_SOCIAL);
		}

		if (mbclipdata != nullptr) {
			delete[] mbclipdata;
			mbclipdata = nullptr;
		}

		return true;
	}
	else {
		return false;
	}
}

static LRESULT WINAPI WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	intptr_t* userdata = reinterpret_cast<intptr_t*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(tme);
	tme.hwndTrack = hWnd;
	tme.dwFlags = TME_HOVER | TME_LEAVE;
	tme.dwHoverTime = HOVER_DEFAULT;

	if (userdata == nullptr) {
		if (Msg == WM_CREATE) {
			printf("WM_CREATE, %p\n", hWnd);
			fflush(stdout);
			TrackMouseEvent(&tme);
		}
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}

	intptr_t
		wind = userdata[0],
		minW = userdata[1],
		minH = userdata[2],
		maxW = userdata[3],
		maxH = userdata[4];

	CMultiD2D* d2d = nullptr;
	if (_libmulti_exists(static_cast<double>(wind))) {
		d2d = vecWindows[wind].second;
	}

	// gm stuff, ignore:
	const double window = static_cast<double>(wind);
	const double zero = 0.0;
	

	EnterVector();
	LRESULT ret = 0;
	switch (Msg) {
		case WM_CLOSE: {
			DestroyWindow(hWnd);
			int async_load = CBCreateDsMap(2,
				"event_type", zero, "libmulti_close",
				"window", window, nullptr
			);
			CBDispatch(async_load, EVENT_OTHER_SOCIAL);
			break;
		}

		case WM_CHAR: {
			// paste...
			if (wParam == 0x16) {
				if (_winapi_gm_paste_event(hWnd, window)) break;
			}

			char mch[8]{ '\0' }; // (8 - 1) characters should be more than enough. (7 cuz nullbyte)
			WCHAR wch = static_cast<WCHAR>(wParam);
			// process exactly one character.
			// size - 1 because the function won't handle a null byte.
			WideCharToMultiByte(IsLegacy ? CP_OEMCP : CP_UTF8, 0, &wch, 1, mch, sizeof(mch) - 1, nullptr, nullptr);

			double w_char = static_cast<double>(wParam);
			// me can't do bit arithmetic so there we go:
			double w_repeat_count = LOWORD(lParam);
			double w_scancode     = (HIWORD(lParam) & 0x00FF);
			double w_is_extended  = (HIWORD(lParam) & KF_EXTENDED) != 0;
			double w_reserved     = (HIWORD(lParam) & (~(KF_EXTENDED | KF_ALTDOWN | KF_REPEAT | KF_UP))); // lol.
			double w_context      = (HIWORD(lParam) & KF_ALTDOWN) != 0;
			double w_previous     = (HIWORD(lParam) & KF_REPEAT) != 0;
			double w_transition   = (HIWORD(lParam) & KF_UP) != 0;
			
			// since it's a variadic function some weird stuff is needed
			// (for example the `zero` thing, so the compiler knows the type of the variable)
			int async_load = CBCreateDsMap(11,
				"event_type", zero, "libmulti_input",
				"window", window, nullptr,
				"character", w_char, nullptr,
				"as_string", zero, &mch,
				"repeat_count", w_repeat_count, nullptr,
				"scan_code", w_scancode, nullptr,
				"is_extended_key", w_is_extended, nullptr,
				"reserved", w_reserved, nullptr,
				"context_code", w_context, nullptr,
				"previous_state", w_previous, nullptr,
				"transition_state", w_transition, nullptr
			);
			CBDispatch(async_load, EVENT_OTHER_SOCIAL);
			break;
		}

		case WM_SIZE: {
			UINT width = LOWORD(lParam);
			UINT height = HIWORD(lParam);
			d2d->OnResize(width, height);

			double d_width = width;
			double d_height = height;

			int async_load = CBCreateDsMap(4,
				"event_type", zero, "libmulti_size",
				"window", window, nullptr,
				"new_width", d_width, nullptr,
				"new_height", d_height, nullptr
			);
			CBDispatch(async_load, EVENT_OTHER_SOCIAL);

			break;
		}

		case WM_DISPLAYCHANGE: {
			InvalidateRect(hWnd, nullptr, FALSE);
			break;
		}

		case WM_PAINT: {
			d2d->Create(hWnd, AltRGBMode);
			d2d->OnRender();
			ValidateRect(hWnd, nullptr);
			break;
		}

		case WM_LBUTTONUP:
		case WM_LBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_MBUTTONDOWN: {
			_winapi_gm_mouse_event(window, Msg, wParam, lParam);
			break;
		}

		case WM_MOUSEHOVER: {
			double xpos = GET_X_LPARAM(lParam);
			double ypos = GET_Y_LPARAM(lParam);
			int async_load = CBCreateDsMap(4,
				"event_type", zero, "libmulti_mousehover",
				"window", window, nullptr,
				"x", xpos, nullptr,
				"y", ypos, nullptr
			);
			CBDispatch(async_load, EVENT_OTHER_SOCIAL);
			break;
		}

		case WM_MOUSEMOVE: {
			int mouse_x = GET_X_LPARAM(lParam);
			int mouse_y = GET_Y_LPARAM(lParam);

			if (userdata[5]) {
				userdata[5] = 0;
				TrackMouseEvent(&tme);

				double xpos = mouse_x;
				double ypos = mouse_y;
				int async_load = CBCreateDsMap(4,
					"event_type", zero, "libmulti_mouseenter",
					"window", window, nullptr,
					"x", xpos, nullptr,
					"y", ypos, nullptr
				);
				CBDispatch(async_load, EVENT_OTHER_SOCIAL);
			}

			userdata[6] = mouse_x;
			userdata[7] = mouse_y;

			break;
		}

		case WM_MOUSELEAVE: {
			userdata[5] = 1;
			int async_load = CBCreateDsMap(2,
				"event_type", zero, "libmulti_mouseleave",
				"window", window, nullptr
			);
			CBDispatch(async_load, EVENT_OTHER_SOCIAL);
			break;
		}

		case WM_DESTROY: {
			delete d2d;
			vecWindows[wind].first = nullptr;
			vecWindows[wind].second = nullptr;
			int async_load = CBCreateDsMap(2,
				"event_type", zero, "libmulti_destroy",
				"window", window, nullptr
			);
			CBDispatch(async_load, EVENT_OTHER_SOCIAL);
			break;
		}

		case WM_GETMINMAXINFO: {
			LPMINMAXINFO maxinfo = reinterpret_cast<LPMINMAXINFO>(lParam);
			auto styles = GetWindowLongPtrW(hWnd, GWL_STYLE);
			auto exstyles = GetWindowLongPtrW(hWnd, GWL_EXSTYLE);
			RECT rc;

			if (minW > 0 || minH > 0) {
				SetRectEmpty(&rc);
				rc.right = static_cast<LONG>(minW); rc.bottom = static_cast<LONG>(minH);
				AdjustWindowRectEx(&rc, static_cast<DWORD>(styles), GetMenu(hWnd) != nullptr, static_cast<DWORD>(exstyles));
				rc.right -= rc.left;
				rc.bottom -= rc.top;

				if (minW > 0) maxinfo->ptMinTrackSize.x = rc.right;
				if (minH > 0) maxinfo->ptMinTrackSize.y = rc.bottom;
			}

			if (maxW > 0 || maxH > 0) {
				SetRectEmpty(&rc);
				rc.right = static_cast<LONG>(maxW); rc.bottom = static_cast<LONG>(maxH);
				AdjustWindowRectEx(&rc, static_cast<DWORD>(styles), GetMenu(hWnd) != nullptr, static_cast<DWORD>(exstyles));
				rc.right -= rc.left;
				rc.bottom -= rc.top;

				if (maxW > 0) maxinfo->ptMaxTrackSize.x = rc.right;
				if (maxH > 0) maxinfo->ptMaxTrackSize.y = rc.bottom;
			}

			break;
		}

		default: {
			ret = DefWindowProc(hWnd, Msg, wParam, lParam);
			break;
		}
	}

	LeaveVector();
	return ret;
}

dllx char* RegisterCallbacks(char* p1, char* p2, char* p3, char* p4) {
	CBDispatch = reinterpret_cast<CBDispatch_t>(p1);
	CBCreateDsMap = reinterpret_cast<CBCreateDsMap_t>(p2);
	CBDsMapAddReal = reinterpret_cast<CBDsMapAddReal_t>(p3);
	CBDsMapAddString = reinterpret_cast<CBDsMapAddString_t>(p4);
	return nullptr; // TODO: Change this when GmxGen updates.
}

dllx double libmulti_init() {
	printf(__FUNCTION__ ": hello!\n");
	fflush(stdout);
	Mutex = new CRITICAL_SECTION();
	InitializeCriticalSection(Mutex);
	InitMultiD2D();
	EnterVector();
	nikWindowClass = register_window_class(WindowProc);
	libmulti_cursor_init();
	LeaveVector();

	// RegisterCallbacks wasn't called? Are we in legacy GM?
	if (CBCreateDsMap == nullptr && CBDispatch == nullptr && CBDsMapAddReal == nullptr && CBDsMapAddString == nullptr) {
		CBCreateDsMap = libmulti_legacy_create_ds_map;
		CBDispatch = libmulti_legacy_dispatch_stub;
		// initialize a custom event system
		IsLegacy = true;
		libmulti_legacy_mutex_init();
		// overmars why
	}

	return nikWindowClass;
}

dllx double libmulti_quit() {
	if (Mutex == nullptr) return -1.0;
	EnterVector();
	for (const auto& pair : vecWindows) {
		if (DestroyWindow(pair.first) == FALSE) {
			LastError = GetLastError();
		}
	}
	BOOL ok = unregister_window_class(nikWindowClass, hModule);
	if (ok == FALSE) {
		LastError = GetLastError();
	}
	LeaveVector();
	DeleteCriticalSection(Mutex);
	Mutex = nullptr;
	libmulti_legacy_mutex_quit();
	return ok;
}

dllx char* libmulti_last_error_message() {
	EnterVector();
	DWORD myError = LastError;
	LeaveVector();

	LPWSTR err = nullptr;

	DWORD ok = FormatMessageW(
		FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		nullptr,
		myError,
		MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), reinterpret_cast<LPWSTR>(&err), 0, nullptr);

	LastError = GetLastError();

	if (ok == 0) {
		return u8"!@ Failed to get the error message.";
	}

	_libmulti_free();

	int needed = WideCharToMultiByte(IsLegacy ? CP_OEMCP : CP_UTF8, 0, err, -1, nullptr, 0, nullptr, nullptr);
	LastString = new char[needed];
	needed = WideCharToMultiByte(IsLegacy ? CP_OEMCP : CP_UTF8, 0, err, -1, LastString, needed, nullptr, nullptr);
	LastError = GetLastError();
	LocalFree(err);
	err = nullptr;

	if (needed == 0) {
		return u8"!@ Failed to convert the error message to UTF-8.";
	}

	return LastString;
}

dllx double libmulti_create_window(double _x, double _y, double _w, double _h, double _style, double _exstyle, double _show, double _minw, double _minh, double _maxw, double _maxh) {
	int X = static_cast<int>(_x), Y = static_cast<int>(_y), W = static_cast<int>(_w), H = static_cast<int>(_h), S = static_cast<int>(_show);
	DWORD St = static_cast<DWORD>(_style);
	DWORD ExSt = static_cast<DWORD>(_exstyle);

	// gotta be careful with these, doing < 0.0 may screw up some stuff if a constant starts with 0x80
	if (_style == -1.0) St = WS_OVERLAPPEDWINDOW;
	if (_exstyle == -1.0) ExSt = 0;
	if (_show == -1.0) S = SW_SHOWDEFAULT;

	// here <0 is fine
	if (X < 0) X = CW_USEDEFAULT;
	if (Y < 0) Y = CW_USEDEFAULT;
	if (W < 0) W = CW_USEDEFAULT;
	if (H < 0) H = CW_USEDEFAULT;

	// CW_USEDEFAULT cannot be passed to AdjustWindowRectEx since it's causing issues.

	RECT clientRc{ (X == CW_USEDEFAULT) ? 0 : X, (Y == CW_USEDEFAULT) ? 0 : Y, W, H };
	if (clientRc.right != CW_USEDEFAULT && clientRc.bottom != CW_USEDEFAULT) {
		BOOL adjustok = AdjustWindowRectEx(&clientRc, St, FALSE, ExSt);
		
		int diffX = ((X == CW_USEDEFAULT) ? 0 : X) - clientRc.left;
		int diffY = ((Y == CW_USEDEFAULT) ? 0 : Y) - clientRc.top;
		clientRc.right += diffX;
		clientRc.bottom += diffY;
		printf(__FUNCTION__ ": AdjustWindowRectEx ok?=%d\ndiffX=%d,diffY=%d\n", adjustok, diffX, diffY);
		fflush(stdout);
	}
	if (X == CW_USEDEFAULT) clientRc.left = CW_USEDEFAULT;
	if (Y == CW_USEDEFAULT) clientRc.top = CW_USEDEFAULT;

	int minW = static_cast<int>(_minw),
		minH = static_cast<int>(_minh),
		maxW = static_cast<int>(_maxw),
		maxH = static_cast<int>(_maxh);

	HWND window = CreateWindowEx(ExSt,
		reinterpret_cast<LPCTSTR>(nikWindowClass), // surprisingly, you can also pass an ATOM casted to a string pointer.
		TEXT("..."),
		St,
		clientRc.left, clientRc.top, // xy
		clientRc.right, clientRc.bottom, // wh
		nullptr, nullptr, hModule, nullptr
	);
	
	LastError = GetLastError();
	if (!window) return -1.0;

	std::pair<HWND, int>* startup = new std::pair<HWND, int>(window, S);
	DWORD threadId = 0;
	intptr_t* userdata = new intptr_t[8];
	std::size_t ind = _libmulti_find_free();
	userdata[0] = ind;
	userdata[1] = minW;
	userdata[2] = minH;
	userdata[3] = maxW;
	userdata[4] = maxH;
	userdata[5] = 0; // mouse hover flag
	userdata[6] = 0; // last mouse x
	userdata[7] = 0; // last mouse y
	SetWindowLongPtrW(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(userdata));

	EnterVector();
	if (ind == vecWindows.size()) {
		vecWindows.emplace_back(std::make_pair(window, new CMultiD2D()));
	}
	else {
		vecWindows[ind] = std::make_pair(window, new CMultiD2D());
	}
	LeaveVector();

	CreateThread(nullptr, 0, libmulti_window_thread, startup, 0, &threadId);
	return static_cast<double>(ind);
}

dllx double libmulti_destroy(double index) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		BOOL ret = FALSE;
		EnterVector();

		std::size_t ind = static_cast<std::size_t>(index);
		HWND wnd = vecWindows[ind].first;
		if (wnd != nullptr) {
			ret = DestroyWindow(vecWindows[ind].first);
			LastError = GetLastError();

			if (ret == TRUE) {
				vecWindows[ind].first = nullptr;
				if (ind == vecWindows.size() - 1) {
					vecWindows.pop_back();
				}
			}
		}

		LeaveVector();

		return ret;
	}
}

dllx double libmulti_set_caption(double index, char* _name) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		BOOL ret = TRUE;
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		if ((*_name) == '\0') {
			// if an empty string is passed, don't bother converting
			BOOL ok = SetWindowText(window, TEXT(""));
			LastError = GetLastError();
		}
		else {
			int needed = MultiByteToWideChar(IsLegacy ? CP_OEMCP : CP_UTF8, 0, _name, -1, nullptr, 0);
			LPWSTR wide = new WCHAR[needed];
			MultiByteToWideChar(IsLegacy ? CP_OEMCP : CP_UTF8, 0, _name, -1, wide, needed);
			BOOL ok = SetWindowText(window, wide);
			LastError = GetLastError();
			delete[] wide;
		}
		LeaveVector();
		return ret;
	}
}

dllx char* libmulti_get_caption(double index) {
	if (!_libmulti_exists(index)) return u8"";
	else {
		char* ret = u8"";
		_libmulti_free();
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		int chars = GetWindowTextLengthW(window);
		LastError = GetLastError();
		if (chars > 0) {
			LPWSTR buf = new WCHAR[chars + 1];
			int copied = GetWindowTextW(window, buf, chars + 1);
			LastError = GetLastError();
			if (chars == copied) {
				int need = WideCharToMultiByte(IsLegacy ? CP_OEMCP : CP_UTF8, 0, buf, -1, nullptr, 0, nullptr, nullptr);
				LastString = new char[need];
				copied = WideCharToMultiByte(IsLegacy ? CP_OEMCP : CP_UTF8, 0, buf, -1, LastString, need, nullptr, nullptr);
				LastError = GetLastError();
				if (copied > 0) {
					ret = LastString;
				}
			}
			delete[] buf;
		}
		LeaveVector();

		return ret;
	}
}

dllx double libmulti_make_bitmap(double index, double width, double height, char* _buf) {
	if (!_libmulti_exists(index) || width < 1.0 || height < 1.0 || _buf == nullptr) return -1.0;
	else {
		BOOL ret = FALSE;
		EnterVector();
		const auto& hwnd = vecWindows[static_cast<std::size_t>(index)].first;
		const auto& d2d = vecWindows[static_cast<std::size_t>(index)].second;
		if (d2d != nullptr) {
			ret = SUCCEEDED(d2d->SetBitmap(static_cast<UINT>(width), static_cast<UINT>(height), _buf))
				&& RedrawWindow(hwnd, nullptr, nullptr, RDW_ERASE | RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);
		}
		LeaveVector();
		return ret;
	}
}
