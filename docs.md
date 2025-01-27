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