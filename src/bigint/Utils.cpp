#include "bigint/BigInt.hpp"
#include "bigint/Utils.hpp"
#include <string>

namespace bigint::utils {
    std::string toString(const BigInt& a) {
        std::string s = "";
        if (a.isNegative() && !(a.get_size() == 1 && a.get_num()[0] == 0)) {
            s.push_back('-');
        }

        // for (auto it = a.get_num().rbegin(); it != a.get_num().rend(); ++it) {
        //     s.push_back('0'+*it);
        // }

        // for (auto it = a.get_num().rbegin(); it != a.get_num().rend(); ++it) {
        //     s += std::to_string(*it);
        // }

        // uint32_t rep
        s += std::to_string(a.get_num().back());    // Most significant chunk doesn't need padding
        char buf[16];               // 10 digits in uint32_t, last char is null char
        for (long long i=((long long)a.get_size()-2); i>=0; --i) {
            std::snprintf(buf, sizeof(buf), "%09u", a.get_num()[i]);        // all other chunks occupy 9 digits
            s += buf;
        }
        return s;
    }

    void trim_leading_zeros(BigInt& a) {
        while (a.get_size() > 1 && a.get_num().back() == 0) {
            a.get_num().pop_back();
        }

        if (a.get_num().size() == 1 && a.get_num()[0] == 0) {
            a.setNegative(false);
        }
    }
} // namespace bigint::utils


