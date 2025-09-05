#include "bigint/BigInt.hpp"
#include "bigint/Logical.hpp"

namespace bigint::logical {
    bool logicalAnd(const BigInt& a, const BigInt& b) {
        return (a != BigInt("0") && b != BigInt("0"));
    }

    bool logicalOr(const BigInt& a, const BigInt& b) {
        return (a != BigInt("0") || b != BigInt("0"));
    }

    bool logicalNot(const BigInt &a) {
        return (a == BigInt("0"));
    }
} // namespace bigint::logical
