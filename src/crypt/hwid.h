//
// Created by sk337 on 1/24/25.
//

#ifndef HWID_H
#define HWID_H
#include <string>
#include <lua.hpp>


std::string GetMachineUUID();
int getHWID(lua_State *L);

#endif //HWID_H
