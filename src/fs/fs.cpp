//
// Created by natet on 1/27/2025.
//

#include "fs.h"

#include <string>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <stdexcept>
#include <filesystem>


namespace fs = std::filesystem;

int luaL_readFile(lua_State *L) {
    std::string fileName = luaL_checkstring(L, 1);
    if (fileName.empty()) {
        luaL_error(L, "File name cannot be empty");
        return 0;
    }

    std::ifstream file(fileName);
    if (!file.is_open()) {
        luaL_error(L, "File could not be opened");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    file.close();

    lua_pushstring(L, buffer.str().c_str());
    return 1;
}

int luaL_writeFile(lua_State *L) {
    std::string fileName = luaL_checkstring(L, 1);
    if (fileName.empty()) {
        luaL_error(L, "File name cannot be empty");
        return 0;
    }

    std::string fileContents = luaL_checkstring(L, 2);

    std::ofstream file(fileName);
    if (!file.is_open()) {
        luaL_error(L, "File could not be opened");
        return 0;
    }

    file.write(fileContents.c_str(), static_cast<long long>(fileContents.size()));

    file.close();
    return 0;
}

int luaL_appendFile(lua_State *L) {
    std::string fileName = luaL_checkstring(L, 1);
    if (fileName.empty()) {
        luaL_error(L, "File name cannot be empty");
        return 0;
    }

    std::string fileContent = luaL_checkstring(L, 2);

    std::ofstream file(fileName, std::ios::app);
    if (!file.is_open()) {
        luaL_error(L, "File could not be opened");
        return 0;
    }

    file.write(fileContent.c_str(), static_cast<long long>(fileContent.size()));
    file.close();
    return 0;

}

int luaL_fileExists(lua_State *L) {
    std::string fileName = luaL_checkstring(L, 1);
    if (fileName.empty()) {
        lua_pushboolean(L, false);
        return 1;
    }

    std::ifstream file(fileName);
    if (!file.is_open()) {
        lua_pushboolean(L, false);
        return 1;
    }
    lua_pushboolean(L, true);
    return 1;
}

int luaL_directoryExists(lua_State *L) {
    std::string fileName = luaL_checkstring(L, 1);
    if (fileName.empty()) {
        lua_pushboolean(L, false);
        return 1;
    }

    struct stat info;
    if (stat(fileName.c_str(), &info) == 0 && (info.st_mode & S_IFDIR)) {
        lua_pushboolean(L, true);
    } else {
        lua_pushboolean(L, false);
    }
    return 1;
}


// int luaL_mkdir(lua_State* L) {
//     std::string path = luaL_checkstring(L, 1);
//     bool recursive = lua_toboolean(L, 2);
//
//     try {
//         if (recursive) {
//             fs::create_directories(path);
//         } else {
//             fs::create_directory(path);
//         }
//         lua_pushstring(L, fs::absolute(path).c_str());
//     } catch (const std::exception& e) {
//         luaL_error(L, "Failed to create directory: %s", e.what());
//     }
//     return 1;
// }

int luaL_rmdir(lua_State* L) {
    std::string path = luaL_checkstring(L, 1);
    bool recursive = lua_toboolean(L, 2);

    try {
        if (recursive) {
            fs::remove_all(path);
        } else {
            if (!fs::is_empty(path)) {
                luaL_error(L, "Directory is not empty");
            }
            fs::remove(path);
        }
    } catch (const std::exception& e) {
        luaL_error(L, "Failed to remove directory: %s", e.what());
    }
    return 0;
}

int luaL_rm(lua_State* L) {
    std::string path = luaL_checkstring(L, 1);

    try {
        if (fs::is_directory(path)) {
            luaL_error(L, "Target is a directory, use rmdir");
        }
        fs::remove(path);
    } catch (const std::exception& e) {
        luaL_error(L, "Failed to remove file: %s", e.what());
    }
    return 0;
}

int luaL_copy(lua_State* L) {
    std::string source = luaL_checkstring(L, 1);
    std::string destination = luaL_checkstring(L, 2);

    try {
        fs::copy(source, destination, fs::copy_options::overwrite_existing);
    } catch (const std::exception& e) {
        luaL_error(L, "Failed to copy file: %s", e.what());
    }
    return 0;
}

int luaL_rename(lua_State* L) {
    std::string source = luaL_checkstring(L, 1);
    std::string destination = luaL_checkstring(L, 2);

    try {
        fs::rename(source, destination);
    } catch (const std::exception& e) {
        luaL_error(L, "Failed to rename file: %s", e.what());
    }
    return 0;
}

// int luaL_createTempDir(lua_State* L) {
//     std::string name = luaL_optstring(L, 1, "");
//     try {
//         fs::path tempDir = fs::temp_directory_path() / (name.empty() ? fs::unique_path() : name);
//         fs::create_directory(tempDir);
//         lua_pushstring(L, tempDir.c_str());
//     } catch (const std::exception& e) {
//         luaL_error(L, "Failed to create temporary directory: %s", e.what());
//     }
//     return 1;
// }