#pragma once

#include "bigint/BigInt.hpp"

namespace bigint::comparison {
    bool isequal(const BigInt& a, const BigInt& b);
    bool isnotequal(const BigInt& a, const BigInt& b);

    bool islt(const BigInt& a, const BigInt& b);
    bool isleq(const BigInt& a, const BigInt& b);

    bool isgt(const BigInt& a, const BigInt& b);
    bool isgeq(const BigInt& a, const BigInt& b);
} // namespace bigint::comparison

