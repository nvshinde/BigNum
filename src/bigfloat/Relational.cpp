#include "bigfloat/BigFloat.hpp"
#include "bigfloat/Relational.hpp"
#include "bigfloat/Utils.hpp"

namespace bigfloat::comparison {

    void matchPrecision(BigFloat &a, BigFloat &b) {
        std::int64_t p = std::max(a.get_precision(), b.get_precision());

        // precision digits to add
        std::int64_t diffa = p - a.get_precision();
        std::int64_t diffb = p - b.get_precision();

        // one block is 9 digits
        size_t blocksA = diffa / 9;
        size_t blocksB = diffb / 9;

        if (blocksA > 0) {
            a.get_num().insert(a.get_num().begin(), blocksA, 0);    // insert that many 0 blocks
        }

        if (blocksB > 0) {
            b.get_num().insert(b.get_num().begin(), blocksB, 0);
        }

        a.set_precision(p);
        b.set_precision(p);
    }

    bool isequal(const BigFloat& a, const BigFloat &b) {
        BigFloat num1 = a;
        BigFloat num2 = b;

        matchPrecision(num1, num2);

        if (utils::hasZeroMag(num1.get_num()) && utils::hasZeroMag(num2.get_num()))
            // both are zero
            return true;

        // both have same sign and have equal magnitude
        return (num1.isNegative() == num2.isNegative()) &&
                (utils::compAbsVal(num1.get_num(), b.get_num()) == 0);
    }

    bool isnotequal(const BigFloat& a, const BigFloat &b) {
        return !isequal(a, b);
    }

    bool islt(const BigFloat &a, const BigFloat &b) {
        BigFloat num1 = a;
        BigFloat num2 = b;
        
        matchPrecision(num1, num2);

        if (utils::hasZeroMag(num1.get_num()) && utils::hasZeroMag(num2.get_num()))
            return false;

        if (num1.isNegative() != num2.isNegative())
            return num1.isNegative();

        int comp = utils::compAbsVal(num1.get_num(), num2.get_num());
        if (!num1.isNegative()) {
            // both are positive
            return comp == -1;      // a < b;
        } else {
            // both are negative
            return comp == 1;       // a > b;
        }
    }

    bool isleq(const BigFloat &a, const BigFloat &b) {
        return !isgt(a, b);
    }

    bool isgt(const BigFloat &a, const BigFloat &b) {
        return islt(b, a);
    }

    bool isgeq(const BigFloat &a, const BigFloat &b) {
        return !islt(a, b);
    }
} // namespace bigfloat::comparison

