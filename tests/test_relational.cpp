#include "../include/bigint/BigInt.hpp"
#include <cassert>
#include <iostream>
#include <string>

void test_equality() {
    bigint::BigInt a("123");
    bigint::BigInt b("123");
    
    assert(a == b);
}

void test_inequality() {
    bigint::BigInt a("999");
    bigint::BigInt b("1");
    
    assert(a != b);
}

void test_lt() {
    bigint::BigInt a("-123");
    bigint::BigInt b("100");

    assert(a < b);
}

void test_leq() {
    bigint::BigInt a("-100");
    bigint::BigInt b("+100");
    assert(a <= b);

    bigint::BigInt c("+100");
    assert(b <= c);
}

void test_gt() {
    bigint::BigInt a("-123");
    bigint::BigInt b("100");

    assert(b > a);
}

void test_geq() {
    bigint::BigInt a("110");
    bigint::BigInt b("+100");
    assert(a >= b);

    bigint::BigInt c("+100");
    assert(b >= c);
}
int main() {
    test_equality();
    test_inequality();
    
    test_gt();
    test_geq();

    test_lt();
    test_leq();

    std::cout << "Relational tests passed.\n";
    return 0;
}
