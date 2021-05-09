/// @description resize the demo room to the game window

var _ww, _wh;
_ww = window_get_width();
_wh = window_get_height();

if (room_width != _ww || room_height != _wh) {
    room_width = _ww;
    room_height = _wh;
    surface_resize(application_surface, _ww, _wh);
    show_debug_message("main window resize");
}
