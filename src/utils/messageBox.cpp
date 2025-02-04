//
// Created by natet on 1/28/2025.
//

#include "messageBox.h"
#include <lua.hpp>

#ifdef _WIN32

#include <Windows.h>
int luaL_messageBox(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    const char *caption = luaL_checkstring(L, 2);
    int type = luaL_checkinteger(L, 3);

    int response = MessageBoxA(NULL, text, caption, type);

    lua_pushinteger(L, response);

    return 1;
}

#else

int luaL_messageBox(lua_State *L) {
    luaL_error(L, "Function Not Implmentated on platform")
}

#endif
