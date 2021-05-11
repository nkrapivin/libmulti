/// @description Test draw

draw_set_halign(fa_left);
draw_set_valign(fa_top);
draw_set_color(c_white);

// here we draw inside the main window.
draw_text(32, 32, @"libmulti by nkrapivindev, a demo,
this is the main game's window.
keys:
N - create New window
P - Poke last window
ESC - Quit (will also destroy all created windows)
wndclass;lasterror;fps = " + string(wndclass) + ";" + string(libmulti_last_error_code()) + ";" + string(fps));

// newline symbol to keep it 1.4-2 compatible...
var nl;
nl = chr(10);

for (var i = 0; i < ds_list_size(windows); i++) {
    var _w, wx, wy, wcap, wstyle, wncarea, wexstyle, width, height, mx, my, surf, buff, str, xx, yy, instr, minw, minh;
    
    _w = ds_list_find_value(windows, i);
    if (!libmulti_exists(_w)) {
        continue; // the window's closing?
    }
    
    str = "";
    wx = libmulti_get_x(_w);
    wy = libmulti_get_y(_w);
    wcap = libmulti_get_caption(_w);
    wstyle = ptr(libmulti_get_window_style(_w, false));
    wexstyle = ptr(libmulti_get_window_style(_w, true));
    width = libmulti_get_width(_w);
    height = libmulti_get_height(_w);
    minw = libmulti_get_min_width(_w);
    minh = libmulti_get_min_height(_w);
    mx = libmulti_mouse_get_x(_w);
    my = libmulti_mouse_get_y(_w);
    surf = surface_create(width, height);
    buff = ds_list_find_value(buffers, i);
    instr = ds_list_find_value(inputs, i);
    
    wncarea[0] = libmulti_get_nonclient_left(_w);
    wncarea[1] = libmulti_get_nonclient_top(_w);
    wncarea[2] = libmulti_get_nonclient_right(_w);
    wncarea[3] = libmulti_get_nonclient_bottom(_w);
    
    // regular surface code as you would imagine.
    surface_set_target(surf);
    draw_clear(c_white); // don't need any alpha in a window duh.
    
    // the actual 'draw' window event is here
    draw_set_color(make_color_hsv((current_time/100 + i*5) mod 255, 255, 255));
    draw_rectangle(8, 8, 8 + 64, 8 + 64, false);
    
    xx = 8;
    yy = 8 + 64 + 8;
    draw_set_color(c_red);
    str = "a libmulti window, window id: " + string(_w) + nl
    + "x: " + string(wx) + nl
    + "y: " + string(wy) + nl
    + "width: " + string(width) + nl
    + "height: " + string(height) + nl
    + "min width: " + string(minw) + nl
    + "min height: " + string(minh) + nl
    + "mouse x: " + string(mx) + nl
    + "mouse y: " + string(my) + nl
    + "caption: " + wcap + nl
    + "style: " + string(wstyle) + nl
    + "extended style: " + string(wexstyle) + nl
    + "nonclient area offsets {x,y,width,height}: " + string(wncarea) + nl
    + "am I in focus? " + string(libmulti_has_focus(_w)) + nl
    + "am I an active window? " + string(libmulti_get_active_window() == _w) + nl
    + "my keyboard_string (type something!): " + instr + nl;
    draw_text(xx, yy, str);
    // and here it ends
    
    surface_reset_target();
    
    if (buffer_get_size(buff) != (width * height * 4)) {
        buffer_resize(buff, width * height * 4);
        // last used bytes fix.
        buffer_poke(buff, buffer_get_size(buff) - 1, buffer_u8, 0);
    }
    
    buffer_get_surface(buff, surf, 0, 0, 0);
    surface_free(surf);
    
    // send to the window
    libmulti_make_bitmap(_w, width, height, buffer_get_address(buff));
}
