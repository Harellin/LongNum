#ifndef PROJECT1_LONGNUM_H
#define PROJECT1_LONGNUM_Hiv

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <exception>

namespace LongNum{

    class LongNum{
    private:
        std::vector<int> number;
        int precision;
        int sign;

        static int FindPrecision(const std::string &str);
        void NoZeroesBegin();
        void NoZeroesEnd();
        int FirstNotZero() const;
        std::string ToString() const;

        LongNum Sum(const LongNum &other) const;
        LongNum Diff(const LongNum &other) const;
        LongNum Mul(const LongNum &other) const;
        LongNum Div(const LongNum &other) const;

    public:
        LongNum();
        explicit LongNum(std::string number);
        explicit LongNum(std::vector<int> longnum, int len, int sign);

        void Round(int precision);

        LongNum operator+(const LongNum &other) const;
        LongNum operator-(const LongNum &other) const;
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

#endif //PROJECT1_LONGNUM_H