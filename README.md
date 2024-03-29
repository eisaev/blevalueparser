![Building Examples](https://github.com/eisaev/blevalueparser/actions/workflows/examples.yml/badge.svg)
![Testing](https://github.com/eisaev/blevalueparser/actions/workflows/tests.yml/badge.svg)
![Code Coverage](https://img.shields.io/badge/Code%20Coverage-87%25-yellow?style=flat)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# BLE Value Parser
This is a header only library for parsing characteristics of some standardized BLE services. At the moment, parsers are implemented for the following services:
* Device Information Service v1.1 (partially, IEEE 11073-20601 Regulatory Certification Data List has external specification and requires ASN.1 MDER parser)
* Current Time Service v1.1.0 (full)
* Battery Service v1.1 (full)
* Heart Rate Service V10r00 (full)
* Body Composition Service v1.0.0 (full, with additional custom parser for Xiaomi Mi Body Composition Scale 2)
* Alert Notification Service V10r00 (full)

This library is designed for rapid prototyping of BLE applications and isn't optimized for either performance or consumption. You can use the library code as example to implement a parser optimized for a specific platform/case. Also, usually you'll need a parser only for certain services, and not all implemented in the library.

# Usage
You just need to include the header file in your C++ file to use parsers. For example:
```c++
#include "blevalueparser/bvp.h"

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
If you need only a string representation of parsed data you can use the following code example:
```c++
#include "blevalueparser/bvp.h"

[...]

void printParsed(bvp::CharacteristicType chType, const char *data, size_t size)
{
    bvp::BLEValueParser bleValueParser;
    auto result = bleValueParser.make_value(chType, data, size);
    if (!result->isValid())
    {
        std::cout << "Invalid data" << std::endl;
        return;
    }

    std::cout << "Parsed Data: " << result->toString() << std::endl;
}
```


# Build Tests and Example
To build you'll need at least CMake and Qt5 or Qt6.

NB: If CMake doesn't find installed Qt then you can explicitly specify the path like this:
```sh
# for Qt5
cmake -B ./build -DCMAKE_PREFIX_PATH=${HOME}/Qt/5.15.2/clang_64/lib/cmake
```
```sh
# for Qt6
cmake -B ./build -DCMAKE_PREFIX_PATH=${HOME}/Qt/6.2.4/macos/lib/cmake
```

## macOS

### Console
1. Generate project:
```sh
cmake -B ./build
```
or you can use generator for Ninja build system:
```sh
cmake -G Ninja -B ./build
```
2. Build:
```sh
cmake --build ./build
```

### Xcode
1. Generate project:
```sh
cmake -G Xcode -B ./build
```
2. Open generated project in Xcode, select target, build.

### QtCreator
Open top level `CMakeList.txt` in QtCreator, select target, build.

## iOS
NB: Only Qt6 is supported. You must specify path to toolchain file (see example below).

1. Generate project:
```sh
cmake -G Xcode -B build -DCMAKE_TOOLCHAIN_FILE=${HOME}/Qt/6.2.4/ios/lib/cmake/Qt6/qt.toolchain.cmake
```
2. Open generated project in Xcode, select target, build.

## Android

### Console
```sh
cmake -G Ninja -B build -DCMAKE_TOOLCHAIN_FILE=${HOME}/Qt/6.2.4/android_arm64_v8a/lib/cmake/Qt6/qt.toolchain.cmake -DANDROID_SDK_ROOT=${HOME}/Library/Android/sdk -DANDROID_NDK_ROOT=${HOME}/Library/Android/sdk/ndk/22.1.7171670
cmake --build ./build
```
NB: If Java version in your PATH is incompatible with Gradle, then you must specify path to compatible Java. For example:
```sh
JAVA_HOME=/Applications/Android\ Studio.app/Contents/jbr/Contents/Home cmake --build ./build
```

### QtCreator
Open top level `CMakeList.txt` in QtCreator, select target, build.

## Linux

### Console
```sh
cmake -B ./build
cmake --build ./build
```
You can also use Ninja build system and QtCreator on Linux.

# Tests
The functionality of library is covered by tests. The GoogleTest framework is used. At the moment test coverage for the demo application isn't implemented.

You can skip tests build on CMake configuration:
```sh
cmake -B ./build -DBUILD_TESTS=OFF
```

# Examples
There are two examples in the project. First demo is GUI application and it uses [Qt](https://qt.io) framework. Second one is TUI application (only for macOS & Linux) which uses [SimpleBLE](https://github.com/OpenBluetoothToolbox/SimpleBLE) library.

You can skip build of specific example on CMake configuration step:
```sh
cmake -B ./build -DBUILD_GUI_EXAMPLE=OFF
```
or
```sh
cmake -B ./build -DBUILD_TUI_EXAMPLE=OFF
```

Also you can skip examples build at all:
```sh
cmake -B ./build -DBUILD_EXAMPLES=OFF
```
