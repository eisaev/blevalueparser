cmake_minimum_required(VERSION 3.14)

project(blevalueparser VERSION 0.1 LANGUAGES CXX)

option(TESTS_ONLY "Build tests only" OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BVP_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

add_subdirectory("tests")

if(NOT (TESTS_ONLY))
    add_subdirectory("examples")
endif()
