/// @description NOTE: Drop this object into an empty room.

if (!libmulti_present()) {
    show_error("libmulti: Cannot load the DLL, demo will quit.", true);
    game_end();
    exit;
}

window_set_caption("libmulti demo.");
window_set_min_width(640);
window_set_min_height(240);
window_set_size(640, 240);
//alarm[0] = 15; // window_center() delay

wndclass = libmulti_init();
libmulti_set_game_window(window_handle());

seed = randomize();
windows = ds_list_create();
buffers = ds_list_create();
inputs = ds_list_create();

// GMS 2.3.1+
var info = os_get_info();
is64bit = ds_map_find_value(info, "is64bit");
ds_map_destroy(info);
