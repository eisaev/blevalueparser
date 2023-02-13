include(FetchContent)
FetchContent_Declare(
    simpleble
    GIT_REPOSITORY https://github.com/OpenBluetoothToolbox/SimpleBLE.git
    GIT_TAG main #389b820a684bcf7d4e2009453320928e7883322b
    GIT_SHALLOW ON
)
#FetchContent_MakeAvailable(simpleble)

# Note that here we manually do what FetchContent_MakeAvailable() would do,
# except to ensure that the dependency can also get what it needs, we add
# custom logic between the FetchContent_Populate() and add_subdirectory()
# calls.
FetchContent_GetProperties(simpleble)
if(NOT simpleble_POPULATED)
    FetchContent_Populate(simpleble)
    list(APPEND CMAKE_MODULE_PATH "${simpleble_SOURCE_DIR}/cmake/find")
    add_subdirectory("${simpleble_SOURCE_DIR}/simpleble" "${simpleble_BINARY_DIR}")
endif()

set(simpleble_FOUND 1)
