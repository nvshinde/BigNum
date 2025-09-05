#include "../include/bigint/BigInt.hpp"
#include <cassert>
#include <iostream>
#include <string>

void test_basic_subtraction() {
    bigint::BigInt a("456");
    bigint::BigInt b("123");
    
    bigint::BigInt c = a - b;
    assert(c.toString() == "333");
}

void test_subtraction_with_borrow() {
    bigint::BigInt a("1000");
    bigint::BigInt b("999");
    
    bigint::BigInt c = a - b;
    assert(c.toString() == "1");
}

void test_negative_subtraction1() {
    bigint::BigInt a("-123");
    bigint::BigInt b("100");

    bigint::BigInt c = a - b;
    assert(c.toString() == "-223");
}

void test_negative_subtraction2() {
    bigint::BigInt a("123");
    bigint::BigInt b("-100");

    bigint::BigInt c = a - b;
    assert(c.toString() == "223");
}

void test_negative_subtraction3() {
    bigint::BigInt a("-123");
    bigint::BigInt b("-100");

    bigint::BigInt c = a - b;
    assert(c.toString() == "-23");
}

void test_subtraction_to_zero() {
    bigint::BigInt a("-100");
    bigint::BigInt b("-100");

    bigint::BigInt c = a - b;
    assert(c.toString() == "0");
}

int main() {
    test_basic_subtraction();
    test_subtraction_with_borrow();
    test_negative_subtraction1();
    test_negative_subtraction2();
    test_negative_subtraction3();
    test_subtraction_to_zero();

    std::cout << "Subtraction tests passed.\n";
    return 0;
}
