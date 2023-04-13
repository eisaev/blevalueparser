set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable Google Benchmark tests" FORCE)
set(BENCHMARK_ENABLE_WERROR OFF CACHE BOOL "Disable Google Benchmark warnings" FORCE)

include(FetchContent)
FetchContent_Declare(
    gbenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG        d572f4777349d43653b21d6c2fc63020ab326db2 # v1.7.1
)
FetchContent_MakeAvailable(gbenchmark)

set(gbenchmark_FOUND 1)
