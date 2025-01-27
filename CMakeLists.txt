cmake_minimum_required(VERSION 3.10)

project(lueExec C CXX)

set(LUA_LIBARY_PATH "${CMAKE_SOURCE_DIR}/external/lua/src")

add_library(liblua
        ${LUA_LIBARY_PATH}/lapi.c
        ${LUA_LIBARY_PATH}/lapi.h
        ${LUA_LIBARY_PATH}/lcode.c
        ${LUA_LIBARY_PATH}/lcode.h
        ${LUA_LIBARY_PATH}/lctype.c
        ${LUA_LIBARY_PATH}/lctype.h
        ${LUA_LIBARY_PATH}/ldebug.c
        ${LUA_LIBARY_PATH}/ldebug.h
        ${LUA_LIBARY_PATH}/ldo.c
        ${LUA_LIBARY_PATH}/ldo.h
        ${LUA_LIBARY_PATH}/ldump.c
        ${LUA_LIBARY_PATH}/lfunc.c
        ${LUA_LIBARY_PATH}/lfunc.h
        ${LUA_LIBARY_PATH}/lgc.c
        ${LUA_LIBARY_PATH}/lgc.h
        ${LUA_LIBARY_PATH}/llex.c
        ${LUA_LIBARY_PATH}/llex.h
        ${LUA_LIBARY_PATH}/lmem.c
        ${LUA_LIBARY_PATH}/lmem.h
        ${LUA_LIBARY_PATH}/lobject.c
        ${LUA_LIBARY_PATH}/lobject.h
        ${LUA_LIBARY_PATH}/lopcodes.c
        ${LUA_LIBARY_PATH}/lopcodes.h
        ${LUA_LIBARY_PATH}/lparser.c
        ${LUA_LIBARY_PATH}/lparser.h
        ${LUA_LIBARY_PATH}/lstate.c
        ${LUA_LIBARY_PATH}/lstate.h
        ${LUA_LIBARY_PATH}/lstring.c
        ${LUA_LIBARY_PATH}/lstring.h
        ${LUA_LIBARY_PATH}/lauxlib.c
        ${LUA_LIBARY_PATH}/lauxlib.h
        ${LUA_LIBARY_PATH}/lbaselib.c
        ${LUA_LIBARY_PATH}/lcorolib.c
        ${LUA_LIBARY_PATH}/ldblib.c
        ${LUA_LIBARY_PATH}/liolib.c
        ${LUA_LIBARY_PATH}/lmathlib.c
        ${LUA_LIBARY_PATH}/loadlib.c
        ${LUA_LIBARY_PATH}/loslib.c
        ${LUA_LIBARY_PATH}/lstrlib.c
        ${LUA_LIBARY_PATH}/ltablib.c
        ${LUA_LIBARY_PATH}/lutf8lib.c
        ${LUA_LIBARY_PATH}/linit.c
        ${LUA_LIBARY_PATH}/lzio.c
        ${LUA_LIBARY_PATH}/lzio.h
        ${LUA_LIBARY_PATH}/lvm.h
        ${LUA_LIBARY_PATH}/lvm.c
        ${LUA_LIBARY_PATH}/ltable.c
        ${LUA_LIBARY_PATH}/ltable.h
        ${LUA_LIBARY_PATH}/ltm.c
        ${LUA_LIBARY_PATH}/ltm.h
        ${LUA_LIBARY_PATH}/lundump.c
        ${LUA_LIBARY_PATH}/lundump.h
)

set_target_properties(liblua PROPERTIES OUTPUT_NAME lua)


#if(WIN32)
#    message(STATUS "Platform detected: Windows")
#    add_definitions(-DLUA_USE_WINDOWS)
#elseif(UNIX)
#    message(STATUS "Platform detected: Unix/Linux")
#    add_definitions(-DLUA_USE_LINUX)
#else()
#    message(WARNING "Unknown platform: No LUA_USE_* macro will be defined.")
#endif()

add_executable(lua
    ${LUA_LIBARY_PATH}/lua.c
)

target_link_libraries(lua PRIVATE liblua)

add_executable(luac
        ${LUA_LIBARY_PATH}/luac.c
)

target_link_libraries(luac PRIVATE liblua)

add_executable(luaRunner src/main.cpp src/bytecode.h
        src/crypt/hwid.cpp
        src/crypt/hwid.h
        src/crypt/base64.cpp
        src/crypt/base64.h
        src/crypt/rand.cpp
        src/crypt/rand.h
)


target_include_directories(luaRunner PRIVATE ${LUA_LIBARY_PATH})

target_link_libraries(luaRunner PRIVATE liblua)

