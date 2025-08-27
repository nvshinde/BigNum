#pragma once

#include "bigint/BigInt.hpp"

#include <string>

namespace bigint::utils {
    std::string toString(const BigInt& a);
    void trim_leading_zeros(BigInt& a);
} // namespace bigint::utils
