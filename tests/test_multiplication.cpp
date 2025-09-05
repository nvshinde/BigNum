#include "../include/bigint/BigInt.hpp"
#include <cassert>
#include <iostream>
#include <string>

void test_basic_multiplication() {
    bigint::BigInt a("123");
    bigint::BigInt b("456");
    
    bigint::BigInt c = a * b;
    assert(c.toString() == "56088");
}

void test_multiplication_with_carry() {
    bigint::BigInt a("999999999");
    bigint::BigInt b("999999999");
    
    bigint::BigInt c = a * b;
    assert(c.toString() == "999999998000000001");
}

void test_negative_multiplication() {
    bigint::BigInt a("-123");
    bigint::BigInt b("100");

    bigint::BigInt c = a * b;
    assert(c.toString() == "-12300");
}

void test_multiplication_to_zero() {
    bigint::BigInt a("-100");
    bigint::BigInt b("0");

    bigint::BigInt c = a * b;
    assert(c.toString() == "0");
}

int main() {
    test_basic_multiplication();
    test_multiplication_with_carry();
    test_negative_multiplication();
    test_multiplication_to_zero();

    std::cout << "Multiplication tests passed.\n";
    return 0;
}
