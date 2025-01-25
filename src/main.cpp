//
// Created by sk337 on 1/24/25.
//

#include <lua.hpp>
#include <iostream>
#include <unistd.h>

#include "bytecode.h"
#include "crypt/hwid.h"
#include "crypt/base64.h"
#include "crypt/rand.h"


int main(){
    lua_State* L = luaL_newstate();
    if (!L) {
        std::cerr << "Failed to create Lua state" << std::endl;
        return 1;
    }

    // Open standard Lua libraries
    luaL_openlibs(L);


    lua_register(L, "base64_decode", base64_decode);
    lua_register(L, "base64_encode", base64_encode);
    lua_register(L, "random_bytes", random_bytes);
    lua_register(L, "random_float", random_float);
    lua_register(L, "random_int", random_int);
    lua_register(L, "getHWID", getHWID);



    // Load Lua bytecode into Lua state
    if (luaL_loadbuffer(L, reinterpret_cast<const char*>(bytecode), bytecode_len, "") != LUA_OK) {
        std::cerr << "Failed to load bytecode" << std::endl;
        lua_close(L);
        return 1;
    }

    // Execute Lua bytecode
    if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
        std::cerr << "failed to call pcall" << std::endl;
        lua_close(L);
        return 1;
    }

    // Close Lua state
    lua_close(L);

    return 0;


}