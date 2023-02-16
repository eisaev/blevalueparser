cmake_minimum_required(VERSION 3.19)

option(BUILD_GUI_EXAMPLE "Build GUI example" ON)
option(BUILD_TUI_EXAMPLE "Build TUI example" ON)

if(BUILD_GUI_EXAMPLE)
    add_subdirectory("qt")
endif()

if(BUILD_TUI_EXAMPLE AND NOT IOS)
    add_subdirectory("tui")
endif()
