// libmulti.h: Main header file for libmulti.
#include "stdafx.h"
#include "MultiD2D.h"
#include "gmcallback.h"

// internal libmulti stuff.
void EnterVector();
void LeaveVector();
extern HMODULE hModule;
extern DWORD LastError;
extern std::vector<std::pair<HWND, CMultiD2D*>> vecWindows;
bool _libmulti_exists(double window);
DWORD WINAPI libmulti_window_thread(LPVOID lpThreadParameter);
ATOM register_window_class(WNDPROC p);
BOOL unregister_window_class(ATOM c, HINSTANCE hi);
int libmulti_legacy_create_ds_map(int _num, ...);
void libmulti_legacy_dispatch_stub(int ds_map, int event_index);
void libmulti_legacy_mutex_init();
void libmulti_legacy_mutex_quit();


/*
@ // ignore this, it's here just for reference.
@ void RegisterCallbacks(char* p1, char* p2, char* p3, char* p4);
@ /// (Dont,Use) : LEGACY GM ONLY, DO NOT USE!
@ double libmulti_make_bitmap_from_file(double window, char* _fileName);
@ /// (DoNotUse) : LEGACY GM ONLY, DO NOT USE!
@ double libmulti_set_game_window_real(double hwnd);
@ /// () : LEGACY GM ONLY, DO NOT USE!
@ double libmulti_legacy_check();
@ /// () : LEGACY GM ONLY, DO NOT USE!
@ const char* libmulti_legacy_dispatch();
*/

/* GmxGen stuff below, change as needed: */
#define dllx extern "C" __declspec(dllexport)

/// Do not call this function at all.
dllx char* RegisterCallbacks(char* please, char* dont, char* call, char* it);
///->real : Initializes the library.
dllx double libmulti_init();
///->real : Destroys all windows and frees the library resources.
dllx double libmulti_quit();
///->real : Returns true if the DLL is present and was loaded.
dllx double libmulti_present();
///->real : Checks if a window index is valid and the window exists.
dllx double libmulti_exists(double window);
///->real : Returns the last WinAPI error code.
dllx double libmulti_last_error_code();
///->string : Tries to turn the last WinAPI error code into a string.
dllx char* libmulti_last_error_message();
///->real : Creates a new window.
dllx double libmulti_create_window(double x, double y, double width, double height, double style, double ex_style, double sw_show, double min_width, double min_height, double max_width, double max_height);
///->real : Destroys a window.
dllx double libmulti_destroy(double window);
///->real : Sets the window caption.
dllx double libmulti_set_caption(double window, char* caption);
///->string : Gets the window's caption.
dllx char* libmulti_get_caption(double window);
///->real : Draws a surface buffer inside the window.
dllx double libmulti_make_bitmap(double window, double width, double height, char* buffer_ADDRESS);
///->real : Tells the extension which window is managed by GM.
dllx double libmulti_set_game_window(char* window_handle_result);
///->real : Sets the passed window as active.
dllx double libmulti_set_active_window(double window);
///->real : Sets the passed window as foreground.
dllx double libmulti_set_foreground_window(double window);
///->real : Checks if the passed window is in focus or not.
dllx double libmulti_has_focus(double window);
///->real : Gets the index of the current active window.
dllx double libmulti_get_active_window();
///->real : Gets the index of the current foreground window.
dllx double libmulti_get_foreground_window();
///->real : Gets the X coord of the client area of the window.
dllx double libmulti_get_x(double window);
///->real : Gets the Y coord of the client area of the window.
dllx double libmulti_get_y(double window);
///->real : Gets the width of the client area of the window.
dllx double libmulti_get_width(double window);
///->real : Gets the height of the client area of the window.
dllx double libmulti_get_height(double window);
///->real : Sets the X position of the client area of the window.
dllx double libmulti_set_x(double window, double new_x);
///->real : Sets the Y position of the client area of the window.
dllx double libmulti_set_y(double window, double new_y);
///->real : Sets the width of the client area of the window.
dllx double libmulti_set_width(double window, double new_width);
///->real : Sets the height of the client area of the window.
dllx double libmulti_set_height(double window, double new_height);
///->real : Sets the position of the client area of the window.
dllx double libmulti_set_position(double window, double new_x, double new_y);
///->real : Sets the size of the client area of the window.
dllx double libmulti_set_size(double window, double new_width, double new_height);
///->real : Sets the window's client area rectangle.
dllx double libmulti_set_rectangle(double window, double new_x, double new_y, double new_width, double new_height);
///->real : Gets the left offset of the window's non-client area.
dllx double libmulti_get_nonclient_left(double window);
///->real : Gets the top offset of the window's non-client area.
dllx double libmulti_get_nonclient_top(double window);
///->real : Gets the right offset of the window's non-client area.
dllx double libmulti_get_nonclient_right(double window);
///->real : Gets the bottom offset of the window's non-client area.
dllx double libmulti_get_nonclient_bottom(double window);
///->real : Sets the extended or window style.
dllx double libmulti_set_window_style(double window, double is_extended, double style_value);
///->real : Gets the window or the extended style.
dllx double libmulti_get_window_style(double window, double is_extended);
///->real : Sets the minimum allowed width of the window.
dllx double libmulti_set_min_width(double window, double new_min_width);
///->real : Sets the minimum allowed height of the window.
dllx double libmulti_set_min_height(double window, double new_min_height);
///->real : Sets the maximum allowed width of the window.
dllx double libmulti_set_max_width(double window, double new_max_width);
///->real : Sets the maximum allowed height of the window.
dllx double libmulti_set_max_height(double window, double new_max_height);
///->real : Sets the minimum allowed size of the window.
dllx double libmulti_set_min_size(double window, double new_min_width, double new_min_height);
///->real : Sets the maximum allowed size of the window.
dllx double libmulti_set_max_size(double window, double new_max_width, double new_max_height);
///->real : Gets the minimum allowed width of the window.
dllx double libmulti_get_min_width(double window);
///->real : Gets the minimum allowed height of the window.
dllx double libmulti_get_min_height(double window);
///->real : Gets the maximum allowed width of the window.
dllx double libmulti_get_max_width(double window);
///->real : Gets the maximum allowed height of the window.
dllx double libmulti_get_max_height(double window);
///->real : Gets the last X mouse coord relative to the window's client area.
dllx double libmulti_mouse_get_x(double window);
///->real : Gets the last Y mouse coord relative to the window's client area.
dllx double libmulti_mouse_get_y(double window);
// End.
