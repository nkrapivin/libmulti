/// @description An example of handling libmulti events.

var _ev_type;

// just in case it's undefined, it will turn into a string "<undefined>"
// which will be an unknown event.
_ev_type = string(ds_map_find_value(async_load, "event_type"));

switch (_ev_type) {
    case "libmulti_mouseenter": {
        var _w, _x, _y; _w = ds_map_find_value(async_load, "window");
        _x = ds_map_find_value(async_load, "x");
        _y = ds_map_find_value(async_load, "y");
        libmulti_set_caption(_w, "wow you care about me! x=" + string(_x) + ",y=" + string(_y));
        break;
    }
    
    case "libmulti_mousehover": {
        var _w, _x, _y; _w = ds_map_find_value(async_load, "window");
        _x = ds_map_find_value(async_load, "x");
        _y = ds_map_find_value(async_load, "y");
        libmulti_set_caption(_w, "why are you... hovering your mouse? x=" + string(_x) + ",y=" + string(_y));
        break;
    }
    
    case "libmulti_mouseleave": {
        var _w; _w = ds_map_find_value(async_load, "window");
        libmulti_set_caption(_w, "d-don't leave me! I'm all alone... :(");
        break;
    }
    
    case "libmulti_close": {
        var _w; _w = ds_map_find_value(async_load, "window");
        show_debug_message("a window is going to close soon, id=" + string(_w));
        // can't do much :(
        break;
    }
    
    case "libmulti_destroy": {
        // need to free the window.
        var _w; _w = ds_map_find_value(async_load, "window");
        var _i; _i = ds_list_find_index(windows, _w);
        if (_i < 0) {
            show_debug_message("Wtf? window id=" + string(_w));
            break;
        }
        
        ds_list_delete(windows, _i);
        buffer_delete(ds_list_find_value(buffers, _i));
        ds_list_delete(buffers, _i);
        ds_list_delete(inputs, _i);
        show_debug_message("Freed window id=" + string(_w));
        break;
    }
    
    case "libmulti_size": {
        var _w, _nw, _nh; _w = ds_map_find_value(async_load, "window");
        _nw = ds_map_find_value(async_load, "new_width");
        _nh = ds_map_find_value(async_load, "new_height");
        
        libmulti_set_caption(_w, "aw, you changed my size, w=" + string(_nw) + ",h=" + string(_nh));
        break;
    }
    
    case "libmulti_pastetext": {
        var _w, _pos, _text; _w = ds_map_find_value(async_load, "window");
        _text = ds_map_find_value(async_load, "contents");
        if (!is_string(_text)) break; // ignore, either an invalid paste event or some winapi error has occurred.
        _pos = ds_list_find_index(windows, _w);
        if (_pos < 0) {
            show_debug_message("[paste] Wtf? window id=" + string(_w));
            break;
        }
        
        // append paste text to the current keyboard string input...
        ds_list_replace(inputs, _pos,
            ds_list_find_value(inputs, _pos) + _text
        );
        
        break;
    }
    
    case "libmulti_input": {
        // handle keyboard input in a window.
        var _w, _raw, _str, _pos, _instr, _inlen; _w = ds_map_find_value(async_load, "window");
        _raw = ds_map_find_value(async_load, "character");
        _str = ds_map_find_value(async_load, "as_string");
        _pos = ds_list_find_index(windows, _w);
        if (_pos < 0) {
            show_debug_message("[input] Wtf? window id=" + string(_w));
            break;
        }
        
        _instr = ds_list_find_value(inputs, _pos);
        _inlen = string_length(_instr);
        
        switch (_raw) {
            case $1B: {
                // handle the escape key, you can do something different idk
                libmulti_destroy(_w);
                break;
            }
            
            case $09: {
                // no idea how to handle this one.
                show_debug_message("libmulti Tab key, window id=" + string(_w));
                break;
            }
            
            case $0D: {
                var nl; nl = chr($0A); // always use the 0A newline, not 0D.
                ds_list_replace(
                    inputs, _pos,
                    _instr + nl
                );
                break;
            }
            
            case $08: {
                // backspace, here we simply delete last character
                ds_list_replace(
                    inputs, _pos,
                    string_delete(_instr, _inlen, 1)
                );
                break;
            }
            
            default: {
                // normal printable character.
                ds_list_replace(
                    inputs, _pos,
                    _instr + _str
                );
                
                break;
            }
        }
        
        break;
    }
    
    // mouse events:
    case "libmulti_leftup": // Left Pressed
    case "libmulti_leftdown": // Left Released
    case "libmulti_rightup": // Right Pressed
    case "libmulti_rightdown": // Right Released
    case "libmulti_middleup": // Wheel Pressed
    case "libmulti_middledown": // Wheel Released
    {
        var _w, _x, _y; _w = ds_map_find_value(async_load, "window");
        _x = ds_map_find_value(async_load, "x");
        _y = ds_map_find_value(async_load, "y");
        libmulti_set_caption(_w, "hehe it tickles ^^' mx=" + string(_x) + ",my=" + string(_y) + ",event_type=" + _ev_type);
        // feel free to implement your own 'hold' event based on this...
        break;
    }
    
    default: {
        // meh...
        show_debug_message("ignored libmulti event as json:");
        show_debug_message(json_encode(async_load));
        break;
    }
}
