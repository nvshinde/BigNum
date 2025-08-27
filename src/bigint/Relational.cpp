#include "bigint/BigInt.hpp"
#include "bigint/Relational.hpp"
#include "bigint/Utils.hpp"

namespace bigint::comparison {
    bool isequal(const BigInt& a, const BigInt &b) {
        return (a.isNegative() == b.isNegative()) && (a.get_num() == b.get_num());
    }

    bool isnotequal(const BigInt& a, const BigInt &b) {
        return !(isequal(a, b));
    }

    bool islt(const BigInt& a, const BigInt &b) {
        if (a.isNegative() != b.isNegative()) {
            return a.isNegative();
        }

        // same neg_sign, compare magnitude
        if (a.get_size() != b.get_size()) {
            bool smaller = a.get_size() < b.get_size();

            return a.isNegative() ? !smaller : smaller;
        }

        // same len, compare MSB digits
        for (int i=a.get_size()-1; i>=0; --i) {
            if (a.get_num()[i] != b.get_num()[i]) {
                bool smaller = a.get_num()[i] < b.get_num()[i];
                return a.isNegative() ? !smaller : smaller;
            }
        }

        return false;   // both are equal
    }

    bool isleq(const BigInt& a, const BigInt &b) {
        return isequal(a, b) || islt(a, b);
    }

    bool isgt(const BigInt& a, const BigInt &b) {
        return !(isleq(a, b));
    }

    bool isgeq(const BigInt& a, const BigInt &b) {
        return !(islt(a, b));
    }    
} // namespace bigint::comparison 
