//
// Created by sk337 on 1/24/25.
//

#include "rand.h"
#include <lua.hpp>
#include <vector>
#include <random>
#include <sstream>
#include <iomanip>

int luaL_random_bytes(lua_State *L) {
    int num_bytes;

    // Validate arguments
    if (lua_gettop(L) > 1 || (lua_gettop(L) == 1 && !lua_isnumber(L, 1))) {
        lua_pushstring(L, "Invalid argument. Must provide 1 number or none.");
        lua_error(L);
        return 0;
    }

    // Determine the number of bytes to generate
    if (lua_gettop(L) == 0) {
        num_bytes = 16; // Default to 16 bytes
    } else {
        num_bytes = lua_tointeger(L, 1);
        if (num_bytes <= 0) {
            lua_pushstring(L, "Number of bytes must be greater than 0.");
            lua_error(L);
            return 0;
        }
    }

    // Generate random bytes
    std::vector<unsigned char> bytes(num_bytes);
    std::random_device rd;
    for (int i = 0; i < num_bytes; ++i) {
        bytes[i] = rd() % 256;
    }

    // Convert bytes to hexadecimal string
    std::ostringstream hex_stream;
    hex_stream << std::hex << std::setfill('0');
    for (unsigned char byte : bytes) {
        hex_stream << std::setw(2) << static_cast<int>(byte);
    }

    std::string hex_output = hex_stream.str();

    // Push the hexadecimal string onto the Lua stack
    lua_pushstring(L, hex_output.c_str());
    return 1; // Number of return values
}

int luaL_random_int(lua_State* L) {
    // Validate arguments
    if (lua_gettop(L) != 2 || !lua_isnumber(L, 1) || !lua_isnumber(L, 2)) {
        lua_pushstring(L, "Invalid arguments. Must provide 2 numbers (min, max).");
        lua_error(L);
        return 0;
    }

    int min = lua_tointeger(L, 1);
    int max = lua_tointeger(L, 2);

    if (min > max) {
        lua_pushstring(L, "Invalid range. Min must be less than or equal to max.");
        lua_error(L);
        return 0;
    }

    // Generate random integer in the range [min, max]
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);

    int result = distrib(gen);
    lua_pushinteger(L, result);
    return 1; // Number of return values
}

int luaL_random_float(lua_State* L) {
    // Validate arguments (should have none)
    if (lua_gettop(L) != 0) {
        lua_pushstring(L, "Invalid arguments. random_float takes no arguments.");
        lua_error(L);
        return 0;
    }

    // Generate random float in the range [0.0, 1.0)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(0.0, 1.0);

    double result = distrib(gen);
    lua_pushnumber(L, result);
    return 1; // Number of return values
}

