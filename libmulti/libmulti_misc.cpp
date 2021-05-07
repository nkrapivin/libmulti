// libmulti_misc.cpp: For functions that are too simple to implement.

#include "stdafx.h"
#include "libmulti.h"

LIBMULTI_DOUBLE libmulti_last_error_code(void) {
	return LastError;
}

LIBMULTI_DOUBLE libmulti_exists(double index) {
	return _libmulti_exists(index);
}

LIBMULTI_DOUBLE libmulti_present(void) {
	return 1.0;
}
