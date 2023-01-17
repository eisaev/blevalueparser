cmake_minimum_required(VERSION 3.14)

project(blevalueparser VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BVP_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

add_subdirectory("tests")
add_subdirectory("examples")

