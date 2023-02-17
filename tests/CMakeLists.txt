cmake_minimum_required(VERSION 3.19)

project(bvptest VERSION 0.1 DESCRIPTION "BLE Value Parser Library tests" LANGUAGES CXX)
set(COMPANY_NAME eisaev)
set(COMPANY_TLD dev)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(gtest REQUIRED)

set(TEST_SOURCES
    tests.cpp
    batteryleveltest.cpp
    bodycompositionfeaturetest.cpp
    bodycompositionmeasurementmibfstest.cpp
    bodycompositionmeasurementtest.cpp
    bodysensorlocationtest.cpp
    currenttimetest.cpp
    datetimetest.cpp
    heartratemeasurementtest.cpp
    hexstringtest.cpp
    internalparsertest.cpp
    localtimeinformationtest.cpp
    pnpidtest.cpp
    textstringtest.cpp
    unsupportedtest.cpp
    userindextest.cpp
)

add_executable(${PROJECT_NAME} ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE
    blevalueparser
    gtest
)

enable_testing()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
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
        set(DEPLOYMENT_TARGET "13.0")
        set_target_properties(${PROJECT_NAME} PROPERTIES
            XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET "${DEPLOYMENT_TARGET}"
            MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/Info.ios.plist"
        )
    else()
        set(DEPLOYMENT_TARGET "12.6")
        set_target_properties(${PROJECT_NAME} PROPERTIES
            XCODE_GENERATE_SCHEME ON
            XCODE_ATTRIBUTE_MACOSX_DEPLOYMENT_TARGET "${DEPLOYMENT_TARGET}"
            MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/Info.macos.plist"
        )
    endif()
endif()

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
