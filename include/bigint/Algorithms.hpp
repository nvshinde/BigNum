#pragma once

#include "bigint/BigInt.hpp"

namespace bigint::algorithms {
    // Optimisation algorithms
    BigInt KaratsubaML(const BigInt& a, const BigInt& b);
    BigInt FFTML(const BigInt& a, const BigInt& b);
    
}   // namespace bigint::algorithms
