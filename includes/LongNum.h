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
        int precision;
        int sign;

        static int FindPrecision(const std::string &str);
        void NoZeroesBegin();
        void NoZeroesEnd();
        int FirstNotZero() const;

        LongNum Sum(const LongNum &other) const;
        LongNum Diff(const LongNum &other) const;
        LongNum Mul(const LongNum &other) const;
        LongNum Div(const LongNum &other) const;

    public:
        LongNum(const char *string);
        explicit LongNum(std::string);
        explicit LongNum(std::vector<int> longnum, int len, int sign);

        void Round(int precision);
        std::string ToString() const;

        LongNum operator+(const LongNum &other) const;
        LongNum operator-(const LongNum &other) const;
        LongNum operator-() const;
        LongNum operator*(const LongNum &other) const;
        LongNum operator/(const LongNum &other) const;

        bool operator==(const LongNum &other) const;
        bool operator!=(const LongNum &other) const;
        bool operator>(const LongNum &other) const;
        bool operator>=(const LongNum &other) const;
        bool operator<(const LongNum &other) const;
        bool operator<=(const LongNum &other) const;
    };

    LongNum PiCalc(int precision);
    LongNum operator "" _LN(const char* str);
}

#endif