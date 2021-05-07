// libmulti_dllmain.cpp: Contains the DllMain entrypoint.

#include "stdafx.h"
#include "libmulti.h"

EXTERN_C BOOL APIENTRY DllMain(HMODULE h, DWORD d, LPVOID l) {
	hModule = h;
	return hModule != nullptr;
}
