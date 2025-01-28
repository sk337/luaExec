//
// Created by natet on 1/27/2025.
//

#ifndef FS_H
#define FS_H

#include <lua.hpp>

int luaL_readFile(lua_State* L);
int luaL_writeFile(lua_State* L);
int luaL_appendFile(lua_State* L);
int luaL_fileExists(lua_State* L);
int luaL_directoryExists(lua_State* L);
int luaL_mkdir(lua_State* L);
int luaL_rmdir(lua_State* L);
int luaL_rm(lua_State* L);
int luaL_copy(lua_State* L);
int luaL_rename(lua_State* L);
int luaL_createTempDir(lua_State* L);


#endif //FS_H
