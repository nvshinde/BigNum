#include "../include/bigint/BigInt.hpp"
#include <cassert>
#include <iostream>

int main() {
    using namespace bigint;

    BigInt a("123");
    BigInt b("456");

    BigInt c = a + b;

    std::cout << a.toString() << " + " << b.toString() << " = " << c.toString() << "\n";

    assert(c.toString() == "579");
    return 0;
}
