cmake_minimum_required(VERSION 3.14)
project(BigIntLib LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Library target
add_library(bigint
    src/bigint/BigInt.cpp
    src/bigint/Arithmetic.cpp
    src/bigint/Relational.cpp
    src/bigint/Utils.cpp
)

# headers
target_include_directories(bigint
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# use ctest
enable_testing()

add_executable(test_bigint tests/test_bigint.cpp)
target_link_libraries(test_bigint PRIVATE bigint)

add_executable(test_addition tests/test_addition.cpp)
target_link_libraries(test_addition PRIVATE bigint)

add_test(NAME BigIntBasic COMMAND test_bigint)
add_test(NAME BigIntAddition COMMAND test_addition)
