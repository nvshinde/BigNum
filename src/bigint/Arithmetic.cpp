#include "bigint/BigInt.hpp"
#include "bigint/Arithmetic.hpp"
#include "bigint/Utils.hpp"

namespace bigint::arithmetic{
    BigInt add(const BigInt& a, const BigInt& b) {
        if (a.isNegative() == b.isNegative()) {     // same sign
            BigInt result;
            result.clear_num();

            uint32_t carry = 0;
            size_t n = std::max(a.get_num().size(), b.get_num().size());

            for (size_t i=0; i<n || carry; ++i) {
                uint32_t da = (i < a.get_num().size() ? a.get_num()[i] : 0);
                uint32_t db = (i < b.get_num().size() ? b.get_num()[i] : 0);
                uint32_t sum = da + db + carry;

                result.get_num().push_back(sum % 10);
                carry = sum / 10;
            }

            result.setNegative(a.isNegative());
            utils::trim_leading_zeros(result);
            return result;
        } else {
            // x - (-y) = x+y;      x sign is irrelevant
            // if y is -ve, x - (-(-y)) = x-(+y)
            // if y is +ve, x - (-(y)) = x+(+y)
            return subtract(a, -b);
        }
    }

    BigInt subtract(const BigInt& a, const BigInt& b) {
        if (!a.isNegative() && !b.isNegative()) {
            if (a < b) {
                // x-y = -y+x = -(y-x)
                // BigInt res = -(b - (a));
                BigInt res = -(subtract(b, a));
                return res;
            }

            BigInt res;
            res.clear_num();
            int borrow = 0;

            for (size_t i=0; i<a.get_size(); ++i) {
                int da = a.get_num()[i];
                int db = (i < b.get_size()) ? b.get_num()[i] : 0;

                int diff = da-db-borrow;

                if (diff < 0) {
                    diff += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }

                res.get_num().push_back(diff);
            }

            res.setNegative(false);
            utils::trim_leading_zeros(res);
            return res;
        } else if (!a.isNegative() && b.isNegative()) {
            return a + (-b);
        } else if (a.isNegative() && !b.isNegative()) {
            // (-a) - b = -(a + b);
            BigInt res = -(-(a) + b);
            return res;
        } else {
            // (-a) - (-b) = b-a
            return -(b) - (-(a));
        }
    }

    // TODO:
    BigInt multiply(const BigInt& a, const BigInt& b) {
        bigint::BigInt dummy;
        return dummy;
    }

    // TODO:
    BigInt divide(const BigInt& a, const BigInt& b) {
        bigint::BigInt dummy;
        return dummy;
    }

    // TODO:
    BigInt mod(const BigInt& a, const BigInt& b) {
        bigint::BigInt dummy;
        return dummy;
    }

    BigInt& compound_add(BigInt& a, const BigInt& b) {
        if (a.isNegative() == b.isNegative()) {     // same sign
            uint32_t carry = 0;
            size_t n = std::max(a.get_num().size(), b.get_num().size());

            for (size_t i=0; i<n || carry; ++i) {
                uint32_t da = (i < a.get_num().size() ? a.get_num()[i] : 0);
                uint32_t db = (i < b.get_num().size() ? b.get_num()[i] : 0);
                uint32_t sum = da + db + carry;

                if (i <a.get_num().size())
                    a.get_num()[i] = sum % 10;
                else
                    a.get_num().push_back(sum%10);
                carry = sum / 10;
            }

            a.setNegative(a.isNegative());
            utils::trim_leading_zeros(a);
            return a;
        } else {
            // x - (-y) = x+y;      x sign is irrelevant
            // if y is -ve, x - (-(-y)) = x-(+y)
            // if y is +ve, x - (-(y)) = x+(+y)
            a = subtract(a, -b);
            return a;
        }
    }

    // TODO:
    BigInt& compound_subtract(BigInt& a, const BigInt& b) {
        return a;
    }

    // TODO:
    BigInt& compound_multiply(BigInt& a, const BigInt& b) {
        return a;
    }

    // TODO:
    BigInt& compound_divide(BigInt& a, const BigInt& b) {
        return a;
    }

    // TODO:
    BigInt& compound_mod(BigInt& a, const BigInt& b) {
        return a;
    }
} // namespace arithmetic
