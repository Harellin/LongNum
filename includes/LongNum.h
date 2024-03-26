#ifndef PROJECT1
#define PROJECT1

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <exception>

namespace MyLongNum{

    class LongNum{
    private:
        std::vector<int> number;
        int exponent;
        int sign;

        void NoZeroes();

        LongNum Sum(const LongNum &other) const;
        LongNum Diff(const LongNum &other) const;
        LongNum Mul(const LongNum &other) const;
        LongNum Div(const LongNum &other) const;

    public:
        explicit LongNum();
        explicit LongNum(std::string);

        void Round(int precision);
        std::string ToString() const;

        LongNum operator+(const LongNum &other) const;
        LongNum operator-(const LongNum &other) const;
        LongNum operator-() const;
        LongNum operator*(const LongNum &other) const;
        LongNum operator/(const LongNum &other) const;
        LongNum operator+=(const LongNum &other);
        LongNum operator-=(const LongNum &other);
        LongNum operator*=(const LongNum &other);
        LongNum operator/=(const LongNum &other);

        bool operator==(const LongNum &other) const;
        bool operator!=(const LongNum &other) const;
        bool operator>(const LongNum &other) const;
        bool operator>=(const LongNum &other) const;
        bool operator<(const LongNum &other) const;
        bool operator<=(const LongNum &other) const;
        friend std::ostream &operator<<(std::ostream &os, const LongNum &other);
    };

    LongNum operator "" _LN(const char* str);
}

#endif