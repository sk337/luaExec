#!/bin/bash

rm -rf external/lua
mkdir -p external/lua

LUA_VERSION=5.4.7

wget https://www.lua.org/ftp/lua-$LUA_VERSION.tar.gz

# Extract directly into external/lua
tar --strip-components=1 -xvf lua-$LUA_VERSION.tar.gz -C external/lua

rm lua-$LUA_VERSION.tar.gz
