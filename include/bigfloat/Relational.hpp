#pragma once

#include "bigfloat/BigFloat.hpp"

namespace bigfloat::comparison {
    bool isequal(const BigFloat& a, const BigFloat& b);
    bool isnotequal(const BigFloat& a, const BigFloat& b);

    bool islt(const BigFloat& a, const BigFloat& b);
    bool isleq(const BigFloat& a, const BigFloat& b);

    bool isgt(const BigFloat& a, const BigFloat& b);
    bool isgeq(const BigFloat& a, const BigFloat& b);
} // namespace bigfloat::comparison

