cmake_minimum_required(VERSION 3.20)
project(BigIntProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(BigIntLib src/BigInt.cpp)
target_include_directories(BigIntLib PUBLIC include)

add_executable(BigIntApp src/main.cpp)
target_link_libraries(BigIntApp PRIVATE BigIntLib)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(BigIntTests tests/test_BigInt.cpp tests/test_BigInt_add.cpp tests/test_BigInt_mult.cpp)
target_link_libraries(BigIntTests PRIVATE BigIntLib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(BigIntTests)
