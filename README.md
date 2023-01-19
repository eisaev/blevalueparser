![Building Examples](https://github.com/eisaev/blevalueparser/actions/workflows/examples.yml/badge.svg)
![Testing](https://github.com/eisaev/blevalueparser/actions/workflows/tests.yml/badge.svg)
![Code Coverage](https://img.shields.io/badge/Code%20Coverage-87%25-yellow?style=flat)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# BLE Value Parser
This is a header only library for parsing characteristics of some standardized BLE services. At the moment, parsers are partially implemented for the following services:
* Device Information Service v1.1
* Current Time Service v1.1
* Battery Service v1.1
* Heart Rate Service v1.0

This library is designed for rapid prototyping of BLE applications and isn't optimized for either performance or consumption. You can use the library code as example to implement a parser optimized for a specific platform/case. Also, usually you'll need a parser only for certain services, and not all implemented in the library.

# Usage
You just need to include the header file in your C++ file to use parsers. For example:
```c++
#include "blevalueparser.h"

[...]

void printBatteryLevel(const char *data, size_t size)
{
    bvp::BLEValueParser bleValueParser;
    auto result = bleValueParser.make_value<bvp::BatteryLevel>(data, size);
    if (!result->isValid())
    {
        std::cout << "Invalid data" << std::endl;
        return;
    }

    std::cout << "Battery Level: " << int(result->level()) << "%" << std::endl;
}
```

# Build Tests and Example
To build you'll need at least CMake and Qt5 or Qt6.

## macOS

### Console
1. Generate project:
  * To build with Qt5 on Apple silicon:
```sh
cmake -B ./build -DCMAKE_PREFIX_PATH=${HOME}/Qt/5.15.2/clang_64/lib/cmake/Qt5 -DCMAKE_OSX_ARCHITECTURES="x86_64"
```
  * To build with Qt5 on Intel:
```sh
cmake -B ./build -DCMAKE_PREFIX_PATH=${HOME}/Qt/5.15.2/clang_64/lib/cmake/Qt5
```
  * To build with Qt6:
```sh
cmake -B ./build -DCMAKE_PREFIX_PATH=${HOME}/Qt/6.2.4/macos/lib/cmake
```
  Also you can use generator for Ninja build system:
```sh
cmake -G Ninja -B ./build -DCMAKE_PREFIX_PATH=${HOME}/Qt/6.2.4/macos/lib/cmake
```
2. Build:
```sh
cmake --build ./build
```

### Xcode
1. Generate project:
  * To build with Qt5 on Apple silicon:
```sh
cmake -G Xcode -B ./build -DCMAKE_PREFIX_PATH=${HOME}/Qt/5.15.2/clang_64/lib/cmake/Qt5 -DCMAKE_OSX_ARCHITECTURES="x86_64"
```
  * To build with Qt5 on Intel:
```sh
cmake -G Xcode -B ./build -DCMAKE_PREFIX_PATH=${HOME}/Qt/5.15.2/clang_64/lib/cmake/Qt5
```
  * To build with Qt6:
```sh
cmake -G Xcode -B ./build -DCMAKE_PREFIX_PATH=${HOME}/Qt/6.2.4/macos/lib/cmake
```
2. Open generated project in Xcode, select target, build.

### QtCreator
Open top level `CMakeList.txt` in QtCreator, select target, build.

NB: If you have an error
```
building for macOS-arm64 but attempting to link with file built for macOS-x86_64
```
as result of building with Qt5 on Apple silicon when you need to run `Build->Run CMake` from menu. It looks like bug in QtCreator that causes variable `CMAKE_OSX_ARCHITECTURES` to be ignored on first CMake run.


## Linux

### Console
```sh
cmake -B ./build
cmake --build ./build
```
You can also use Ninja build system and QtCreator on Linux.

# Tests
The functionality of library is covered by tests. The GoogleTest framework is used. The test coverage for the demo application isn't implemented.

# Examples
Currently there is only one example in the project. This demo application uses Qt framework.

