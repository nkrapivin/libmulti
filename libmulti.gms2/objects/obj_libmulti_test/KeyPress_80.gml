/// @description poke a window

if (ds_list_size(windows) < 1) exit;

var _lastw; _lastw = ds_list_find_value(windows, ds_list_size(windows) - 1);
if (!libmulti_exists(_lastw)) exit;

libmulti_set_caption(_lastw, "poke!");
libmulti_set_min_size(_lastw, 1024, 768);
libmulti_set_rectangle(_lastw, 64, 64, 1024, 768);

