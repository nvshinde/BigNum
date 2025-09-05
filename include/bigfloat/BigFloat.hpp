#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cstdint>

namespace bigfloat {
    static const uint32_t BASE = 1e9;
    // static const int 
    class BigFloat {
        private:
            std::vector<uint32_t> num;  // storage for float
            bool neg_sign;
            std::int64_t precision;
        public:
            // constructors
            BigFloat();
            BigFloat(const std::string &s);

            ~BigFloat();

            // copy
            BigFloat(const BigFloat& other);
            BigFloat& operator=(const BigFloat& other);

            // move
            BigFloat(BigFloat &&other) noexcept;
            BigFloat& operator=(BigFloat &&other) noexcept;

            // Arithmetics operators
            BigFloat operator+(const BigFloat& other) const;
            BigFloat operator-(const BigFloat& other) const;
            BigFloat operator*(const BigFloat& other) const;
            BigFloat operator/(const BigFloat& other) const;
            BigFloat operator-();

            // Relational operators
            bool operator==(const BigFloat& other) const;
            bool operator!=(const BigFloat& other) const;
            bool operator<(const BigFloat& other) const;
            bool operator<=(const BigFloat& other) const;
            bool operator>(const BigFloat& other) const;
            bool operator>=(const BigFloat& other) const;

            // output
            friend std::ostream& operator<<(std::ostream& os, const BigFloat& num);

            std::string toString() const;

            void setNegative(bool neg);
            bool isNegative() const;

            const std::vector<uint32_t> &get_num() const;
            std::vector<uint32_t>& get_num();

            void set_num(const std::vector<uint32_t>& new_num);
            void set_num(std::vector<uint32_t> &&new_num);

            void clear_num();
            void reset_num();

            size_t get_size() const;

            std::int64_t get_precision() const;
            void set_precision(std::int64_t s);
    };

}; // namespace bigfloat

