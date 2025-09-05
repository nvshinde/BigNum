#pragma once

#include "bigfloat/BigFloat.hpp"

namespace bigfloat::arithmetic {
    BigFloat add(const BigFloat& a, const BigFloat& b);
    BigFloat subtract(const BigFloat& a, const BigFloat& b);
    BigFloat multiply(const BigFloat& a, const BigFloat& b);
    BigFloat divide(const BigFloat& a, const BigFloat& b);
} // namespace bigfloat::arithmetic
