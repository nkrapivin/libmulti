/// @description Free all allocated resources.

var ok, iw, ib;

for (var i = 0; i < ds_list_size(windows); i++) {
    iw = ds_list_find_value(windows, i);
    ib = ds_list_find_value(buffers, i);
    if (libmulti_exists(iw)) {
        show_debug_message("Destroying window id=" + string(iw));
        libmulti_destroy(iw);
    }
    
    if (buffer_exists(ib)) {
        show_debug_message("Freeing image buffer id=" + string(ib));
        buffer_delete(ib);
    }
}

ds_list_clear(inputs);

ds_list_destroy(windows);
ds_list_destroy(inputs);
ds_list_destroy(buffers);
ok = libmulti_quit(); // will also destroy all windows we didn't destroy ourselves.

if (ok) {
    show_debug_message("libmulti freed ok!");
}
