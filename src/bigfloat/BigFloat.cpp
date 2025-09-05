#include "bigfloat/BigFloat.hpp"
#include "bigfloat/Arithmetic.hpp"
#include "bigfloat/Relational.hpp"
#include "bigfloat/Utils.hpp"

#include <stdexcept>
#include <algorithm>

namespace bigfloat {
    BigFloat::BigFloat() : num(1, 0), neg_sign(false) {
    }

    BigFloat::BigFloat(const std::string& s) : neg_sign(false) {
        if (s.empty()) {
            num = {0};
            neg_sign = false;
            precision = 0;
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
            if (!(std::isdigit(s[i]) || s[i] == '.'))
                throw std::invalid_argument("Invalid digit in argument");
        }

        // find the decimal point position
        size_t decimalPointPos = s.find('.', start);
        
        std::string integerPart, fractionPart;

        if (decimalPointPos == std::string::npos) {
            // no fraction in this float
            integerPart = s.substr(start);
            fractionPart.clear();           
        } else {
            integerPart = s.substr(start, decimalPointPos-start);
            fractionPart = s.substr(decimalPointPos+1);
        }

        // incase the number has leading and trailing zeros
        size_t intStart = 0;
        while (intStart < integerPart.size() && integerPart[intStart] == '0') {
            intStart++;
        }

        // update with removed leading zeros
        if (intStart == integerPart.size()) {
            integerPart = "0";
        } else {
            integerPart.substr(intStart);
        }

        // remove trailing zeros
        while (fractionPart.size() != 0 && fractionPart.back() == '0') {
            fractionPart.pop_back();
        }

        // number may become zero
        if (integerPart == "0" && fractionPart.size() == 0) {
            num = {0};
            neg_sign = false;
            precision = 0;
            return;
        }

        // TODO:
    }

    BigFloat::~BigFloat() {
    }

    BigFloat::BigFloat(const BigFloat& other) : num(other.num), neg_sign(other.neg_sign) {
    }

    BigFloat& BigFloat::operator=(const BigFloat & other) {
        if (this != &other) {
            num = other.num;
            neg_sign = other.neg_sign;
            precision = other.precision;
        }
        return *this;
    }

    BigFloat::BigFloat(BigFloat&& other) noexcept : num(std::move(other.num)), neg_sign(other.neg_sign), precision(other.precision) {
        other.neg_sign = false;
        other.precision = 0;
    }

    BigFloat& BigFloat::operator=(BigFloat&& other) noexcept {
        if (this != &other) {
            num = std::move(other.num);
            neg_sign = other.neg_sign;
            precision = other.precision;

            other.neg_sign = false;
            other.precision = 0;
        }

        return *this;
    }

    std::string BigFloat::toString() const {
        return utils::toString(*this);
    }

    void BigFloat::setNegative(bool neg) {
        neg_sign = neg;
    }

    bool BigFloat::isNegative() const {
        return neg_sign;
    }

    const std::vector<uint32_t>& BigFloat::get_num() const {
        return num;
    }

    std::vector<uint32_t>& BigFloat::get_num() {
        return num;
    }

    void BigFloat::set_num(const std::vector<uint32_t>& new_num) {
        num = new_num;
    }

    void BigFloat::set_num(std::vector<uint32_t>&& new_num) {
        num = std::move(new_num);
    }

    void BigFloat::clear_num() {
        num.clear();
    }

    void BigFloat::reset_num() {
        num.clear();
        num = {0};
        neg_sign = false;
        precision = 0;
    }

    size_t BigFloat::get_size() const {
        return num.size();
    }

    std::int64_t BigFloat::get_precision() const {
        return precision;
    }

    std::ostream& operator<<(std::ostream& os, const BigFloat& n) {
        return os << n.toString();
    }

    // Math ops
    BigFloat BigFloat::operator+(const BigFloat& other) const {
        return arithmetic::add(*this, other);
    }

    BigFloat BigFloat::operator-(const BigFloat& other) const {
        return arithmetic::subtract(*this, other);
    }

    BigFloat BigFloat::operator*(const BigFloat& other) const {
        return arithmetic::multiply(*this, other);
    }

    BigFloat BigFloat::operator/(const BigFloat& other) const {
        return arithmetic::divide(*this, other);
    }

    BigFloat BigFloat::operator-() {
        BigFloat res = *this;
        if (!(res.num.size() == 1 && res.num[0] == 0)) {
            res.neg_sign = !neg_sign;
        }

        return res;
    }

    bool BigFloat::operator==(const BigFloat &other) const {
        return comparison::isequal(*this, other);
    }

    bool BigFloat::operator!=(const BigFloat &other) const {
        return comparison::isnotequal(*this, other);
    }

    bool BigFloat::operator<(const BigFloat &other) const {
        return comparison::islt(*this, other);
    }

    bool BigFloat::operator<=(const BigFloat &other) const {
        return comparison::isleq(*this, other);
    }

    bool BigFloat::operator>(const BigFloat &other) const {
        return comparison::isgt(*this, other);
    }

    bool BigFloat::operator>=(const BigFloat &other) const {
        return comparison::isgeq(*this, other);
    }

} // namespace bigfloat

