#include "bigint/BigInt.hpp"
#include "bigint/Arithmetic.hpp"
#include "bigint/Utils.hpp"
#include "bigint/Algorithms.hpp"

namespace bigint::arithmetic{
    BigInt abs(const BigInt& a) {
        BigInt val = a;
        val.setNegative(false);
        return val;
    }

    BigInt add(const BigInt& a, const BigInt& b) {
        if (a.isNegative() == b.isNegative()) {
            BigInt result;
            result.clear_num();

            uint64_t carry = 0;     // base is 1e9

            size_t n = std::max(a.get_num().size(), b.get_num().size());

            for (size_t i=0; i<n || carry; ++i) {        // little endian
                uint64_t a_op = (i < a.get_num().size() ? a.get_num()[i] : 0);
                uint64_t b_op = (i < b.get_num().size() ? b.get_num()[i] : 0);

                uint64_t res = a_op + b_op + carry;
                result.get_num().push_back(res % BASE);
                carry = res / BASE;
            }
            result.setNegative(a.isNegative());
            return result;
        } else {
            if (a.isNegative()) {       // Goal: -a+b -> b-|a| ; to get abs(a) do -a
                // return subtract(b, -a);
                return subtract(b, abs(a));
            } else {                    // Goal: a+(-b) -> a-|b| ; to get abs(b) do -b
                // return subtract(a, -b);
                return subtract(a, abs(b));
            }
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
                int a_op = a.get_num()[i];
                int b_op = (i < b.get_size()) ? b.get_num()[i] : 0;

                int diff = a_op-b_op-borrow;

                if (diff < 0) {
                    diff += BASE;
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
            // return a + (-b);
            return a + abs(b);
        } else if (a.isNegative() && !b.isNegative()) {
            // (-a) - b = -(a + b);
            // BigInt res = -(-(a) + b);
            BigInt res= -(abs(a) + b);
            return res;
        } else {
            // (-a) - (-b) = b-a
            // return (-b) - (-(a));
            return abs(b) - abs(a);
        }
    }

    BigInt multiply(const BigInt& a, const BigInt& b) {
        // bigint::BigInt dummy;
        // return dummy;

        // for each chunk of a, multiply each chunk of b, with correct padding
        bigint::BigInt result;
        result.clear_num();
        result.get_num().assign(a.get_size() + b.get_size(), 0);

        for (size_t i=0; i<a.get_size(); ++i) {
            uint64_t carry = 0;
            for (size_t j=0; j<b.get_size() || carry ; ++j) {
                uint64_t res_chunk = result.get_num()[i+j] + uint64_t(a.get_num()[i]) * (j < b.get_size() ? b.get_num()[j] : 0) + carry;

                result.get_num()[i+j] = res_chunk % BASE;
                carry = res_chunk / BASE;
            }
        }

        if (a.isNegative() != b.isNegative()) {  // if different signs
            result.setNegative(true);
        } else {
            result.setNegative(false);
        }
        utils::trim_leading_zeros(result);
        return result;
    }

    BigInt multiply_karatsuba(const BigInt& a, const BigInt& b) {
        return algorithms::KaratsubaML(a, b);
    }

    // TODO: Fix repeated divison
    BigInt divide(const BigInt& a, const BigInt& b) {

        if (b.get_size() == 1 && b.get_num()[0] == 0) {
            throw std::runtime_error("Division by zero");
        }

        // Repeated subtraction
        BigInt dividend;
        dividend.clear_num();
        dividend = abs(a);
        
        // if (dividend < BigInt("0")) dividend = -dividend;

        BigInt divisor;
        divisor.clear_num();
        divisor = abs(b);

        if (divisor < BigInt("0")) divisor = -divisor;

        BigInt quotient("0");

        while (dividend >= divisor) {
            dividend = (dividend - divisor);
            quotient = quotient + BigInt("1");
        }

        quotient.setNegative(a.isNegative() ^ b.isNegative());      // only one has to be negative
        utils::trim_leading_zeros(quotient);
        return quotient;
    }

    // TODO: Fix repeated subraction
    BigInt mod(const BigInt& a, const BigInt& b) {
        if (b.get_size() == 1 && b.get_num()[0] == 0) {
            throw std::runtime_error("Mod by zero");
        }

        // Repeated subtraction
        BigInt dividend;
        dividend.clear_num();
        dividend = abs(a);

        BigInt divisor;
        divisor.clear_num();
        divisor = abs(b);

        BigInt quotient("0");

        while (dividend >= divisor) {
            dividend = (dividend - divisor);
            quotient = quotient + BigInt("1");
        }

        utils::trim_leading_zeros(dividend);


        if (a.isNegative() && !b.isNegative()) {
            dividend = divisor - dividend;
        } else if (!a.isNegative() && b.isNegative()) {
            dividend = divisor - dividend;
            dividend.setNegative(true);
        } else if (a.isNegative() && b.isNegative()) {
            dividend.setNegative(true);
        }

        return dividend;
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
