#include "../include/LongNum.h"

const int divDigits = 100;

namespace LongNum {
    const LongNum Zero = LongNum("0");

    LongNum::LongNum() {
        sign = 1;
        precision = 0;
        number.push_back(0);
    }

    LongNum::LongNum(std::string number) {
        if(number[0] == '-') {
            sign = -1;
            number.erase(number.begin());
        } else {
            sign = 1;
        }

        precision = FindPrecision(number);

        for(int i = 0; i < number.size(); i++) {
            number.push_back(number[i] - '0');
        }
        this->NoZeroesBegin();
        this->NoZeroesEnd();
    }

    LongNum::LongNum(std::vector<int> number, int len, int sign) {
        sign = sign;
        number = number;
        precision = len;
        this -> NoZeroesEnd();
        this -> NoZeroesBegin();
    }

    int LongNum::FindPrecision(const std::string &str) {
        int ans = 0;
        for(int i = str.size() - 1; i >= 0; i--) {
            if(str[i] == '.') {
                break;
            }
            ans++;
        }
        return ans;
    }

    void LongNum::NoZeroesBegin() {
        while(number.size() > precision + 1 && number.back() == 0) {
            number.pop_back();
        }
        return;
    }

    void LongNum::NoZeroesEnd() {
        while (precision > 0 && *number.begin() == 0) {
            number.erase(number.begin());
            precision--;
        }
        return;
    }

    int LongNum::FirstNotZero() const {
        int ans = 0;
        for(int i = number.size() - 1; i >= 0; i--) {
            ans++;
            if(number[i] != 0) {
                break;
            }
        }
        return ans;
    }

    std::string LongNum::ToString() const {
        std::string ans = "";
        if(sign == -1) {
            ans += "-";
        }

        for(int i = number.size() - 1; i >= 0; i--) {
            if(precision == i + 1) {
                ans += ".";
            }
            ans += ('0' + number[i]);
        }
        return ans;
    }

    LongNum LongNum::Sum(const LongNum &other) const {
        long prec1 = precision;
        long prec2 = other.precision;
        long prec = std::max(prec1, prec2);

        std::vector<int> first(number.size());
        std::vector<int> second(other.number.size());

        while (prec1 != prec) {
            first.insert(first.begin(), 0);
            prec1++;
        }
        while (prec2 != prec) {
            second.insert(second.begin(), 0);
            prec2++;
        }

        int size = std::max(first.size(), second.size());
        while (first.size() != size) {
            first.push_back(0);
        }

        while (second.size() != size) {
            second.push_back(0);
        }

        LongNum res;
        res.number = std::vector<int>(size + 1, 0);
        for (size_t i = 0; i < size; i++) {
            res.number[i + 1] = first[i] + second[i];
        }
        for (size_t i = size; i > 0; i--) {
            res.number[i - 1] += res.number[i] / 10;
            res.number[i] %= 10;
        }

        res.precision = prec + 1;
        res.NoZeroesEnd();
        res.NoZeroesBegin();
        return res;
    }

    LongNum LongNum::Diff(const LongNum &other) const {
        bool cmp = *this > other; //теперь 1 число будет обозначено за большее, 2 за меньшее

        long prec1 = cmp ? precision : other.precision;
        long prec2 = cmp ? other.precision : precision;
        long prec = std::max(prec1, prec2);

        std::vector<int> first(cmp ? number : other.number);
        std::vector<int> second(cmp ? other.number : number);

        while (prec1 != prec) {
            first.insert(first.begin(), 0);
            prec1++;
        }
        while (prec2 != prec) {
            second.insert(second.begin(), 0);
            prec2++;
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

        for (size_t i = 0; i < size; i++) {
            res.number[i + 1] = first[i] - second[i];
        }
        for (size_t i = size; i > 0; i--) {
            if (res.number[i] < 0) {
                res.number[i] += 10;
                res.number[i - 1]--;
            }
        }

        res.precision = prec + 1;
        res.NoZeroesEnd();
        res.NoZeroesBegin();
        return res;
    }

    LongNum LongNum::Mul(const LongNum &other) const {
        size_t len = number.size() + other.number.size();

        LongNum res;
        res.number = std::vector<int>(len, 0);
        res.precision = precision + other.precision;

        for (size_t i = 0; i < number.size(); i++) {
            for (size_t j = 0; j < other.number.size(); j++) {
                res.number[i + j + 1] += number[i] * other.number[j];
            }
        }
        for (size_t i = len - 1; i > 0; i--) {
            res.number[i - 1] += res.number[i] / 10;
            res.number[i] %= 10;
        }

        res.NoZeroesBegin();
        res.NoZeroesEnd();
        return res;
    }

    LongNum LongNum::Div(const LongNum &other) const {
        if (number.size() == 1 && number[0] == 0)
            throw std::string("LongNum - division by zero!");

        LongNum copy = *this;
        std::vector<int> ans;
        int dif = number.size() - precision - FirstNotZero() - other.number.size() - other.precision - other.FirstNotZero();
        int exp = dif < 0 ? abs(dif) - 1: 0;
        int max_exp = std::max(precision, other.precision);
        for (int i = 0; i + dif < 0; i++) {
            ans.push_back(0);
        }

        while (dif >= 0 || exp < max_exp) {
            std::vector<int> div = other.number;
            int len = other.precision;
            if (dif > 0 && other.precision < dif) {
                len = 0;
                std::reverse(div.begin(), div.end());
                int cnt = 0;
                while (other.precision + cnt < dif) {
                    cnt += 1;
                    div.push_back(0);
                }
                std::reverse(div.begin(), div.end());
            } else if (dif < 0 && other.number.size() - other.precision <= -dif) {
                len = other.precision - dif;
                int cnt = 0;
                while (other.number.size() - other.precision + cnt <= -dif) {
                    cnt += 1;
                    div.push_back(0);
                }
            } else {
                len = other.precision - dif;
            }
            ans.push_back(0);
            LongNum copycopy(div, len, 1);
            copycopy.NoZeroesEnd();
            while (copy >= copycopy) {
                copy = copy - copycopy;
                ans[ans.size() - 1] += 1;
            }
            if (dif < 0) {
                exp += 1;
            }
            dif -= 1;
        }

        std::reverse(ans.begin(), ans.end());
        LongNum ans_num(ans, max_exp, sign * other.sign);
        ans_num.NoZeroesBegin();
        ans_num.NoZeroesEnd();
        return ans_num;
    }

    void LongNum::Round(int cnt) {
        if (cnt < 0) {
            return;
        }
        if (precision <= cnt) {
            return;
        }

        while (precision > cnt) {
            number.erase(number.begin());
            precision -= 1;
        }
        return;
    }

    LongNum LongNum::operator+(const LongNum &other) const {
        if(sign == other.sign) {
            LongNum ans = this->Sum(other);
            ans.sign = sign;
            return ans;
        }
        if(sign == -1) {
            return other - (Zero - (*this));
        }
        return *this - (Zero - other);
    }

    LongNum LongNum::operator-(const LongNum &other) const {
        if(sign == 1 && other.sign == 1) {
            return this->Diff(other);
        }
        if(sign == -1 && other.sign == -1) {
            return (Zero - other) - (Zero - *this);
        }
        return *this + (Zero - other);
    }

    LongNum LongNum::operator*(const LongNum &other) const {
        LongNum ans = this->Mul(other);
        ans.sign = sign * other.sign;
        return ans;
    }

    LongNum LongNum::operator/(const LongNum &other) const {
        return this->Div(other);
    }

    bool LongNum::operator==(const LongNum &other) const {
        if (sign == other.sign) {
            return number == other.number;
        }
        std::vector<int> nul = {0};
        if (number == nul && other.number == nul) {
            return true;
        }
        return false;
    }

    bool LongNum::operator!=(const LongNum &other) const {
        return !(*this == other);
    }

    bool LongNum::operator<(const LongNum &other) const {
        if (*this == other) return false;

        if (sign < other.sign) {
            return true;
        } else if (sign > other.sign) {
            return false;
        }

        if (number.size() - precision > other.number.size() - other.precision) {
            return false;
        }
        if (number.size() - precision < other.number.size() - other.precision) {
            return true;
        }

        bool ans = true;
        for (int i = number.size() - 1, j = other.number.size() - 1; i >= 0 && j >= 0; i--, j--) {
            if (number[i] < other.number[j]) {
                ans = true;
                break;
            }
            if (number[i] > other.number[j]) {
                ans = false;
                break;
            }
            if (i == 0) {
                ans = false;
                while (j > 0) {
                    j -= 1;
                    if (other.number[j] != 0) {
                        ans = true;
                        break;
                    }
                }
            } else if (j == 0) {
                ans = false;
            }
        }

        if (sign < other.sign) return true;
        return ans;
    }

    bool LongNum::operator<=(const LongNum &other) const {
        return *this == other || *this < other;
    }

    bool LongNum::operator>(const LongNum &other) const {
        return !(*this <= other);
    }

    bool LongNum::operator>=(const LongNum &other) const {
        return !(*this < other);
    }

    LongNum operator "" _LN(const char* str) {
        LongNum ans(str);
        return ans;
    }

}