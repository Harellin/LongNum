#include "../includes/LongNum.h"
#include <vector>
#include <string>

const int divDigits = 100;

namespace MyLongNum {
    LongNum::LongNum() {
        sign = 1;
        number = std::vector<int>(1, 0);
        exponent = 1;
    }

    LongNum::LongNum(std::string number) {
        int index = (number[0] == '-') ? 1 : 0;
        sign = (number[0] == '-') ? -1 : 1;
        exponent = number.length() - index;

        while (index < number.length()) {
            if (number[index] == '.') {
                exponent = sign == 1 ? index : index - 1;
            } else {
                this->number.push_back(number[index] - '0');
            }
            index++;
        }
        this->NoZeroes();
    }

    void LongNum::NoZeroes() {
        int n = std::max(1, exponent);
        while (number.size() > n && number[number.size() - 1] == 0) {
            number.erase(number.end() - 1);
        }
        while (number.size() > 1 && number[0] == 0) {
            number.erase(number.begin());
            exponent--;
        }
        while (number.size() > 1 && number[number.size() - 1] == 0) {
            number.erase(number.end() - 1);
        }
        if (number.size() == 1 && number[0] == 0) {
            exponent = 1;
            sign = 1;
        }
    }

    std::string LongNum::ToString() const {
        std::string ans;
        if (sign == -1) {
            ans += '-';
        }

        if (exponent > 0) {
            int i = 0;
            while(i < number.size() && i < exponent) {
                ans += number[i++] + '0';
            }
            while (i < exponent){
                ans += '0';
                i++;
            }
            if (i < number.size()) {
                ans += '.';
                while(i < number.size()) {
                    ans += number[i++] + '0';
                }
            }
        }
        else {
           ans += "0.";
            for (long i = 0; i < -exponent; i++) {
                ans += "0";
            }
            for (int i = 0; i < number.size(); i++) {
                ans += number[i++] + '0';
            }
        }
        return ans;
    }

    LongNum LongNum::Sum(const LongNum &other) const {
        int exp = std::max(exponent, other.exponent);
        std::vector<int> first(number);
        std::vector<int> second(other.number);
        for(int i = exponent; i < exp; i++) {
            first.insert(first.begin(), 0);
        }
        for(int i = other.exponent; i < exp; i++) {
            second.insert(second.begin(), 0);
        }

        int size = std::max(first.size(), second.size());
        while (first.size() != size) {
            first.push_back(0);
        }
        while (second.size() != size) {
            second.push_back(0);
        }

        LongNum res;
        res.sign = sign;
        res.number = std::vector<int>(size + 1, 0);
        for (int i = 0; i < size; i++) {
            res.number[i + 1] = first[i] + second[i];
        }
        for (int i = size; i > 0; i--) {
            res.number[i - 1] += res.number[i] / 10;
            res.number[i] %= 10;
        }
        res.exponent = exp + 1;
        res.NoZeroes();
        return res;
    }

    LongNum LongNum::Diff(const LongNum &other) const {
        bool cmp = *this > other;
        long exp = std::max(exponent, other.exponent);
        std::vector<int> first(cmp ? number : other.number);
        std::vector<int> second(cmp ? other.number : number);
        for(int i = cmp ? exponent : other.exponent; i < exp; i++) {
            first.insert(first.begin(), 0);
        }
        for(int i = cmp ? other.exponent : exponent; i < exp; i++) {
            second.insert(second.begin(), 0);
        }

        int size = std::max(first.size(), second.size());
        while (first.size() != size) {
            first.push_back(0);
        }
        while (second.size() != size) {
            second.push_back(0);
        }

        LongNum res;
        res.sign = cmp ? 1 : -1;
        res.number = std::vector<int>(size + 1, 0);
        for (int i = 0; i < size; i++) {
            res.number[i + 1] = first[i] - second[i];
        }
        for (int i = size; i > 0; i--) {
            if (res.number[i] < 0) {
                res.number[i] += 10;
                res.number[i - 1]--;
            }
        }
        res.exponent = exp + 1;
        res.NoZeroes();
        return res;
    }

    LongNum LongNum::Mul(const LongNum &other) const {
        int size = number.size() + other.number.size();
        LongNum res;
        res.sign = sign * other.sign;
        res.number = std::vector<int>(size, 0);
        res.exponent = exponent + other.exponent;
        for (int i = 0; i < number.size(); i++) {
            for (int j = 0; j < other.number.size(); j++) {
                res.number[i + j + 1] += number[i] * other.number[j];
            }
        }
        for (int i = size - 1; i > 0; i--) {
            res.number[i - 1] += res.number[i] / 10;
            res.number[i] %= 10;
        }
        res.NoZeroes();
        return res;
    }

    LongNum LongNum::Div(const LongNum &other) const {
        if (other.number.size() == 1 && other.number[0] == 0)
            throw "LongDouble LongDouble::inverse() - division by zero!";

        LongNum divider(other);
        divider.sign = 1;
        LongNum divided = 1_LN;
        LongNum otherinverse;
        otherinverse.sign = other.sign;
        otherinverse.exponent = 1;
        otherinverse.number = std::vector<int>();
        while (divider < 1_LN) {
            divider.exponent++;
            otherinverse.exponent++;
        }
        while (divided < divider) {
            divided.exponent++;
        }
        otherinverse.exponent -= divided.exponent - 1;

        int tmp = 0;
        int maxtmp = divDigits + std::max(0, otherinverse.exponent);
        do {
            int cur = 0;
            while (divided >= divider) {
                cur++;
                divided = divided - divider;
            }
            divided.exponent++;
            divided.NoZeroes();
            otherinverse.number.push_back(cur);
            tmp++;
        } while (divided != 0_LN && tmp < maxtmp);

        LongNum ans =  *this * otherinverse;
        int i = ans.number.size() - std::max(0, exponent) - 1;
        int n = std::max( 0, ans.exponent);
        if (i > n && ans.number[i] == 9) {
            while (i > n && ans.number[i] == 9) {
                i--;
            }
            if (ans.number[i] == 9) {
                ans.number.erase(ans.number.begin() + n, ans.number.end());
                if(ans.sign == 1) {
                    ans += 1_LN;
                } else {
                    ans -= 1_LN;
                }
            }
            else {
                ans.number.erase(ans.number.begin() + i + 1, ans.number.end());
                ans.number[i]++;
            }
        }
        return ans;
    }

    void LongNum::Round(int cnt) {
        if (cnt < 0) {
            return;
        }
        while (number.size() - exponent > cnt) {
            number.pop_back();
        }
    }

    LongNum LongNum::operator+(const LongNum &other) const {
        if(sign == other.sign) {
            return Sum(other);
        }
        if (sign == -1) {
            return other - (-(*this));
        }
        return *this - (-other);
    }

    LongNum LongNum::operator+=(const MyLongNum::LongNum &other) {
        return *this = *this + other;
    }

    LongNum LongNum::operator-(const LongNum &other) const {
        if (sign == 1 && other.sign == 1) {
            return Diff(other);
        }
        if (sign == -1 && other.sign == -1)
            return (-other) - (-(*this));

        return *this + (-other);
    }

    LongNum LongNum::operator-() const {
        LongNum res;
        res.sign = -sign;
        res.exponent = exponent;
        res.number = std::vector<int>(number);
        return res;
    }

    LongNum LongNum::operator-=(const MyLongNum::LongNum &other) {
        return *this = *this - other;
    }

    LongNum LongNum::operator*(const LongNum &other) const {
        return Mul(other);
    }

    LongNum LongNum::operator*=(const MyLongNum::LongNum &other) {
        return *this = *this * other;
    }

    LongNum LongNum::operator/(const LongNum &other) const {
        return Div(other);
    }

    LongNum LongNum::operator/=(const MyLongNum::LongNum &other) {
        return *this = *this / other;
    }

    bool LongNum::operator==(const LongNum &other) const {
        if (sign != other.sign || exponent != other.exponent || number.size() != other.number.size()) {
            return false;
        }
        for (int i = 0; i < number.size(); i++) {
            if (number[i] != other.number[i]) {
                return false;
            }
        }
        return true;
    }

    bool LongNum::operator!=(const LongNum &other) const {
        return !(*this == other);
    }

    bool LongNum::operator>(const LongNum &other) const {
        if (sign != other.sign) {
            return sign > other.sign;
        }
        if (exponent != other.exponent) {
            return (exponent > other.exponent) ^ (sign == -1);
        }

        std::vector<int> first(number);
        std::vector<int> second(other.number);
        int size = std::max(first.size(), second.size());
        while (first.size() != size) {
            first.push_back(0);
        }
        while (second.size() != size) {
            second.push_back(0);
        }

        for (int i = 0; i < size; i++) {
            if (first[i] != second[i]) {
                return (first[i] > second[i]) ^ (sign == -1);
            }
        }
        return false;
    }

    bool LongNum::operator>=(const LongNum &other) const {
        return *this == other || *this > other;
    }

    bool LongNum::operator<(const LongNum &other) const {
        return !(*this >= other);
    }

    bool LongNum::operator<=(const LongNum &other) const {
        return !(*this > other);
    }

    std::ostream &operator<<(std::ostream &os, const LongNum &other) {
        os << other.ToString();
        return os;
    }

    LongNum operator "" _LN(const char* str) {
        std::string h = str;
        LongNum ans(h);
        return ans;
    }

}