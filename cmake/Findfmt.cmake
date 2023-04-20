include(FetchContent)
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        a33701196adfad74917046096bf5a2aa0ab0bb50 # release-9.1.0
)
FetchContent_MakeAvailable(fmt)

set(fmt_FOUND 1)
