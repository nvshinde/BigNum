#include "bigfloat/BigFloat.hpp"
#include "bigfloat/Utils.hpp"
#include <vector>

namespace bigfloat::utils {
    
    void trim(std::vector<uint32_t> &a) {
        while (a.size() > 1 && a.back() == 0) {
            a.pop_back();
        }
        if (a.empty()) {
            a.push_back(0);
        }
    }

    std::vector<uint32_t> add_abs(const std::vector<uint32_t> &a, const std::vector<uint32_t> &b) {
        size_t n = std::max(a.size(), b.size());

        std::vector<uint32_t> res;
        res.reserve(n+1);

        std::uint64_t carry = 0;
        for (size_t i=0; i<n; ++i) {
            std::uint64_t sum = carry;
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

    std::vector<uint32_t> sub_abs(const std::vector<uint32_t> &a, const std::vector<uint32_t> &b) {
        // |a| > |b|
        std::vector<uint32_t> res;

        res.reserve(a.size());

        std::int64_t borr = 0;
        for (size_t i=0; i < a.size(); ++i) {
            std::int64_t sub = std::int64_t(a[i]) - (i < b.size() ? std::int64_t(b[i]) : 0) - borr;

            if (sub < 0) {
                sub += BASE;
                borr = 1;
            } else {
                borr = 0; 
            }

            res.push_back(uint32_t(sub));
        }

        trim(res);
        return res;
    }

    std::vector<uint32_t> mul_abs(const std::vector<uint32_t> &a, const std::vector<uint32_t> &b) {
        if (a.size() == 1 && a[0] == 0)
            return std::vector<uint32_t>{0};
        if (b.size() == 1 && b[0] == 0)
            return std::vector<uint32_t>{0};

        std::vector<uint32_t> res(a.size()+b.size(), 0);
        for (size_t i=0; i<a.size(); ++i) {
            std::uint64_t carry = 0;
            for (size_t j=0; j<b.size() || carry; ++j) {
                std::uint64_t sum = res[i+j] + carry;

                if (j < b.size()) {
                    sum += uint64_t(a[i]) * uint64_t(b[j]);
                }

                res[i*j] = uint32_t(sum % BASE);
                carry = sum / BASE;
            }
        }

        trim(res);
        return res;
    }

    int compAbsVal(const std::vector<uint32_t> &a, const std::vector<uint32_t> &b) {
        if (a.size() < b.size()) return -1;
        if (a.size() > b.size()) return 1;

        for (size_t i=a.size(); i > 0; i--) {
            if (a[i] < b[i]) return -1;
            if (a[i] > b[i]) return 1;
        }

        return 0;
    }

    bool hasZeroMag(const std::vector<uint32_t> &a) {
        return (a.size() == 1) && (a[0] == 0);
    }
} // namespace bigfloat::utils
