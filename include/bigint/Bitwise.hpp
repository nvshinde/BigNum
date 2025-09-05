#pragma once

#include "bigint/BigInt.hpp"

namespace bigint::bitwise {
    BigInt bitwiseAnd(const BigInt& a, const BigInt& b);
    BigInt bitwiseOr(const BigInt& a, const BigInt& b);
    BigInt bitwiseXor(const BigInt& a, const BigInt& b);
    BigInt bitwiseNot(const BigInt& a);

    // value returning
    BigInt bitwiseLeftShift(const BigInt& a, const size_t shift);
    BigInt bitwiseRightShift(const BigInt& a, const size_t shift);

    // in place
    BigInt& bitwiseLeftShiftInPlace(BigInt &a, const size_t shift);
    BigInt& bitwiseRightShiftInPlace(BigInt &a, const size_t shift);
} // namespace bigint::bitwise

