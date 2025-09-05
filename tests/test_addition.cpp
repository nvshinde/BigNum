#include "../include/bigint/BigInt.hpp"
#include <cassert>
#include <iostream>
#include <string>

void test_basic_addition() {
    bigint::BigInt a("123");
    bigint::BigInt b("456");
    
    bigint::BigInt c = a + b;
    assert(c.toString() == "579");
}

void test_addition_with_carry() {
    bigint::BigInt a("999");
    bigint::BigInt b("1");
    
    bigint::BigInt c = a + b;
    assert(c.toString() == "1000");
}

void test_negative_addition() {
    bigint::BigInt a("-123456789");
    bigint::BigInt b("100");

    bigint::BigInt c = a + b;
    assert(c.toString() == "-123456689");
}

void test_addition_to_zero() {
    bigint::BigInt a("-100");
    bigint::BigInt b("+100");

    bigint::BigInt c = a + b;
    assert(c.toString() == "0");
}

int main() {
    test_basic_addition();
    test_addition_with_carry();
    test_negative_addition();
    test_addition_to_zero();

    std::cout << "Addition tests passed.\n";
    return 0;
}
