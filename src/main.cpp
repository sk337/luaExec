//
// Created by sk337 on 1/24/25.
//

#include <lua.hpp>
#include <iostream>

#include "bytecode.h"
#include "crypt/hwid.h"
#include "crypt/base64.h"
#include "crypt/rand.h"
#include "utils/getEnviron.h"

int main() {
    // std::cout << GetMachineUUID() << std::endl;
    lua_State* L = luaL_newstate();
    if (!L) {
#ifndef NDEBUG
        std::cerr << "Failed to create Lua state" << std::endl;
#endif
        return 1;
    }

    // Open standard Lua libraries
    luaL_openlibs(L);

    lua_register(L, "base64_decode", luaL_base64_decode);
    lua_register(L, "base64_encode", luaL_base64_encode);
    lua_register(L, "random_bytes", luaL_random_bytes);
    lua_register(L, "random_float", luaL_random_float);
    lua_register(L, "random_int", luaL_random_int);
    lua_register(L, "getHWID", luaL_getHWID);
    lua_register(L, "getEnviron", luaL_getEnviron);

    // Load Lua bytecode into Lua state
    if (luaL_loadbuffer(L, reinterpret_cast<const char*>(bytecode), bytecode_len, "") != LUA_OK) {
#ifndef NDEBUG
        std::cerr << "Failed to load bytecode: " << lua_tostring(L, -1) << std::endl;
#endif
        lua_close(L);
        return 1;
    }

    // Execute Lua bytecode
    if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
#ifndef NDEBUG
        // Get error message from Lua stack
        const char* errorMsg = lua_tostring(L, -1);
        std::cerr << "Failed to execute Lua bytecode: "
                  << (errorMsg ? errorMsg : "Unknown error")
                  << std::endl;
        lua_pop(L, 1); // Remove error message from stack
#endif
        lua_close(L);
        return 1;
    }

    // Close Lua state
    lua_close(L);

    return 0;
}
