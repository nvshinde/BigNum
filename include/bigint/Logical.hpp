#pragma once

#include "bigint/BigInt.hpp"

namespace bigint::logical {
    bool logicalAnd(const BigInt& a, const BigInt& b);
    bool logicalOr(const BigInt& a, const BigInt& b);
    bool logicalNot(const BigInt& a);

} // namespace bigint::logical

