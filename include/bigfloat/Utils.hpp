#pragma once

#include "bigfloat/BigFloat.hpp"

#include <string>

namespace bigfloat::utils {
    std::string toString(const BigFloat& a);
    std::vector<uint32_t> add_abs(const std::vector<uint32_t>& a, const std::vector<uint32_t> &b);
    std::vector<uint32_t> sub_abs(const std::vector<uint32_t>& a, const std::vector<uint32_t> &b);
    std::vector<uint32_t> mul_abs(const std::vector<uint32_t>& a, const std::vector<uint32_t> &b);
    int compAbsVal(const std::vector<uint32_t>& a, const std::vector<uint32_t> &b);
    bool hasZeroMag(const std::vector<uint32_t>& a);
    void trim(std::vector<uint32_t> &a);
} // namespace bigfloat::utils

