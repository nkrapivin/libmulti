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
