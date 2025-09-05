#include "bigint/BigInt.hpp"
#include "bigint/Algorithms.hpp"
#include "bigint/Arithmetic.hpp"
#include "bigint/Utils.hpp"

#include <algorithm>
#include <vector>

#define u32vec std::vector<uint32_t>

namespace bigint::algorithms {
    void trim (u32vec &a) {
        while (a.size() > 1 && a.back() == 0) {
            a.pop_back();
        }
    }

    u32vec add_vec(const u32vec &a, const u32vec &b) {
        size_t n = std::max(a.size(), b.size());
        u32vec res;
        res.reserve(n+1);

        uint64_t carry = 0;
        for (size_t i=0; i<n; ++i) {
            uint64_t sum = carry;
            if (i < a.size()) sum += a[i];
            if (i < b.size()) sum += b[i];

            res.push_back(uint32_t(sum % BASE));
            carry = sum / BASE;
        }

        if (carry) {
            res.push_back(uint32_t(carry));
        }

        return res;
    }

    u32vec sub_vec(const u32vec &a, const u32vec &b) {
        u32vec res;
        res.reserve(a.size());  // a is larger always because z3 includes z2 and z0

        int64_t borrow = 0;
        for (size_t i=0; i<a.size(); ++i) {
            int64_t sub = int64_t(a[i]) - (i < b.size() ? int64_t(b[i]) : 0);
            sub = sub - borrow;

            if (sub < 0) {
                sub += BASE;
                borrow = 1;
            } else {
                borrow = 0;
            }
            res.push_back(uint32_t(sub));
        }

        trim(res);
        return res;
    }

    void addWithShift(u32vec &res, const u32vec val, size_t shift) {
        if (val.empty()) return;

        if (res.size() < shift + val.size() + 1) {  // +1 for carry
            res.resize(shift + val.size() + 1, 0);
        }

        uint64_t carry = 0;
        size_t i = 0;

        for (; i<val.size() || carry; ++i) {
            uint64_t sum = res[shift + i] + carry;
            if (i < val.size()) {
                sum += val[i];
            }

            res[shift + i] = uint32_t(sum % BASE);
            carry = sum / BASE;
        }

        trim(res);
    }

    u32vec Karatsuba_rec(const u32vec &a, const u32vec &b) {
        size_t n = a.size();
        size_t m = b.size();
        
        // base case
        if (n == 0 || m == 0) {
            return {};      // empty vector
        }

        // if below threshold, use normal as it is faster
        BigInt tmp_a;
        tmp_a.clear_num();
        tmp_a.set_num(a);

        BigInt tmp_b;
        tmp_b.clear_num();
        tmp_b.set_num(b);

        if (std::min(n, m) <= 32) {
            return arithmetic::multiply(tmp_a, tmp_b).get_num();
        }

        // x    = x1*B^m + x0
        // y    = y1*B^m + y0
        // xy   = z2*B^2m + z1*B^m + z0

        // z0  = x0*y0
        // z1  = x1*y0 + x0*y1,
        // z2  = x1*y1

        // z1  = x1*y0 + x0*y1
        //      = (x1 + x0)(y0 + y1) - x1*y1 - x0*y0
        //      = z3 - z2 - z0

        size_t k = std::min(n, m) / 2;

        u32vec a0(a.begin(), a.begin()+k);
        u32vec a1(a.begin()+k, a.end());

        u32vec b0(b.begin(), b.begin()+k);
        u32vec b1(b.begin()+k, b.end());

        trim(a0);
        trim(a1);
        trim(b0);
        trim(b1);

        u32vec z0 = Karatsuba_rec(a0, b0);
        u32vec z2 = Karatsuba_rec(a1, b1);

        u32vec a0plusa1 = add_vec(a0, a1);
        u32vec b0plusb1 = add_vec(b0, b1);

        u32vec z1 = Karatsuba_rec(a0plusa1, b0plusb1);
        z1 = sub_vec(z1, z0);
        z1 = sub_vec(z1, z2);

        u32vec res(n+m, 0);

        addWithShift(res, z0, 0);
        addWithShift(res, z1, k);
        addWithShift(res, z2, 2*k);

        trim(res);
        return res;
    }

    BigInt KaratsubaML(const BigInt &a, const BigInt &b) {
        if (a.get_size() == 0 || b.get_size() == 0) {
            return BigInt("0");
        }

        if (a.get_size() == 1 && a.get_num()[0] == 0) {
            return BigInt("0");
        }

        if (b.get_size() == 1 && a.get_num()[0] == 0) {
            return BigInt("0");
        }

        u32vec tmp_a = a.get_num();
        u32vec tmp_b = b.get_num();

        u32vec res = Karatsuba_rec(tmp_a, tmp_b);

        BigInt result;
        result.clear_num();
        result.set_num(res);

        bool isnegative = (a.isNegative() != b.isNegative());
        result.setNegative(isnegative);

        return result;
    }

} // namespace bigint::algorithms


