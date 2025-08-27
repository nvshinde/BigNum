#pragma once

#include "bigint/BigInt.hpp"

namespace bigint::arithmetic {
        // core
        BigInt add(const BigInt& a, const BigInt& b);
        BigInt subtract(const BigInt& a, const BigInt& b);
        BigInt multiply(const BigInt& a, const BigInt& b);
        BigInt divide(const BigInt& a, const BigInt& b);
        BigInt mod(const BigInt& a, const BigInt& b);

        BigInt& compound_add(BigInt& a, const BigInt& b);
        BigInt& compound_subtract(BigInt& a, const BigInt& b);
        BigInt& compound_multiply(BigInt& a, const BigInt& b);
        BigInt& compound_divide(BigInt& a, const BigInt& b);
        BigInt& compound_mod(BigInt& a, const BigInt& b);

}   // namespace bigint::arithmetic
