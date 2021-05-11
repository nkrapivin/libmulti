// libmulti_legacy.cpp: Functions that are only useful on old engines such as GM8.

#include "stdafx.h"
#include "libmulti.h"
#include <string>
#include <sstream>
#include <queue>
#include <iomanip>

static CRITICAL_SECTION* LegacyMutex{ nullptr };
//                                       name         strvalue     realval is_string
static std::queue<std::vector<std::tuple<std::string, std::string, double, bool>>> EventQueue{};

void libmulti_legacy_mutex_init() {
	LegacyMutex = new CRITICAL_SECTION();
	InitializeCriticalSection(LegacyMutex);
}

void libmulti_legacy_mutex_quit() {
	if (LegacyMutex != nullptr) {
		DeleteCriticalSection(LegacyMutex);
		LegacyMutex = nullptr;
	}
}

int libmulti_legacy_create_ds_map(int _num, ...) {
	va_list args;
	va_start(args, _num);

	std::vector<std::tuple<std::string, std::string, double, bool>> vecevent{ };
	vecevent.reserve(_num);
	int ind = -1;

	EnterCriticalSection(LegacyMutex);

	for (int i = 0; i < _num; i++) {
		const char* name = va_arg(args, char*);
		double dbl = va_arg(args, double);
		const char* value = va_arg(args, char*);

		if (value == nullptr) {
			vecevent.push_back(std::make_tuple(name, "", dbl, false));
		}
		else {
			vecevent.push_back(std::make_tuple(name, value, 0.0, true));
		}
	}

	EventQueue.push(vecevent);
	ind = static_cast<int>(EventQueue.size()) - 1;

	LeaveCriticalSection(LegacyMutex);

	va_end(args);
	return ind;
}

void libmulti_legacy_dispatch_stub(int ds_map, int event_index) {
	// do nothing.
}

dllx double libmulti_legacy_check() {
	double size = 0.0;

	EnterCriticalSection(LegacyMutex);
	size = static_cast<double>(EventQueue.size());
	LeaveCriticalSection(LegacyMutex);

	return size;
}

dllx double libmulti_legacy_done() {
	double ret = 0.0;

	EnterCriticalSection(LegacyMutex);

	if (!(EventQueue.empty())) {
		EventQueue.pop();
		ret = 1.0;
	}

	LeaveCriticalSection(LegacyMutex);

	return ret;
}

dllx double libmulti_legacy_event_length() {
	double len = 0.0;

	EnterCriticalSection(LegacyMutex);
	len = static_cast<double>(EventQueue.front().size());
	LeaveCriticalSection(LegacyMutex);

	return len;
}

dllx const char* libmulti_legacy_event_value_name(double num) {
	const char* ret = "";

	EnterCriticalSection(LegacyMutex);
	ret = std::get<0>(EventQueue.front()[static_cast<std::size_t>(num)]).c_str();
	LeaveCriticalSection(LegacyMutex);

	return ret;
}

dllx const char* libmulti_legacy_event_value_string(double num) {
	const char* ret = "";

	EnterCriticalSection(LegacyMutex);
	ret = std::get<1>(EventQueue.front()[static_cast<std::size_t>(num)]).c_str();
	LeaveCriticalSection(LegacyMutex);

	return ret;
}

dllx double libmulti_legacy_event_value_real(double num) {
	double ret = 0.0;

	EnterCriticalSection(LegacyMutex);
	ret = std::get<2>(EventQueue.front()[static_cast<std::size_t>(num)]);
	LeaveCriticalSection(LegacyMutex);

	return ret;
}

dllx double libmulti_legacy_event_is_string(double num) {
	double ret = -1.0;

	EnterCriticalSection(LegacyMutex);
	ret = std::get<3>(EventQueue.front()[static_cast<std::size_t>(num)]);
	LeaveCriticalSection(LegacyMutex);

	return ret;
}

dllx double libmulti_make_bitmap_from_file(double index, char* _fileName) {
	if (!_libmulti_exists(index)) return -1.0;
	else {
		// empty string?
		if ((*_fileName) == '\0') return -2.0;

		int needed = MultiByteToWideChar(CP_OEMCP, 0, _fileName, -1, nullptr, 0);
		LastError = GetLastError();
		if (needed <= 0) {
			return -3.0;
		}

		LPWSTR str = new WCHAR[needed];
		needed = MultiByteToWideChar(CP_OEMCP, 0, _fileName, -1, str, needed);
		LastError = GetLastError();
		if (needed <= 0) {
			delete[] str;
			str = nullptr;
			return -4.0;
		}

		EnterVector();
		HWND hwnd = vecWindows[static_cast<std::size_t>(index)].first;
		CMultiD2D* md2d = vecWindows[static_cast<std::size_t>(index)].second;
		md2d->SetBitmapFromFile(str);
		BOOL ok = RedrawWindow(hwnd, nullptr, nullptr, RDW_ERASE | RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);
		LastError = GetLastError();
		LeaveVector();

		if (str != nullptr) {
			delete[] str;
			str = nullptr;
		}

		return ok;
	}
}
