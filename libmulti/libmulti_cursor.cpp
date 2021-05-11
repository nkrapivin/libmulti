// libmulti_cursor.cpp: Functions related to cursor management.

#include "stdafx.h"
#include "libmulti.h"

enum class gm_cursor_type : int {
	cr_size_all = -22,
	cr_handpoint = -21,
	cr_appstart = -19, // I have no idea why they aren't aligned.
	cr_drag = -12,
	cr_hourglass = -11,
	cr_uparrow = -10,
	cr_size_we = -9,
	cr_size_nwse = -8,
	cr_size_ns = -7,
	cr_size_nesw = -6,
	cr_beam = -4,
	cr_cross = -3,
	cr_arrow = -2,
	cr_none = -1,
	cr_default = 0
};

static HCURSOR hCrNone{ nullptr };
static HCURSOR hCrArrow{ nullptr };
static HCURSOR hCrCross{ nullptr };
static HCURSOR hCrIBeam{ nullptr };
static HCURSOR hCrSizeNesw{ nullptr };
static HCURSOR hCrSizeNs{ nullptr };
static HCURSOR hCrSizeNwse{ nullptr };
static HCURSOR hCrSizeWe{ nullptr };
static HCURSOR hCrUpArrow{ nullptr };
static HCURSOR hCrGlass{ nullptr };
static HCURSOR hCrDrag{ nullptr };
static HCURSOR hCrAppstart{ nullptr };
static HCURSOR hCrHandpoint{ nullptr };
static HCURSOR hCrSizeAll{ nullptr };

HCURSOR libmulti_cursor_get_from_gm(int v) {
	switch (static_cast<gm_cursor_type>(v)) {
		case gm_cursor_type::cr_size_all: return hCrSizeAll;
		case gm_cursor_type::cr_handpoint: return hCrHandpoint;
		case gm_cursor_type::cr_appstart: return hCrAppstart;
		case gm_cursor_type::cr_drag: return hCrDrag;
		case gm_cursor_type::cr_hourglass: return hCrGlass;
		case gm_cursor_type::cr_uparrow: return hCrUpArrow;
		case gm_cursor_type::cr_size_we: return hCrSizeWe;
		case gm_cursor_type::cr_size_nwse: return hCrSizeNwse;
		case gm_cursor_type::cr_size_ns: return hCrSizeNs;
		case gm_cursor_type::cr_size_nesw: return hCrSizeNesw;
		case gm_cursor_type::cr_beam: return hCrIBeam;
		case gm_cursor_type::cr_cross: return hCrCross;
		case gm_cursor_type::cr_arrow: return hCrArrow;
		case gm_cursor_type::cr_none: return hCrNone;
		case gm_cursor_type::cr_default: return hCrArrow;
		default: return nullptr;
	}
}

void libmulti_cursor_init(void) {
	hCrNone = nullptr; // not right, need to investigate later.
	hCrArrow = LoadCursor(nullptr, IDC_ARROW);
	hCrCross = LoadCursor(nullptr, IDC_CROSS);
	hCrIBeam = LoadCursor(nullptr, IDC_IBEAM);
	hCrSizeNesw = LoadCursor(nullptr, IDC_SIZENESW);
	hCrSizeNs = LoadCursor(nullptr, IDC_SIZENS);
	hCrSizeNwse = LoadCursor(nullptr, IDC_SIZENWSE);
	hCrSizeWe = LoadCursor(nullptr, IDC_SIZEWE);
	hCrUpArrow = LoadCursor(nullptr, IDC_UPARROW);
	hCrGlass = LoadCursor(nullptr, IDC_WAIT);
	hCrAppstart = LoadCursor(nullptr, IDC_APPSTARTING);
	hCrHandpoint = LoadCursor(nullptr, IDC_HAND);
	hCrDrag = hCrHandpoint; // wtf??
	hCrSizeAll = LoadCursor(nullptr, IDC_SIZEALL);
}
