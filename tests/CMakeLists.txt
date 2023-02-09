cmake_minimum_required(VERSION 3.19)

project(bvptest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        58d77fa8070e8cec2dc1ed015d66b454c8d78850 # release-1.12.1
)
FetchContent_MakeAvailable(gtest)

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

install(TARGETS ${PROJECT_NAME})
