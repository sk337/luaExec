//
// Created by natet on 1/28/2025.
//

#include "messageBox.h"
#include <lua.hpp>

#ifdef _WIN32

#include <Windows.h>
int luaL_messageBox(lua_State *L) {
    // Check and retrieve arguments from Lua
    const char *text = luaL_checkstring(L, 1);      // Get the first argument (text)
    const char *caption = luaL_checkstring(L, 2);   // Get the second argument (caption)
    int type = luaL_checkinteger(L, 3);             // Get the third argument (type)

    // Display the message box
    int response = MessageBoxA(NULL, text, caption, type);

    // Push the response code onto the Lua stack
    lua_pushinteger(L, response);

    return 1; // Return one value (the response code) to Lua
}

#else

int luaL_messageBox(lua_State *L) {
    luaL_error(L, "Function Not Implmentated on platform")
}

#endif
