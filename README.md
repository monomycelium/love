# `love`
A CLI tool to find the chances of success in a relationship using the name of each party. The purpose of the project was to explore using the CMake build system, so features are minimal.

### demo
[![asciicast](https://asciinema.ilmul.com/a/eSlRtLnIEILh4MdKVQ9dRGsvQ.svg)](https://asciinema.ilmul.com/a/eSlRtLnIEILh4MdKVQ9dRGsvQ)

### building
Ensure you have `jansson`, `libcurl` and `cmake` installed.
``` console
$ cmake -B build
$ cmake --build build
```
The executable should be available at `./build/love`.
