// libmulti_legacy.cpp: Functions that are only useful on old engines such as GM8.

#include "stdafx.h"
#include "libmulti.h"
#include <string>
#include <sstream>
#include <queue>
#include <iomanip>

static CRITICAL_SECTION* LegacyMutex{ nullptr };
static std::queue<std::string> EventQueue{};
static bool DoClean{ false };
static char* TempCopy{ nullptr };

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

	EnterCriticalSection(LegacyMutex);

	std::stringstream ss{};
	ss << "var __libmulti_async_load;" << std::endl << "__libmulti_async_load = ds_map_create();" << std::endl;;

	for (int i = 0; i < _num; i++) {
		const char* name = va_arg(args, char*);
		double dbl = va_arg(args, double);
		const char* value = va_arg(args, char*);

		ss << "ds_map_add(__libmulti_async_load, \"" << name << "\", ";

		if (value == nullptr) {
			ss << std::fixed << dbl;
		}
		else {
			ss << '"' << value << '"';
		}

		ss << ");" << std::endl;
	}

	ss << "return script_execute(argument0, __libmulti_async_load);" << std::endl;

	EventQueue.push(ss.str());
	int ind = EventQueue.size() - 1;

	LeaveCriticalSection(LegacyMutex);

	va_end(args);
	return ind;
}

void libmulti_legacy_dispatch_stub(int ds_map, int event_index) {
	// do nothing.
}

LIBMULTI_DOUBLE libmulti_legacy_check(void) {
	return static_cast<double>(EventQueue.size());
}

LIBMULTI_STRING libmulti_legacy_dispatch(void) {
	if (!(EventQueue.empty())) {
		std::string evstr{ EventQueue.front() };

		if (TempCopy != nullptr) {
			delete[] TempCopy;
		}

		std::size_t siz = evstr.length() + 1;
		TempCopy = new char[siz];
		memset(TempCopy, '\0', siz);

		std::size_t i = 0;
		for (const auto& c : evstr) {
			TempCopy[i] = c;
			i++;
		}

		EventQueue.pop();
		return TempCopy;
	}
	else {
		return "";
	}
}

LIBMULTI_DOUBLE libmulti_make_bitmap_from_file(double index, char* _fileName) {
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
