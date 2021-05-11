// libmulti_misc.cpp: For functions that are too simple to implement.

#include "stdafx.h"
#include "libmulti.h"

dllx double libmulti_last_error_code() {
	return LastError;
}

dllx double libmulti_exists(double index) {
	return _libmulti_exists(index);
}

dllx double libmulti_present() {
	return 1.0;
}

dllx double libmulti_set_gms2_pixel_format(double truefalse) {
	double old = -1.0;
	EnterVector();
	old = AltRGBMode;
	AltRGBMode = truefalse > 0.5;
	LeaveVector();
	return old;
}

dllx double libmulti_get_gms2_pixel_format() {
	double ret = -1.0;
	EnterVector();
	ret = AltRGBMode;
	LeaveVector();
	return ret;
}
