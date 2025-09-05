cmake_minimum_required(VERSION 3.14)
project(BigIntLib LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Bigint
# Library target
add_library(bigint
    src/bigint/BigInt.cpp
    src/bigint/Arithmetic.cpp
    src/bigint/Relational.cpp
    src/bigint/Utils.cpp
    src/bigint/Logical.cpp
    src/bigint/Bitwise.cpp
    src/bigint/Algorithms.cpp
)


# headers
target_include_directories(bigint
PUBLIC
${PROJECT_SOURCE_DIR}/include
)

# Bigfloat

add_library(bigfloat
    src/bigfloat/BigFloat.cpp
    src/bigfloat/Arithmetic.cpp
    src/bigfloat/Relational.cpp
    src/bigfloat/Utils.cpp
)

target_include_directories(bigfloat
PUBLIC
${PROJECT_SOURCE_DIR}/include()
)

# use ctest
enable_testing()

add_executable(test_bigint tests/test_bigint.cpp)
target_link_libraries(test_bigint PRIVATE bigint)

add_executable(test_addition tests/test_addition.cpp)
target_link_libraries(test_addition PRIVATE bigint)

add_executable(test_subtraction tests/test_subtraction.cpp)
target_link_libraries(test_subtraction PRIVATE bigint)

add_executable(test_multiplication tests/test_multiplication.cpp)
target_link_libraries(test_multiplication PRIVATE bigint)

add_executable(test_karatsuba tests/test_multiplication_karatsuba.cpp)
target_link_libraries(test_karatsuba PRIVATE bigint)

add_executable(test_division tests/test_division.cpp)
target_link_libraries(test_division PRIVATE bigint)

add_executable(test_modulus tests/test_mod.cpp)
target_link_libraries(test_modulus PRIVATE bigint)

add_test(NAME BigIntBasic COMMAND test_bigint)
add_test(NAME BigIntAddition COMMAND test_addition)
add_test(NAME BigIntSubtraction COMMAND test_subtraction)
add_test(NAME BigIntMultiplication COMMAND test_multiplication)
add_test(NAME BigIntKaratsuba COMMAND test_karatsuba)
add_test(NAME BigIntDivision COMMAND test_division)
add_test(NAME BigIntModulus COMMAND test_modulus)
