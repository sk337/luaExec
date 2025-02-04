//
// Created by natet on 1/27/2025.
//

#include "getEnviron.h"


int luaL_getEnviron(lua_State *L) {
#ifdef _WIN32
    lua_pushstring(L, "WINDOWS");
#elif defined(__linux__)
    lua_pushstring(L, "LINUX");
#elif defined(__APPLE__) || defined(__MACH__)
    lua_pushstring(L, "MACOS");
#else
    lua_pushstring(L, "UNKNOWN");
#endif
    return 1;
}