{
    "id": "a8a9771e-0106-4002-b41d-5fed7c52b040",
    "modelName": "GMExtension",
    "mvc": "1.2",
    "name": "libmulti",
    "IncludedResources": [
        
    ],
    "androidPermissions": [
        
    ],
    "androidProps": false,
    "androidactivityinject": "",
    "androidclassname": "",
    "androidinject": "",
    "androidmanifestinject": "",
    "androidsourcedir": "",
    "author": "",
    "classname": "",
    "copyToTargets": 64,
    "date": "2021-01-09 08:05:08",
    "description": "",
    "exportToGame": true,
    "extensionName": "",
    "files": [
        {
            "id": "dfbd8a9a-0586-4647-b570-a46b18473503",
            "modelName": "GMExtensionFile",
            "mvc": "1.0",
            "ProxyFiles": [
                
            ],
            "constants": [
                
            ],
            "copyToTargets": 64,
            "filename": "libmulti.dll",
            "final": "",
            "functions": [
                {
                    "id": "c5041168-ecc6-30e1-002b-d4b72da3b6c9",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 4,
                    "args": [
                        1,
                        1,
                        1,
                        1
                    ],
                    "externalName": "RegisterCallbacks",
                    "help": "RegisterCallbacks(please, dont, call, it) : Do not call this function at all.",
                    "hidden": false,
                    "kind": 1,
                    "name": "RegisterCallbacks",
                    "returnType": 1
                },
                {
                    "id": "d5415e82-a8ba-05e7-e2b7-ca142935a78e",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 0,
                    "args": [
                        
                    ],
                    "externalName": "libmulti_init",
                    "help": "libmulti_init() ->real  :  Initializes the library.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_init",
                    "returnType": 2
                },
                {
                    "id": "dc2752d6-4b1d-763c-2381-7ab34feba283",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 0,
                    "args": [
                        
                    ],
                    "externalName": "libmulti_quit",
                    "help": "libmulti_quit() ->real  :  Destroys all windows and frees the library resources.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_quit",
                    "returnType": 2
                },
                {
                    "id": "0cc3272b-4431-84dc-6737-e6730f2542b1",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 0,
                    "args": [
                        
                    ],
                    "externalName": "libmulti_present",
                    "help": "libmulti_present() ->real  :  Returns true if the DLL is present and was loaded.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_present",
                    "returnType": 2
                },
                {
                    "id": "3edb9f9b-1dd2-6aaf-2153-f04959324c62",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "libmulti_exists",
                    "help": "libmulti_exists(window) ->real  :  Checks if a window index is valid and the window exists.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_exists",
                    "returnType": 2
                },
                {
                    "id": "92e97236-d761-84d6-4322-c812a350c774",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 0,
                    "args": [
                        
                    ],
                    "externalName": "libmulti_last_error_code",
                    "help": "libmulti_last_error_code() ->real  :  Returns the last WinAPI error code.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_last_error_code",
                    "returnType": 2
                },
                {
                    "id": "6b93b080-ee58-a210-bcd0-a4501cf4c3a6",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 0,
                    "args": [
                        
                    ],
                    "externalName": "libmulti_last_error_message",
                    "help": "libmulti_last_error_message() ->string  :  Tries to turn the last WinAPI error code into a string.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_last_error_message",
                    "returnType": 1
                },
                {
                    "id": "f1bdb9a3-b14e-3877-144f-97a1592f134a",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 11,
                    "args": [
                        2,
                        2,
                        2,
                        2,
                        2,
                        2,
                        2,
                        2,
                        2,
                        2,
                        2
                    ],
                    "externalName": "libmulti_create_window",
                    "help": "libmulti_create_window(x, y, width, height, style, ex_style, sw_show, min_width, min_height, max_width, max_height) ->real  :  Creates a new window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_create_window",
                    "returnType": 2
                },
                {
                    "id": "3e996352-1a58-f7c8-4728-fbd879727b27",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "libmulti_destroy",
                    "help": "libmulti_destroy(window) ->real  :  Destroys a window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_destroy",
                    "returnType": 2
                },
                {
                    "id": "d9a5fe0e-e2df-112e-c9a9-1bb8101db3a6",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 2,
                    "args": [
                        2,
                        1
                    ],
                    "externalName": "libmulti_set_caption",
                    "help": "libmulti_set_caption(window, caption) ->real  :  Sets the window caption.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_set_caption",
                    "returnType": 2
                },
                {
                    "id": "7da6d795-749c-dd65-795e-0862d14ed32b",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 4,
                    "args": [
                        2,
                        2,
                        2,
                        1
                    ],
                    "externalName": "libmulti_make_bitmap",
                    "help": "libmulti_make_bitmap(window, width, height, buffer_ADDRESS) ->real  :  Draws a surface buffer inside the window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_make_bitmap",
                    "returnType": 2
                },
                {
                    "id": "77747c04-052c-2eb3-ab51-dc6e788b3a83",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        1
                    ],
                    "externalName": "libmulti_set_game_window",
                    "help": "libmulti_set_game_window(window_handle_result) ->real  :  Tells the extension which window is managed by GM.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_set_game_window",
                    "returnType": 2
                },
                {
                    "id": "1d5662eb-90db-69fe-6141-d0db18ce3516",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "libmulti_set_active_window",
                    "help": "libmulti_set_active_window(window) ->real  :  Sets the passed window as active.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_set_active_window",
                    "returnType": 2
                },
                {
                    "id": "cfb495c7-da8c-ea8e-8952-57500a5d5f73",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "libmulti_set_foreground_window",
                    "help": "libmulti_set_foreground_window(window) ->real  :  Sets the passed window as foreground.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_set_foreground_window",
                    "returnType": 2
                },
                {
                    "id": "f7e6ea51-4c33-81c6-fe5a-0f049a4f0f2d",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "libmulti_has_focus",
                    "help": "libmulti_has_focus(window) ->real  :  Checks if the passed window is in focus or not.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_has_focus",
                    "returnType": 2
                },
                {
                    "id": "34d6b10d-43e9-328e-ded7-9d307ad36614",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 0,
                    "args": [
                        
                    ],
                    "externalName": "libmulti_get_active_window",
                    "help": "libmulti_get_active_window() ->real  :  Gets the index of the current active window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_get_active_window",
                    "returnType": 2
                },
                {
                    "id": "a5f345ae-e86c-0616-1511-1a460cf14c7e",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 0,
                    "args": [
                        
                    ],
                    "externalName": "libmulti_get_foreground_window",
                    "help": "libmulti_get_foreground_window() ->real  :  Gets the index of the current foreground window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_get_foreground_window",
                    "returnType": 2
                },
                {
                    "id": "29fd24a8-4f91-67f1-9610-4f3f19276891",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "libmulti_get_x",
                    "help": "libmulti_get_x(window) ->real  :  Gets the X coord of the client area of the window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_get_x",
                    "returnType": 2
                },
                {
                    "id": "0797734c-a9c2-12f9-de8d-a6926fc9231c",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "libmulti_get_y",
                    "help": "libmulti_get_y(window) ->real  :  Gets the Y coord of the client area of the window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_get_y",
                    "returnType": 2
                },
                {
                    "id": "570ee795-256b-30ee-a9a8-fb79e6187ba7",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "libmulti_get_width",
                    "help": "libmulti_get_width(window) ->real  :  Gets the width of the client area of the window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_get_width",
                    "returnType": 2
                },
                {
                    "id": "70ca10b5-43b5-0df5-0de8-99caf70761e7",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "libmulti_get_height",
                    "help": "libmulti_get_height(window) ->real  :  Gets the height of the client area of the window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_get_height",
                    "returnType": 2
                },
                {
                    "id": "ae4243c9-e43c-0290-6c79-c1dd42aa03f3",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 2,
                    "args": [
                        2,
                        2
                    ],
                    "externalName": "libmulti_set_x",
                    "help": "libmulti_set_x(window, new_x) ->real  :  Sets the X position of the client area of the window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_set_x",
                    "returnType": 2
                },
                {
                    "id": "44a19d0d-05a5-6f9d-df09-94b806e1819a",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 2,
                    "args": [
                        2,
                        2
                    ],
                    "externalName": "libmulti_set_y",
                    "help": "libmulti_set_y(window, new_y) ->real  :  Sets the Y position of the client area of the window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_set_y",
                    "returnType": 2
                },
                {
                    "id": "408c7769-ba97-7874-8dd0-259f9202ee4e",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 2,
                    "args": [
                        2,
                        2
                    ],
                    "externalName": "libmulti_set_width",
                    "help": "libmulti_set_width(window, new_width) ->real  :  Sets the width of the client area of the window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_set_width",
                    "returnType": 2
                },
                {
                    "id": "bf057d55-97ef-b317-f99b-498e682563ac",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 2,
                    "args": [
                        2,
                        2
                    ],
                    "externalName": "libmulti_set_height",
                    "help": "libmulti_set_height(window, new_height) ->real  :  Sets the height of the client area of the window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_set_height",
                    "returnType": 2
                },
                {
                    "id": "5ab781da-876b-7a45-0935-59a171ffa0e5",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 3,
                    "args": [
                        2,
                        2,
                        2
                    ],
                    "externalName": "libmulti_set_position",
                    "help": "libmulti_set_position(window, x, y) ->real  :  Sets the position of the client area of the window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_set_position",
                    "returnType": 2
                },
                {
                    "id": "c2917afd-be3d-2c7c-3d5d-056c0af72e08",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 3,
                    "args": [
                        2,
                        2,
                        2
                    ],
                    "externalName": "libmulti_set_size",
                    "help": "libmulti_set_size(window, new_width, new_height) ->real  :  Sets the size of the client area of the window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_set_size",
                    "returnType": 2
                },
                {
                    "id": "81f503d6-96a7-5ceb-93bd-b157bc0da8bc",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 5,
                    "args": [
                        2,
                        2,
                        2,
                        2,
                        2
                    ],
                    "externalName": "libmulti_set_rectangle",
                    "help": "libmulti_set_rectangle(window, new_x, new_y, new_width, new_height) ->real  :  Sets the window's client area rectangle.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_set_rectangle",
                    "returnType": 2
                },
                {
                    "id": "eb41d2b0-0e3a-af63-b4df-32d7c7932fb1",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "libmulti_get_nonclient_left",
                    "help": "libmulti_get_nonclient_left(window) ->real  :  Gets the left offset of the window's non-client area.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_get_nonclient_left",
                    "returnType": 2
                },
                {
                    "id": "ad9a8dd7-7adc-dacc-5d15-ac9bed4598e0",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "libmulti_get_nonclient_top",
                    "help": "libmulti_get_nonclient_top(window) ->real  :  Gets the top offset of the window's non-client area.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_get_nonclient_top",
                    "returnType": 2
                },
                {
                    "id": "21fd6cbe-7679-5091-bdd4-d57e4dcb97ee",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "libmulti_get_nonclient_right",
                    "help": "libmulti_get_nonclient_right(window) ->real  :  Gets the right offset of the window's non-client area.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_get_nonclient_right",
                    "returnType": 2
                },
                {
                    "id": "bc9bbe69-23e4-4f5d-32ab-a92ca188ff4f",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "libmulti_get_nonclient_bottom",
                    "help": "libmulti_get_nonclient_bottom(window) ->real  :  Gets the bottom offset of the window's non-client area.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_get_nonclient_bottom",
                    "returnType": 2
                },
                {
                    "id": "89d87e6c-7429-7394-8f86-c241ac1a6ea2",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "libmulti_get_caption",
                    "help": "libmulti_get_caption(window) ->string  :  Gets the window's caption.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_get_caption",
                    "returnType": 1
                },
                {
                    "id": "febb1c64-ce46-7857-7400-7e354ceacb69",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 3,
                    "args": [
                        2,
                        2,
                        2
                    ],
                    "externalName": "libmulti_set_window_style",
                    "help": "libmulti_set_window_style(window, is_extended, style_value) ->real  :  Sets the extended or window style.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_set_window_style",
                    "returnType": 2
                },
                {
                    "id": "90a87e3b-83ae-dda1-6a32-dab0b565eb70",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 2,
                    "args": [
                        2,
                        2
                    ],
                    "externalName": "libmulti_get_window_style",
                    "help": "libmulti_get_window_style(window, is_extended) ->real  :  Gets the window or the extended style.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_get_window_style",
                    "returnType": 2
                },
                {
                    "id": "7bc6edf8-0574-4487-1d32-84bf59d17dcd",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 2,
                    "args": [
                        2,
                        2
                    ],
                    "externalName": "libmulti_set_min_width",
                    "help": "libmulti_set_min_width(window, new_min_width) ->real  :  Sets the minimum allowed width of the window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_set_min_width",
                    "returnType": 2
                },
                {
                    "id": "b9621339-aa18-36c6-df41-85730d14fd03",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 2,
                    "args": [
                        2,
                        2
                    ],
                    "externalName": "libmulti_set_min_height",
                    "help": "libmulti_set_min_height(window, new_min_height) ->real  :  Sets the minimum allowed height of the window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_set_min_height",
                    "returnType": 2
                },
                {
                    "id": "899ad65d-998e-22ce-d648-9b4623131f9d",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 2,
                    "args": [
                        2,
                        2
                    ],
                    "externalName": "libmulti_set_max_width",
                    "help": "libmulti_set_max_width(window, new_max_width) ->real  :  Sets the maximum allowed width of the window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_set_max_width",
                    "returnType": 2
                },
                {
                    "id": "9e09d297-967e-d80e-1369-989c428a42ba",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 2,
                    "args": [
                        2,
                        2
                    ],
                    "externalName": "libmulti_set_max_height",
                    "help": "libmulti_set_max_height(window, new_max_height) ->real  :  Sets the maximum allowed height of the window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_set_max_height",
                    "returnType": 2
                },
                {
                    "id": "0b54120a-dcf2-4699-232e-8031434aae37",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 3,
                    "args": [
                        2,
                        2,
                        2
                    ],
                    "externalName": "libmulti_set_min_size",
                    "help": "libmulti_set_min_size(window, new_min_width, new_min_height) ->real  :  Sets the minimum allowed size of the window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_set_min_size",
                    "returnType": 2
                },
                {
                    "id": "bce13bce-2ccc-978e-9e70-0d2f740ee60e",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 3,
                    "args": [
                        2,
                        2,
                        2
                    ],
                    "externalName": "libmulti_set_max_size",
                    "help": "libmulti_set_max_size(window, new_max_width, new_max_height) ->real  :  Sets the maximum allowed size of the window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_set_max_size",
                    "returnType": 2
                },
                {
                    "id": "97788766-73bc-377d-b50b-627d9eaebe0c",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "libmulti_get_min_width",
                    "help": "libmulti_get_min_width(window) ->real  :  Gets the minimum allowed width of the window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_get_min_width",
                    "returnType": 2
                },
                {
                    "id": "bd21f062-709c-16cf-c228-548709e9c7b8",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "libmulti_get_min_height",
                    "help": "libmulti_get_min_height(window) ->real  :  Gets the minimum allowed height of the window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_get_min_height",
                    "returnType": 2
                },
                {
                    "id": "2e0646eb-fd35-8ab3-2a29-b8765b051c60",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "libmulti_get_max_width",
                    "help": "libmulti_get_max_width(window) ->real  :  Gets the maximum allowed width of the window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_get_max_width",
                    "returnType": 2
                },
                {
                    "id": "509356b5-4787-12e6-db71-51ca7a096892",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "libmulti_get_max_height",
                    "help": "libmulti_get_max_height(window) ->real  :  Gets the maximum allowed height of the window.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_get_max_height",
                    "returnType": 2
                },
                {
                    "id": "73f808dc-fc44-0f52-c986-54a33fbb52fc",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "libmulti_mouse_get_x",
                    "help": "libmulti_mouse_get_x(window) ->real  :  Gets the last X mouse coord relative to the window's client area.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_mouse_get_x",
                    "returnType": 2
                },
                {
                    "id": "d6fd2655-ea28-c8a7-5dcc-f3c38b40c26d",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "libmulti_mouse_get_y",
                    "help": "libmulti_mouse_get_y(window) ->real  :  Gets the last Y mouse coord relative to the window's client area.",
                    "hidden": false,
                    "kind": 1,
                    "name": "libmulti_mouse_get_y",
                    "returnType": 2
                }
            ],
            "init": "",
            "kind": 1,
            "order": [
                
            ],
            "origname": "",
            "uncompress": false
        }
    ],
    "gradleinject": "",
    "helpfile": "",
    "installdir": "",
    "iosProps": false,
    "iosSystemFrameworkEntries": [
        
    ],
    "iosThirdPartyFrameworkEntries": [
        
    ],
    "iosdelegatename": "",
    "iosplistinject": "",
    "license": "",
    "maccompilerflags": "",
    "maclinkerflags": "",
    "macsourcedir": "",
    "options": null,
    "optionsFile": "options.json",
    "packageID": "",
    "productID": "",
    "sourcedir": "",
    "supportedTargets": -1,
    "tvosProps": false,
    "tvosSystemFrameworkEntries": [
        
    ],
    "tvosThirdPartyFrameworkEntries": [
        
    ],
    "tvosclassname": "",
    "tvosdelegatename": "",
    "tvosmaccompilerflags": "",
    "tvosmaclinkerflags": "",
    "tvosplistinject": "",
    "version": "1.2.0"
}