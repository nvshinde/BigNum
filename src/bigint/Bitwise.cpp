#pragma once

#include "bigint/BigInt.hpp"
#include "bigint/Bitwise.hpp"

namespace bigint::bitwise {
    // covert BigInt to bits, since each chunk of BigInt is not a binary representation of the actual values
    std::vector<uint8_t> BigInt2Bits(const BigInt &x) {
        if (x.isNegative()) {
            throw std::runtime_error("Negative number. Ops not supported.\n");
        }

        BigInt tmp = x;
        std::vector<uint8_t> bits;

        // loop until tmp is 0
        while (!(tmp.get_size() == 1 && tmp.get_num()[0] == 0)) {
            BigInt bit;

            bit = tmp % BigInt("2");
            tmp = tmp / BigInt("2");
            bits.push_back(uint8_t(bit.get_num()[0]));
        }

        if (bits.empty()) bits.push_back(0);
        return bits;
    }

    // covert back
    BigInt Bits2BigInt(const std::vector<uint8_t> &bits) {
        BigInt res("0");

        for (int i=bits.size()-1; i>=0; --i) {
            res = res * BigInt("2");
            if (bits[i] == 1) {
                res = res + BigInt("1");
            }
        }

        return res;
    }

    BigInt bitwiseAnd(const BigInt& a, const BigInt& b) {
        std::vector<uint8_t> bits_a = BigInt2Bits(a);
        std::vector<uint8_t> bits_b = BigInt2Bits(b);

        size_t n = std::max(bits_a.size(), bits_b.size());

        bits_a.resize(n, 0);
        bits_b.resize(n, 0);

        std::vector<uint8_t> c(n);
        for (size_t i=0; i<n; ++i) {
            c[i] = bits_a[i] & bits_b[i];
        }

        return Bits2BigInt(c);
    }

    BigInt bitwiseOr(const BigInt& a, const BigInt& b) {
        std::vector<uint8_t> bits_a = BigInt2Bits(a);
        std::vector<uint8_t> bits_b = BigInt2Bits(b);

        size_t n = std::max(bits_a.size(), bits_b.size());

        bits_a.resize(n, 0);
        bits_b.resize(n, 0);

        std::vector<uint8_t> c(n);
        for (size_t i=0; i<n; ++i) {
            c[i] = bits_a[i] | bits_b[i];
        }

        return Bits2BigInt(c);
    }

    BigInt bitwiseXor(const BigInt& a, const BigInt& b) {
        std::vector<uint8_t> bits_a = BigInt2Bits(a);
        std::vector<uint8_t> bits_b = BigInt2Bits(b);

        size_t n = std::max(bits_a.size(), bits_b.size());

        bits_a.resize(n, 0);
        bits_b.resize(n, 0);

        std::vector<uint8_t> c(n);
        for (size_t i=0; i<n; ++i) {
            c[i] = bits_a[i] ^ bits_b[i];
        }

        return Bits2BigInt(c);
    }

    BigInt bitwiseNot(const BigInt& a) {
        std::vector<uint8_t> bits_a = BigInt2Bits(a);
        size_t n = bits_a.size();
        std::vector<uint8_t> c(n);

        for (size_t i=0; i<n; ++i) {
            // c[i] = ~bits_a[i];       // will flip all bits
            c[i] = bits_a[i] ^ 1;
        }
        
        return Bits2BigInt(c);
    }

    BigInt bitwiseLeftShift(const BigInt& a, const size_t shift) {
        if (shift == 0) 
            return a;

        std::vector<uint8_t> bits_a = BigInt2Bits(a);
        bits_a.insert(bits_a.begin(), shift, 0);        // insert shift * 0 at the start of bits_a

        return Bits2BigInt(bits_a);
    }

    BigInt bitwiseRightShift(const BigInt& a, const size_t shift) {
        if (shift == 0)
            return a;
        
        std::vector<uint8_t> bits_a = BigInt2Bits(a);
        if (shift >= bits_a.size()) return BigInt("0");

        bits_a.erase(bits_a.begin(), bits_a.begin() + shift);       // erase the first shift elements
        return Bits2BigInt(bits_a);
    }

    // TODO:
    // BigInt& bitwiseLeftShiftInPlace(BigInt& a, const size_t shift) {
    // }

    // BigInt& bitwiseRightShiftInPlace(BigInt& a, const size_t shift) {
    // }
} // namespace bigint::bitwise
