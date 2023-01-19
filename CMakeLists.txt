cmake_minimum_required(VERSION 3.14)

project(blevalueparser VERSION 0.1 LANGUAGES CXX)

option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_TESTS "Build tests" ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BVP_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

if(BUILD_TESTS)
    add_subdirectory("tests")
endif()

if(BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()
