# Lua Exec

> A self-contained lua runtime environment with some extra functions

## Building

### With CLion

You dont need to do anything special everything should set itself up as I made the project in CLion

### Commandline

Setup and build with command line

#### Release

```shell
mkdir cmake-build-release
cd cmake-build-release
cmake -S .. -DCMAKE_BUILD_TYPE=release
cmake ./
```

#### Debug

```shell
mkdir cmake-build-debug
cd cmake-build-debug
cmake -S .. -DCMAKE_BUILD_TYPE=debug
cmake ./
```