cmake_minimum_required(VERSION 3.19)

project(bvptui VERSION 0.1 DESCRIPTION "BLE Value Parser Library TUI Demo Application" LANGUAGES CXX)
set(COMPANY_NAME eisaev)
set(COMPANY_TLD dev)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(simpleble REQUIRED)
set_target_properties(simpleble PROPERTIES CXX_CLANG_TIDY "")
set_target_properties(simpleble-c PROPERTIES CXX_CLANG_TIDY "")

set(PROJECT_SOURCES
    main.cpp
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
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

if (APPLE)
    set(BUNDLE_IDENTIFIER "${COMPANY_TLD}.${COMPANY_NAME}.${PROJECT_NAME}")

    set_target_properties(${PROJECT_NAME} PROPERTIES
        XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "${BUNDLE_IDENTIFIER}"
        XCODE_ATTRIBUTE_MARKETING_VERSION "${PROJECT_VERSION}"
        XCODE_ATTRIBUTE_INFOPLIST_KEY_CFBundleDisplayName "${PROJECT_DESCRIPTION}"
        XCODE_ATTRIBUTE_INFOPLIST_KEY_NSBluetoothAlwaysUsageDescription "This application wants to access your Bluetooth adapter"
        XCODE_ATTRIBUTE_INFOPLIST_KEY_LSApplicationCategoryType "public.app-category.utilities"
    )

    if (IOS)
        message(FATAL_ERROR "TUI Demo Application doesn't suported on iOS.")
    else()
        set(DEPLOYMENT_TARGET "12.6")
        set_target_properties(${PROJECT_NAME} PROPERTIES
            XCODE_GENERATE_SCHEME ON
            XCODE_ATTRIBUTE_MACOSX_DEPLOYMENT_TARGET "${DEPLOYMENT_TARGET}"
            MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/Info.macos.plist"
        )
    endif()
endif()

# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
# -Og           Optimize debugging experience
# -fno-inline   Do not expand any functions inline apart from those marked with the always_inline attribute
set(CMAKE_C_FLAGS_DEBUG   " -Og -fno-inline ${CMAKE_C_FLAGS_DEBUG} ")
set(CMAKE_CXX_FLAGS_DEBUG " -Og -fno-inline ${CMAKE_CXX_FLAGS_DEBUG} ")

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
