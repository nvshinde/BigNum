#include "../include/bigint/BigInt.hpp"
#include <cassert>
#include <iostream>
#include <string>

void test_basic_division() {
    bigint::BigInt a("123");
    bigint::BigInt b("456");
    
    bigint::BigInt c = a / b;
    assert(c.toString() == "0");
}

void test_division_with_carry() {
    bigint::BigInt a("999999999");
    bigint::BigInt b("999999999");
    
    bigint::BigInt c = a / b;
    assert(c.toString() == "1");
}

void test_negative_division() {
    bigint::BigInt a("-123");
    bigint::BigInt b("100");

    bigint::BigInt c = a / b;
    assert(c.toString() == "-1");
}

void test_division_by_zero() {
    bigint::BigInt a("-100");
    bigint::BigInt b("0");

    try {
        bigint::BigInt c = a / b;
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Division by zero");
    }
}

void test_division_of_zero() {
    bigint::BigInt a("00");
    bigint::BigInt b("100");

    bigint::BigInt c = a / b;
    assert(c.toString() == "0");
}

int main() {
    test_basic_division();
    test_division_with_carry();
    test_negative_division();
    test_division_by_zero();
    test_division_of_zero();

    std::cout << "Division tests passed.\n";
    return 0;
}
