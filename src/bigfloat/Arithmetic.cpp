#include "bigfloat/BigFloat.hpp"
#include "bigfloat/Arithmetic.hpp"
#include "bigfloat/Utils.hpp"

namespace bigfloat::arithmetic {
    BigFloat abs(const BigFloat& a) {
        BigFloat val = a;
        val.setNegative(false);
        return val;
    }

    void matchPrecision(BigFloat& a, BigFloat& b) {
        // the decimal points should align
        std::int64_t p = std::max(a.get_precision(), b.get_precision());
    }

    BigFloat add(const BigFloat& a, const BigFloat& b) {
        // match precision
        BigFloat num1 = a;
        BigFloat num2 = b;
        matchPrecision(num1, num2);

        BigFloat res;
        res.set_precision(num1.get_precision());

        if (num1.isNegative() == b.isNegative()) {
            // same sign, so only simple addition
            res.set_num(utils::add_abs(num1.get_num(), num2.get_num()));
            res.setNegative(num1.isNegative());
        } else {
            int comp = utils::compAbsVal(num1.get_num(), num2.get_num());
            if (comp == 0) {        // both are equal
                res.set_num({0});
                res.setNegative(true);
                res.set_precision(0);
            } else if (comp > 0) {
                res.set_num(utils::sub_abs(num1.get_num(), num2.get_num()));
                res.setNegative(num1.isNegative());
            } else {
                res.set_num(utils::sub_abs(num2.get_num(), num1.get_num()));
                res.setNegative(num2.isNegative());
            }
        }

        if (utils::hasZeroMag(res.get_num())) {
            res.setNegative(false);
        }
        return res;
    }

    BigFloat subtract(const BigFloat& a, const BigFloat& b) {
        BigFloat tmp = b;
        tmp.setNegative(!tmp.isNegative());
        return a + tmp;
    }

    BigFloat multiply(const BigFloat& a, const BigFloat& b) {
        BigFloat res;
        res.set_num(utils::mul_abs(a.get_num(), b.get_num()));
        res.setNegative(a.isNegative() != b.isNegative());

        res.set_precision(a.get_precision() + b.get_precision());

        if (utils::hasZeroMag(res.get_num())) {
            res.setNegative(false);
            res.set_precision(0);
        }

        return res;
    }

    BigFloat divide(const BigFloat& a, const BigFloat& b) {
        // TODO:
    }
} // namespace bigfloat::arithmetic

