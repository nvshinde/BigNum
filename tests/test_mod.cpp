#include "../include/bigint/BigInt.hpp"
#include <cassert>
#include <iostream>
#include <string>

void test_basic_mod() {
    bigint::BigInt a("123");
    bigint::BigInt b("456");
    
    bigint::BigInt c = a % b;
    assert(c.toString() == "123");
}

void test_zero_mod() {
    bigint::BigInt a("999999999");
    bigint::BigInt b("999999999");
    
    bigint::BigInt c = a % b;
    assert(c.toString() == "0");
}

void test_negative_mod1() {
    bigint::BigInt a("-123");
    bigint::BigInt b("100");

    bigint::BigInt c = a % b;
    assert(c.toString() == "77");
}

void test_negative_mod2() {
    bigint::BigInt a("123");
    bigint::BigInt b("-100");

    bigint::BigInt c = a % b;
    assert(c.toString() == "-77");
}

void test_negative_mod3() {
    bigint::BigInt a("-123");
    bigint::BigInt b("-100");

    bigint::BigInt c = a % b;
    assert(c.toString() == "-23");
}

void test_mod_by_zero() {
    bigint::BigInt a("-100");
    bigint::BigInt b("0");

    try {
        bigint::BigInt c = a % b;
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Mod by zero");
    }
}

int main() {
    test_basic_mod();
    test_zero_mod();
    test_negative_mod1();
    test_negative_mod2();
    test_negative_mod3();
    test_mod_by_zero();

    std::cout << "Modulus tests passed.\n";
    return 0;
}
