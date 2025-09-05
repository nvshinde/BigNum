#include "bigint/BigInt.hpp"
#include "bigint/Arithmetic.hpp"
#include "bigint/Relational.hpp"
#include "bigint/Logical.hpp"
#include "bigint/Utils.hpp"
#include "bigint/Bitwise.hpp"

#include <stdexcept>
#include <algorithm>
namespace bigint {

    BigInt::BigInt() : num(1, 0), neg_sign(false) { 
    }

    BigInt::BigInt(const std::string& s) : neg_sign(false) {
        if (s.empty()) {
            num = {0};
            return;
        }

        size_t start = 0;
        if (s[0] == '-') {
            neg_sign = true;
            start = 1;
        } else if (s[0] == '+') {
            start = 1;
        }

        if (start == s.size()) {
            throw std::invalid_argument("No digits in input\n");
        }

        // validate digits
        for (size_t i=start; i<s.size(); ++i) {
            if (!std::isdigit(s[i]))
                throw std::invalid_argument("Invalid digit in argument");
        }

        // sign before number?
        // const size_t numdigits = s.size() - start;
        // num.resize(numdigits);
        
        // for (size_t i=0; i<numdigits; ++i) {      // scan string from right to left
        //     num[i] = s[s.size()-1-i] - '0';
        // }
        
        num.clear();
        
        // each word in num stores 9 digits in 1e9 base, little endian
        for (size_t i=s.size(); i>= start; ) {
            // parse chunks of 9 digits
            // size_t chunk_start_idx = std::max(start, i - BASE_DIGITS);
            size_t chunk_start_idx = (i >= BASE_DIGITS ? i-BASE_DIGITS : start);    // handle underflow/wrap around
            std::string chunk = s.substr(chunk_start_idx, i-chunk_start_idx);
            
            uint32_t chunk_i = std::stoul(chunk);
            num.push_back(chunk_i);

            if (chunk_start_idx == start) break;            // reached the first valid char. break to avoid underflow of i
            i -= BASE_DIGITS;
        }
        
        if (num.size() == 1 && num[0] == 0) {       // -0 changes to 0
            neg_sign = false;
        }
        utils::trim_leading_zeros(*this);
    }

    BigInt::~BigInt() { // no need
    }

    BigInt::BigInt(const BigInt& other) : num(other.num), neg_sign(other.neg_sign) {
    }

    BigInt& BigInt::operator=(const BigInt& other) {
        if (this != &other) {
            num = other.num;
            neg_sign = other.neg_sign;
        }
        return *this;
    }

    BigInt::BigInt(BigInt&& other) noexcept : num(std::move(other.num)), neg_sign(other.neg_sign) {
        other.neg_sign = false;
    }

    BigInt& BigInt::operator=(BigInt&& other) noexcept {
        if (this != &other) {
            num = std::move(other.num);
            neg_sign = other.neg_sign;

            other.num = {};
            other.neg_sign = false;
        }

        return *this;
    };

    std::string BigInt::toString() const {
        return utils::toString(*this);
    }

    void BigInt::setNegative(bool neg) {
        neg_sign = neg;
    }

    bool BigInt::isNegative() const {
        return neg_sign;
    }

    const std::vector<uint32_t>& BigInt::get_num() const {
        return num;
    }

    std::vector<uint32_t>& BigInt::get_num() {
        return num;
    }

    void BigInt::set_num(const std::vector<uint32_t>& new_num) {
        num = new_num;
    }

    void BigInt::set_num(std::vector<uint32_t>&& new_num) {
        num = std::move(new_num);
    }

    void BigInt::clear_num() {
        num.clear();
    }

    void BigInt::reset_num() {
        num.clear();
        num = {0};
        neg_sign = false;
    }

    size_t BigInt::get_size() const {
        return num.size();
    }

    std::ostream& operator<<(std::ostream& os, const BigInt& n) {
        return os << n.toString();
    }

    // Math operators
    BigInt BigInt::operator+(const BigInt& other) const {   // addition
        return arithmetic::add(*this, other);
    }

    BigInt BigInt::operator-(const BigInt& other) const {   // subtraction
        return arithmetic::subtract(*this, other);
    }

    BigInt BigInt::operator*(const BigInt& other) const {
        return arithmetic::multiply(*this, other);
    }

    BigInt BigInt::operator/(const BigInt& other) const {
        return arithmetic::divide(*this, other);
    }

    BigInt BigInt::operator%(const BigInt& other) const {
        return arithmetic::mod(*this, other);
    }

    BigInt BigInt::operator-() const {      // negate
        BigInt res = *this;
        if (!(res.num.size() == 1 && res.num[0] == 0)) {
            res.neg_sign = !neg_sign;
        }

        return res;
    }

    // Compound operators
    BigInt& BigInt::operator+=(const BigInt& other) {
        return arithmetic::compound_add(*this, other);
    }

    BigInt& BigInt::operator-=(const BigInt& other) {
        return arithmetic::compound_subtract(*this, other);
    }

    BigInt& BigInt::operator*=(const BigInt& other) {
        return arithmetic::compound_multiply(*this, other);
    }

    BigInt& BigInt::operator/=(const BigInt& other) {
        return arithmetic::compound_divide(*this, other);
    }

    BigInt& BigInt::operator%=(const BigInt& other) {
        return arithmetic::compound_mod(*this, other);
    }

    // Relational operators
    bool BigInt::operator==(const BigInt& other) const {
        return comparison::isequal(*this, other);
    }

    bool BigInt::operator!=(const BigInt& other) const {
        return comparison::isnotequal(*this, other);
    }

    bool BigInt::operator<(const BigInt& other) const {
        return comparison::islt(*this, other);
    }

    bool BigInt::operator<=(const BigInt& other) const {
        return comparison::isleq(*this, other);
    }

    bool BigInt::operator>(const BigInt& other) const {
        return comparison::isgt(*this, other);
    }

    bool BigInt::operator>=(const BigInt& other) const {
        return comparison::isgeq(*this, other);
    }

    // Logical operators
    bool BigInt::operator&&(const BigInt& other) const {
        return logical::logicalAnd(*this, other);
    }

    bool BigInt::operator||(const BigInt& other) const {
        return logical::logicalOr(*this, other);
    }

    bool BigInt::operator!() const {
        return logical::logicalNot(*this);
    }

    // Bitwise operators
    BigInt BigInt::operator&(const BigInt& other) const {
        return bitwise::bitwiseAnd(*this, other);
    }

    BigInt BigInt::operator|(const BigInt& other) const {
        return bitwise::bitwiseOr(*this, other);
    }

    BigInt BigInt::operator^(const BigInt& other) const {
        return bitwise::bitwiseXor(*this, other);
    }

    BigInt BigInt::operator~() const {
        return bitwise::bitwiseNot(*this);
    }

    BigInt BigInt::operator<<(size_t shift) const {
        return bitwise::bitwiseLeftShift(*this, shift);
    }

    BigInt BigInt::operator>>(size_t shift) const {
        return bitwise::bitwiseRightShift(*this, shift);
    }

    // TODO: inplace
    // BigInt& BigInt::operator<<=(size_t shift) {

    // }

    // BigInt& BigInt::operator>>=(size_t shift) {

    // }
}

