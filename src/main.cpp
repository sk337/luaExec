//
// Created by sk337 on 1/24/25.
//

#include <lua.hpp>
#include <iostream>

#include "bytecode.h"
#include "crypt/hwid.h"
#include "crypt/base64.h"
#include "crypt/rand.h"
#include "fs/fs.h"
#include "utils/getEnviron.h"
#include "utils/messageBox.h"

void handleLuaError(lua_State *L, const std::string &errorMessage) {
#ifndef NDEBUG
    std::cerr << errorMessage << lua_tostring(L, -1) << std::endl;
#endif
    lua_close(L);
}

int main() {
    lua_State* L = luaL_newstate();
    if (!L) {
        handleLuaError(L, "Failed to create Lua state");
    }

    lua_pushboolean(L, true);
    lua_setglobal(L, "is_luaExec_closure");
    // Open standard Lua libraries
    luaL_openlibs(L);

    // base64
    lua_register(L, "base64_decode", luaL_base64_decode);
    lua_register(L, "base64_encode", luaL_base64_encode);
    // rando,
    lua_register(L, "random_bytes", luaL_random_bytes);
    lua_register(L, "random_float", luaL_random_float);
    lua_register(L, "random_int", luaL_random_int);
    //utils
    lua_register(L, "getHWID", luaL_getHWID);
    lua_register(L, "getEnviron", luaL_getEnviron);
    lua_register(L, "messageBox", luaL_messageBox);
    //fs
    lua_register(L, "readFile", luaL_readFile);
    lua_register(L, "writeFile", luaL_writeFile);
    lua_register(L, "appendFile", luaL_appendFile);
    lua_register(L, "fileExists", luaL_fileExists);
    lua_register(L, "directoryExists", luaL_directoryExists);
    lua_register(L, "rmdir", luaL_rmdir);
    lua_register(L, "rm", luaL_rm);

    // Load Lua bytecode into Lua state
    if (luaL_loadbuffer(L, reinterpret_cast<const char*>(bytecode), bytecode_len, "") != LUA_OK) {
        handleLuaError(L, "Failed to load bytecode");
        return 1;
    }

    // Execute Lua bytecode
    if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
        handleLuaError(L, "Failed to run bytecode");
        return 1;
    }

    // Close Lua state
    lua_close(L);

    return 0;
}
