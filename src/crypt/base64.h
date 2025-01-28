//
// Created by sk337 on 1/24/25.
//

#ifndef BASE64_H
#define BASE64_H

#include<lua.hpp>

int luaL_base64_encode(lua_State *L);
int luaL_base64_decode(lua_State *L);

#endif //BASE64_H
