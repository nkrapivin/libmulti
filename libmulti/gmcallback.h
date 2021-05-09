#pragma once

typedef void(*CBDispatch_t)(int dsmap_index, int event_subtype);
typedef int(*CBCreateDsMap_t)(int num, ...);
typedef bool(*CBDsMapAddReal_t)(int dsmap_index, const char* pKey, double value);
typedef bool(*CBDsMapAddString_t)(int dsmap_index, const char* pKey, const char* pValue);
const int EVENT_OTHER_SOCIAL = 70;
