cmake_minimum_required(VERSION 3.20)
project(BigIntProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(BigIntLib 
  src/BigInt.cpp
  src/Lexer.cpp
  src/Parser.cpp)
target_include_directories(BigIntLib PUBLIC include)

add_executable(BigIntApp src/main.cpp)
target_link_libraries(BigIntApp PRIVATE BigIntLib)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(BigIntTests 
  tests/test_BigInt.cpp 
  tests/test_BigInt_add.cpp 
  tests/test_BigInt_mult.cpp
  tests/test_Lexer.cpp 
  tests/test_Parser.cpp
  tests/test_LargeNumbers.cpp
)
target_link_libraries(BigIntTests PRIVATE BigIntLib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(BigIntTests)

# Benchmarks
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  googlebenchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.10.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googlebenchmark)

add_executable(BigIntBenchmarks
  benchmarks/bench_BigInt.cpp
)
target_link_libraries(BigIntBenchmarks PRIVATE BigIntLib benchmark::benchmark_main)