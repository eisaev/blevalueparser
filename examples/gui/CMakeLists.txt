cmake_minimum_required(VERSION 3.19)

# vvv This part must be before project() vvv
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Bluetooth Core Quick QuickControls2 LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Bluetooth Core Quick QuickControls2 LinguistTools)

if(APPLE AND (${QT_VERSION_MAJOR} LESS 6))
    set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE INTERNAL "Workaround for Qt 5.15.2 on Apple Silicon" FORCE)
endif()
# ^^^ This part must be before project() ^^^

project(bvpqt VERSION 0.1 DESCRIPTION "BLE Value Parser Library GUI Demo Application" LANGUAGES CXX)
set(COMPANY_NAME eisaev)
set(COMPANY_TLD dev)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TS_FILES
    translations/${PROJECT_NAME}_en_US.ts
    translations/${PROJECT_NAME}_fi_FI.ts
)

set(PROJECT_SOURCES
    main.cpp
    blemanager.h
    blemanager.cpp
    bledeviceinfo.h
    bledeviceinfo.cpp
    bleserviceinfo.h
    bleserviceinfo.cpp
    blecharacteristicinfo.h
    blecharacteristicinfo.cpp
    qml.qrc
    ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    qt6_add_translations(${PROJECT_NAME} TS_FILES ${TS_FILES})
else()
    qt5_add_translation(QM_FILES ${TS_FILES})

    add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
        ${QM_FILES}
    )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    blevalueparser
    Qt${QT_VERSION_MAJOR}::Bluetooth
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Qml
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::QuickControls2
)

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

if(APPLE)
    set(BUNDLE_IDENTIFIER "${COMPANY_TLD}.${COMPANY_NAME}.${PROJECT_NAME}")

    set_target_properties(${PROJECT_NAME} PROPERTIES
        XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "${BUNDLE_IDENTIFIER}"
        XCODE_ATTRIBUTE_MARKETING_VERSION "${PROJECT_VERSION}"
        XCODE_ATTRIBUTE_INFOPLIST_KEY_CFBundleDisplayName "${PROJECT_DESCRIPTION}"
        XCODE_ATTRIBUTE_INFOPLIST_KEY_NSBluetoothAlwaysUsageDescription "This application wants to access your Bluetooth adapter"
        XCODE_ATTRIBUTE_INFOPLIST_KEY_LSApplicationCategoryType "public.app-category.utilities"
    )

    if(IOS)
        set(DEPLOYMENT_TARGET "13.0")
        set_target_properties(${PROJECT_NAME} PROPERTIES
            XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET "${DEPLOYMENT_TARGET}"
            MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/Info.ios.plist"
        )
    else()
        set(DEPLOYMENT_TARGET "12.6")
        set_target_properties(${PROJECT_NAME} PROPERTIES
            XCODE_GENERATE_SCHEME ON
            # https://developer.apple.com/forums/thread/696140
            XCODE_SCHEME_ENABLE_GPU_API_VALIDATION "0"
            XCODE_ATTRIBUTE_MACOSX_DEPLOYMENT_TARGET "${DEPLOYMENT_TARGET}"
            MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/Info.macos.plist"
        )
    endif()
endif()

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if(${QT_VERSION_MAJOR} EQUAL 6)
    qt_import_qml_plugins(${PROJECT_NAME})
    qt_finalize_executable(${PROJECT_NAME})
endif()
