#!/usr/bin/env bash

# Check if the --bypass-wsl flag is set
if [[ "$1" == "--bypass-wsl" ]]; then
    # If bypass flag is set, do not check for WSL
    bypass_wsl=true
else
    bypass_wsl=false
fi

# Check if running under WSL and bypass flag is not set
if [[ "$(uname -r)" == *Microsoft* && "$bypass_wsl" == false ]]; then
    # Running under WSL, use exe versions of luac
    if [[ "$1" == "-r" || "$1" == "--release" ]]; then
        # Run in release mode with exe version
        ./cmake-build-release/luac.exe -s source.lua
    else
        # Run in debug mode with exe version
        ./cmake-build-debug/luac.exe source.lua
    fi
else
    # Not running under WSL or bypass flag is set, use regular luac
    if [[ "$1" == "-r" || "$1" == "--release" ]]; then
        # Run in release mode
        ./cmake-build-release/luac -s source.lua
    else
        # Run in debug mode
        ./cmake-build-debug/luac source.lua
    fi
fi

xxd -n bytecode -i luac.out > src/bytecode.h
