//
// Created by sk337 on 1/24/25.
//

#include "base64.h"
#include <string>
#include <lua.hpp>
#include <vector>

static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

std::string base64_encode_impl(const std::string &in) {
    std::string out;
    int val = 0, valb = -6;
    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(base64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) out.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4) out.push_back('=');
    return out;
}

std::string base64_decode_impl(const std::string &in) {
    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) T[base64_chars[i]] = i;

    std::string out;
    int val = 0, valb = -8;
    for (unsigned char c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}

int base64_encode(lua_State *L) {
    if (lua_gettop(L) != 1 || !lua_isstring(L, 1)) {
        lua_pushstring(L, "Invalid arguments, expected 1 string");
        lua_error(L);
        return 0;
    }

    std::string str(lua_tostring(L, 1));
    std::string encoded = base64_encode_impl(str);

    lua_pushstring(L, encoded.c_str());
    return 1;  // Number of return values
}

int base64_decode(lua_State *L) {
    if (lua_gettop(L) != 1 || !lua_isstring(L, 1)) {
        lua_pushstring(L, "Invalid arguments, expected 1 string");
        lua_error(L);
        return 0;
    }

    std::string str(lua_tostring(L, 1));
    std::string decoded = base64_decode_impl(str);

    lua_pushstring(L, decoded.c_str());
    return 1;  // Number of return values
}
