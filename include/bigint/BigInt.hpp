#pragma once

#include <vector>
#include <string>
#include <iostream>

namespace bigint {
    
    static const uint32_t BASE = 1e9;
    static const int BASE_DIGITS = 9;
    class BigInt {
        private:
            std::vector<uint32_t> num;      // little endian
            bool neg_sign;

        public:
            // constructors
            BigInt();       
            BigInt(const std::string& s);

            // Destructors
            ~BigInt();
            
            // Copy
            BigInt(const BigInt& other);
            
            // Copy assignment
            BigInt& operator=(const BigInt& other);
            
            // Move 
            BigInt(BigInt&& other) noexcept;
            
            // Move assingment
            BigInt& operator=(BigInt&& other) noexcept;
            
            // Math operators
            BigInt operator+(const BigInt& other) const;
            BigInt operator-(const BigInt& other) const;    // subtract
            BigInt operator*(const BigInt& other) const;
            BigInt operator/(const BigInt& other) const;
            BigInt operator%(const BigInt& other) const;
            BigInt operator-() const;    // negate
            
            BigInt& operator+=(const BigInt& other);
            // TODO: Compound operators
            BigInt& operator-=(const BigInt& other);
            BigInt& operator*=(const BigInt& other);
            BigInt& operator/=(const BigInt& other);
            BigInt& operator%=(const BigInt& other);
            
            // Relational operators
            bool operator==(const BigInt& other) const;
            bool operator!=(const BigInt& other) const;
            bool operator<(const BigInt& other) const;
            bool operator<=(const BigInt& other) const;
            bool operator>(const BigInt& other) const;
            bool operator>=(const BigInt& other) const;
            
            // Logical operators: &&, ||, !
            bool operator&&(const BigInt& other) const;
            bool operator||(const BigInt& other) const;
            bool operator!() const;

            // Bitwise operators: &, |, ^, ~, <<, >>
            BigInt operator&(const BigInt& other) const;
            BigInt operator|(const BigInt& other) const;
            BigInt operator^(const BigInt& other) const;
            BigInt operator~() const;

            // value returning
            BigInt operator<<(size_t shift) const;
            BigInt operator>>(size_t shift) const;

            // TODO: in place
            BigInt& operator<<=(size_t shift);
            BigInt& operator>>=(size_t shift);


            // io
            friend std::ostream& operator<<(std::ostream& os, const BigInt& num);
            // TODO: >> input operator
            
            std::string toString() const;
            // void trim_leading_zeros();
            
            // setters/getters
            
            // sign
            void setNegative(bool neg);
            bool isNegative() const;
            
            // num
            const std::vector<uint32_t>& get_num() const;    // read only
            std::vector<uint32_t>& get_num();                // mutable
            
            void set_num(const std::vector<uint32_t>& new_num);
            void set_num(std::vector<uint32_t>&& new_num);

            void clear_num();       // clear memory
            void reset_num();       // reset to 0

            size_t get_size() const;
    };
};  // namespace bigint
