//
// Created by sk337 on 1/24/25.
//

#ifndef RAND_H
#define RAND_H
#include <lua.hpp>

int luaL_random_bytes(lua_State* L);
int luaL_random_int(lua_State* L);
int luaL_random_float(lua_State* L);

#endif //RAND_H
