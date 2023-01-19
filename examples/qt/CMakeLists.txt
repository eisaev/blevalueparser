cmake_minimum_required(VERSION 3.14)

# vvv This part must be before project() vvv
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Bluetooth Core Quick QuickControls2 LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Bluetooth Core Quick QuickControls2 LinguistTools)

if(APPLE AND (${QT_VERSION_MAJOR} LESS 6))
    set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE INTERNAL "Workaround for Qt 5.15.2 on Apple Silicon" FORCE)
endif()
# ^^^ This part must be before project() ^^^

project(bvpqt VERSION 0.1 LANGUAGES CXX)

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

target_include_directories(${PROJECT_NAME} PRIVATE "${BVP_INCLUDE_DIR}")

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Bluetooth
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Qml
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::QuickControls2
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

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(${QT_VERSION_MAJOR} EQUAL 6)
    qt_import_qml_plugins(${PROJECT_NAME})
    qt_finalize_executable(${PROJECT_NAME})
endif()
