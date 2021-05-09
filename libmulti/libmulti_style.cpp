// libmulti_style.cpp: Functions related to window style management.

#include "stdafx.h"
#include "libmulti.h"

dllx double libmulti_set_window_style(double index, double is_extended, double value) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		double ret = static_cast<double>
			(SetWindowLongPtrW(window, ((is_extended > 0.5) ? GWL_EXSTYLE : GWL_STYLE), static_cast<LONG_PTR>(value)));
		LastError = GetLastError();
		LeaveVector();
		return ret;
	}
}

dllx double libmulti_get_window_style(double index, double is_extended) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		EnterVector();
		HWND window = vecWindows[static_cast<std::size_t>(index)].first;
		double ret = static_cast<double>
			(GetWindowLongPtrW(window, ((is_extended > 0.5) ? GWL_EXSTYLE : GWL_STYLE)));
		LastError = GetLastError();
		LeaveVector();
		return ret;
	}
}
