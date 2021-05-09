/// @description New window

var _defw, _defh;

// change this to your liking?
_defw = 800;
_defh = 600;

var _w, n;
_w = libmulti_create_window(
    -1, -1, // we don't care about x,y
    _defw, _defh, // width height
    -1, -1, -1, // style|extended style|sw_show we don't care
    320, 240, // min width min height, something regular
    -1, -1 // max width max height, we don't care
);

ds_list_add(windows, _w);
ds_list_add(buffers, buffer_create(_defw * _defh * 4, buffer_fixed, 1));
ds_list_add(inputs, "");

n = 10 + irandom(10);
libmulti_set_caption(_w, "libmulti window, you're just as cool as " + string(n) + " cats.");
