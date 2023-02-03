cmake_minimum_required(VERSION 3.19)

project(bvptui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(simpleble REQUIRED)
set_target_properties(simpleble PROPERTIES CXX_CLANG_TIDY "")
set_target_properties(simpleble-c PROPERTIES CXX_CLANG_TIDY "")

set(PROJECT_SOURCES
    main.cpp
    utils.cpp
    utils.hpp
    demoapplication.cpp
    demoapplication.h
    blemanager.cpp
    blemanager.h
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    blevalueparser
    simpleble::simpleble
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    XCODE_SCHEME_ENVIRONMENT "OS_ACTIVITY_MODE=disable"
    MACOSX_BUNDLE_GUI_IDENTIFIER bvpqt.eisaev.dev
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist"
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
# -Og           Optimize debugging experience
# -fno-inline   Do not expand any functions inline apart from those marked with the always_inline attribute
set(CMAKE_C_FLAGS_DEBUG   " -Og -fno-inline ${CMAKE_C_FLAGS_DEBUG} ")
set(CMAKE_CXX_FLAGS_DEBUG " -Og -fno-inline ${CMAKE_CXX_FLAGS_DEBUG} ")

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
