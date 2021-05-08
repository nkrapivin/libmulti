// Приведенный ниже блок ifdef - это стандартный метод создания макросов, упрощающий процедуру 
// экспорта из библиотек DLL. Все файлы данной DLL скомпилированы с использованием символа LIBMULTI_EXPORTS,
// в командной строке. Этот символ не должен быть определен в каком-либо проекте
// использующем данную DLL. Благодаря этому любой другой проект, чьи исходные файлы включают данный файл, видит 
// функции LIBMULTI_API как импортированные из DLL, тогда как данная DLL видит символы,
// определяемые данным макросом, как экспортированные.
#include "stdafx.h"
#include "MultiD2D.h"
#ifdef LIBMULTI_EXPORTS
#define LIBMULTI_API __declspec(dllexport)
#else
#define LIBMULTI_API __declspec(dllimport)
#endif

#define LIBMULTI_VOID   EXTERN_C LIBMULTI_API void        CDECL 
#define LIBMULTI_DOUBLE EXTERN_C LIBMULTI_API double      CDECL 
#define LIBMULTI_STRING EXTERN_C LIBMULTI_API const char* CDECL 

typedef void(*CBDispatch_t)(int dsmap_index, int event_subtype);
typedef int(*CBCreateDsMap_t)(int num, ...);
typedef bool(*CBDsMapAddReal_t)(int dsmap_index, const char* pKey, double value);
typedef bool(*CBDsMapAddString_t)(int dsmap_index, const char* pKey, const char* pValue);

void EnterVector(void);
void LeaveVector(void);
extern HMODULE hModule;
extern DWORD LastError;
extern std::vector<std::pair<HWND, CMultiD2D*>> vecWindows;
bool _libmulti_exists(double index);
DWORD WINAPI libmulti_window_thread(LPVOID lpThreadParameter);
ATOM register_window_class(WNDPROC p);
BOOL unregister_window_class(ATOM c, HINSTANCE hi);

LIBMULTI_VOID   RegisterCallbacks(char* p1, char* p2, char* p3, char* p4);
LIBMULTI_DOUBLE libmulti_init(void);
LIBMULTI_DOUBLE libmulti_quit(void);
LIBMULTI_DOUBLE libmulti_present(void);
LIBMULTI_DOUBLE libmulti_exists(double index);
LIBMULTI_DOUBLE libmulti_last_error_code(void);
LIBMULTI_STRING libmulti_last_error_message(void);
LIBMULTI_DOUBLE libmulti_create_window(double _x, double _y, double _w, double _h, double _style, double _exstyle, double _show, double _minw, double _minh, double _maxw, double _maxh);
LIBMULTI_DOUBLE libmulti_destroy(double index);
LIBMULTI_DOUBLE libmulti_set_caption(double index, char* _name);
LIBMULTI_DOUBLE libmulti_make_bitmap(double index, double width, double height, char* _buf);
LIBMULTI_DOUBLE libmulti_make_bitmap_from_file(double index, char* _fileName);
LIBMULTI_DOUBLE libmulti_set_game_window(char* hwnd);
LIBMULTI_DOUBLE libmulti_set_game_window_real(double hwnd);
LIBMULTI_DOUBLE libmulti_set_active_window(double index);
LIBMULTI_DOUBLE libmulti_set_foreground_window(double index);
LIBMULTI_DOUBLE libmulti_has_focus(double index);
LIBMULTI_DOUBLE libmulti_get_active_window(void);
LIBMULTI_DOUBLE libmulti_get_foreground_window(void);
LIBMULTI_DOUBLE libmulti_get_x(double index);
LIBMULTI_DOUBLE libmulti_get_y(double index);
LIBMULTI_DOUBLE libmulti_get_width(double index);
LIBMULTI_DOUBLE libmulti_get_height(double index);
LIBMULTI_DOUBLE libmulti_set_x(double index, double x);
LIBMULTI_DOUBLE libmulti_set_y(double index, double y);
LIBMULTI_DOUBLE libmulti_set_width(double index, double w);
LIBMULTI_DOUBLE libmulti_set_height(double index, double h);
LIBMULTI_DOUBLE libmulti_set_position(double index, double x, double y);
LIBMULTI_DOUBLE libmulti_set_size(double index, double w, double h);
LIBMULTI_DOUBLE libmulti_set_rectangle(double index, double x, double y, double w, double h);
LIBMULTI_DOUBLE libmulti_get_nonclient_left(double index);
LIBMULTI_DOUBLE libmulti_get_nonclient_top(double index);
LIBMULTI_DOUBLE libmulti_get_nonclient_right(double index);
LIBMULTI_DOUBLE libmulti_get_nonclient_bottom(double index);
LIBMULTI_STRING libmulti_get_caption(double index);
LIBMULTI_DOUBLE libmulti_set_window_style(double index, double is_extended, double value);
LIBMULTI_DOUBLE libmulti_get_window_style(double index, double is_extended);
LIBMULTI_DOUBLE libmulti_set_min_width(double index, double width);
LIBMULTI_DOUBLE libmulti_set_min_height(double index, double height);
LIBMULTI_DOUBLE libmulti_set_max_width(double index, double width);
LIBMULTI_DOUBLE libmulti_set_max_height(double index, double height);
LIBMULTI_DOUBLE libmulti_set_min_size(double index, double width, double height);
LIBMULTI_DOUBLE libmulti_set_max_size(double index, double width, double height);
LIBMULTI_DOUBLE libmulti_get_min_width(double index);
LIBMULTI_DOUBLE libmulti_get_min_height(double index);
LIBMULTI_DOUBLE libmulti_get_max_width(double index);
LIBMULTI_DOUBLE libmulti_get_max_height(double index);

int libmulti_legacy_create_ds_map(int _num, ...);
void libmulti_legacy_dispatch_stub(int ds_map, int event_index);

LIBMULTI_DOUBLE libmulti_legacy_check(void);
LIBMULTI_STRING libmulti_legacy_dispatch(void);

void libmulti_legacy_mutex_init();
void libmulti_legacy_mutex_quit();
