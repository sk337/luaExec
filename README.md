# Lua Exec

> A self-contained Lua runtime environment with additional functions.

## Overview

Lua Exec is a **cross-platform** Lua runtime designed for **Windows and Linux**, with planned support for **macOS**. It provides an isolated execution environment with extended capabilities, making it easy to integrate Lua scripting into various applications.

Built with **CMake**, Lua Exec ensures a straightforward build process across different operating systems, whether using **CLion** or the command line.

## Features

* **Cross Platform:** Fully supports Windows and Linux, with macOS support in progress.
* **Self-contained:** No external dependencies required for runtime execution.
* **Extended functionality:** Includes additional helper functions beyond standard Lua.
* **Easy to build:** Compatible with CLion and simple command-line setup.

## Building

### Using CLion

No special setup is required—everything should configure itself automatically, as the project was created in CLion.

### Commandline

To manually set up and build the project via the command line, use the following steps:

#### Release Build

```shell
mkdir cmake-build-release
cd cmake-build-release
cmake -S .. -DCMAKE_BUILD_TYPE=Release
cmake ./
```

#### Debug Build

```shell
mkdir cmake-build-debug
cd cmake-build-debug
cmake -S .. -DCMAKE_BUILD_TYPE=Debug
cmake ./
```

## Setting Up Lua

Before building, you need to **download Lua**. Run one of the following scripts depending on your platform:

- **For Linux**:
  ```sh
  ./download_lua.sh
  ```

- **For Windows**:
  ```sh
  download_lua.bat
  ```

These scripts will automatically download the necessary Lua files for your environment.

### Prerequisites
After downloading Lua, ensure that the **`luac` target is built first** before running the bytecode build script.

## Building Bytecode

To generate Lua bytecode, run `./build_bytecode.sh` **whenever the target file is changed**. This must be done in a **WSL/Linux environment** with `xxd` installed.

### Prerequisites
- Ensure that the **`luac` target is built first** before running the script.
- Use the `-r` argument to generate a **release build** of `luac`, which strips debug info from the Lua bytecode.

### Running the Script

#### Standard Bytecode Build

```sh
./build_bytecode.sh
```

#### Release Bytecode Build (Strips Debug Info)

```sh
./build_bytecode.sh -r
```

Use the `-r` flag when you need optimized bytecode without debug symbols.  

