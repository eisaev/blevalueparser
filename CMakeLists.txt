cmake_minimum_required(VERSION 3.19)

project(blevalueparser VERSION 0.1 LANGUAGES CXX)

option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_TESTS "Build tests" ON)

include(GNUInstallDirs)

set(LIBRARY_SOURCES
    include/blevalueparser.h
)

add_library(${PROJECT_NAME} INTERFACE ${LIBRARY_SOURCES})
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_14)
target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
# -Og           Optimize debugging experience
# -fno-inline   Do not expand any functions inline apart from those marked with the always_inline attribute
set(CMAKE_C_FLAGS_DEBUG   " -Og -fno-inline ${CMAKE_C_FLAGS_DEBUG} ")
set(CMAKE_CXX_FLAGS_DEBUG " -Og -fno-inline ${CMAKE_CXX_FLAGS_DEBUG} ")

if(BUILD_TESTS)
    add_subdirectory("tests")
endif()

if(BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()

install(FILES "include/blevalueparser.h" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
