cmake_minimum_required(VERSION 3.19)

project(blevalueparser VERSION 0.1 LANGUAGES CXX)

option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_TESTS "Build tests" ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(GNUInstallDirs)

set(LIBRARY_SOURCES
    include/blevalueparser/bvp.h
    # common
    include/blevalueparser/basevalue.h
    include/blevalueparser/blenames.h
    include/blevalueparser/characteristictype.h
    include/blevalueparser/servicetype.h
    # characteristics
    include/blevalueparser/alertcategoryid.h
    include/blevalueparser/alertcategoryidbitmask.h
    include/blevalueparser/alertnotificationcontrolpoint.h
    include/blevalueparser/batterycriticalstatus.h
    include/blevalueparser/batteryenergystatus.h
    include/blevalueparser/batteryhealthinformation.h
    include/blevalueparser/batteryhealthstatus.h
    include/blevalueparser/batteryinformation.h
    include/blevalueparser/batterylevel.h
    include/blevalueparser/batterylevelstatus.h
    include/blevalueparser/batterytimestatus.h
    include/blevalueparser/bodycompositionfeature.h
    include/blevalueparser/bodycompositionmeasurementbase.h
    include/blevalueparser/bodycompositionmeasurement.h
    include/blevalueparser/bodycompositionmeasurementmibfs.h
    include/blevalueparser/bodysensorlocation.h
    include/blevalueparser/currenttime.h
    include/blevalueparser/datetime.h
    include/blevalueparser/dateutc.h
    include/blevalueparser/daydatetime.h
    include/blevalueparser/dayofweek.h
    include/blevalueparser/dstoffset.h
    include/blevalueparser/estimatedservicedate.h
    include/blevalueparser/exacttime256.h
    include/blevalueparser/heartratecontrolpoint.h
    include/blevalueparser/heartratemeasurement.h
    include/blevalueparser/hexstring.h
    include/blevalueparser/localtimeinformation.h
    include/blevalueparser/newalert.h
    include/blevalueparser/pnpid.h
    include/blevalueparser/referencetimeinformation.h
    include/blevalueparser/supportedalertcategorybase.h
    include/blevalueparser/supportednewalertcategory.h
    include/blevalueparser/supportedunreadalertcategory.h
    include/blevalueparser/textstring.h
    include/blevalueparser/timeaccuracy.h
    include/blevalueparser/timesource.h
    include/blevalueparser/timezone.h
    include/blevalueparser/unreadalertstatus.h
    include/blevalueparser/userindex.h
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
