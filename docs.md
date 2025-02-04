# My Custom Envrionment


## Crypt

Cryptography / encoding related functions.

---
### `base64_encode(data: string) -> string` ✅


Encodes data to base64

---
### `base64_decode(data: string) -> string` ✅

Decodes data from base64

---
### `getHWID() -> string` ✅

Returns a Unique identifier for the device

---
### `random_bytes(count: number?) -> string` ✅

returns `count` or 16 if not provided random bytes as a hex formatted string.

---
### `random_int(min: number, max: number) -> number` ✅

returns an `int` between `min` and `max`

---
### `random_float() -> number` ✅

return a float between 0 and 1

---
### `getEnviron() -> string` ✅

Gets the current Host operating system and returns of the following values

* WINDOWS
* LINUX
* MACOS
* UNKNOWN

---
### `readFile(path: string) -> string` ✅

Reads the contents of a file to a string

---
### `writeFile(path: string, data: string)` ✅

Write string data to a file

---
### `appendFile(path: string, data: string)` ✅

Append data to a file

---
### `fileExists(path: string) -> boolean` ✅

Check if a file exists returns `false` if path either doesnt exist or is a folder. only returns `true` if a file is found

---
### `directoryExitsts(path: string) -> boolean` ✅

Check if a directory exists returns `false` if path either doesnt exist or it is a file. only return `true` if a directory is found

---
### `mkdir(path: string, recursive: boolean?) -> string` ❌

Create a directory at path without creating non existent parent folder unless recursive flag is applied. returns absolute path of created directory 

---
### `rmdir(path: string, rf: boolean?)` ✅

Removes a directory that is empty unless rf is set to `true` then directory is deleted recursively

---
### `rm(path: string)` ✅

Remove a file. will error if directory is targeted

---
### `copy(path: string, destination: string)` ✅

Copies file from a path to a destination

---
### `rename(path: string, destination: string)` ✅

Renames a file

---
### `createTempDir(name: string?) -> string` ❌

Create a temp directory with a random or provided name

