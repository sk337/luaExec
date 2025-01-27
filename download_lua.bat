@echo off
setlocal enabledelayedexpansion

:: Remove the external/lua directory if it exists and recreate it
if exist external\lua (
    rmdir /s /q external\lua
)
mkdir external\lua

:: Set the Lua version
set LUA_VERSION=5.4.7

:: Download the Lua tarball
curl -O https://www.lua.org/ftp/lua-%LUA_VERSION%.tar.gz

:: Extract the tarball directly into external/lua
tar --strip-components=1 -xvf lua-%LUA_VERSION%.tar.gz -C external\lua

:: Remove the downloaded tarball
del lua-%LUA_VERSION%.tar.gz
