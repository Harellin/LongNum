#include "../includes/LongNum.h"
#include <utility>
#include <vector>
#include <string>

const int divDigits = 100;

namespace MyLongNum {
    const LongNum Zero = LongNum("0");

    LongNum::LongNum() {
        sign = 1;
        precision = 0;
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
            if(number[i] != '.') {
                this->number.push_back(number[i] - '0');
            }
        }
        this->NoZeroesBegin();
        this->NoZeroesEnd();
    }

    LongNum::LongNum(std::vector<int> number, int len, int sign) {
        this->sign = sign;
        this->number = std::move(number);
        precision = len;
        this->NoZeroesEnd();
        this->NoZeroesBegin();
    }

    int LongNum::FindPrecision(const std::string &str) {
        int ans = 0;
        int fl = 0;
        for(int i = str.size() - 1; i >= 0; i--) {
            if(str[i] == '.') {
                fl = 1;
                break;
            }
            ans++;
        }
        if(fl) {
            return ans;
        } else {
            return 0;
        }
    }

    void LongNum::NoZeroesBegin() {
        while(number.size() > precision && *number.begin() == 0) {
            number.erase(number.begin());
        }
        if(number.size() - precision == 0) {
            number.insert(number.begin(), 0);
            sign = 1;
        }
    }

    void LongNum::NoZeroesEnd() {
        while (number.size() > 0 && precision > 0 && number.back() == 0) {
            number.pop_back();
            precision--;
        }
    }

    std::string LongNum::ToString() const {
        std::string ans;
        int i = 0;
        if(sign == -1) {
            ans += "-";
            i++;
        }

        for(; i < number.size(); i++) {
            if(precision == number.size() - i) {
                ans += ".";
            }
            ans += ('0' + number[i]);
        }
        return ans;
    }

    LongNum LongNum::Sum(const LongNum &other) const {
        int maxprec = std::max(precision, other.precision);
        std::vector<int> first = number;
        std::vector<int> second = other.number;
        int precfirst = precision, precsecond = other.precision;

        while(precfirst < maxprec) {
            precfirst++;
            first.push_back(0);
        }
        while(precsecond < maxprec) {
            precsecond++;
            second.push_back(0);
        }

        int maxlen = std::max(first.size() - precfirst, second.size() - precsecond);
        while(first.size() - precfirst < maxlen) {
            first.insert(first.begin(), 0);
        }
        while(second.size() - precsecond < maxlen) {
            second.insert(second.begin(), 0);
        }

        std::vector<int> ans(std::max(first.size(), second.size()));
        for(int i = ans.size() - 1; i >= 0; i--) {
            if(second.size() > i && first.size() > i) {
                ans[i] = second[i] + first[i];
            } else if(second.size() > i) {
                ans[i] = second[i];
            } else if(first.size() > i) {
                ans[i] = first[i];
            }
        }

        for(int i = ans.size() - 2; i >= 0; i--) {
            ans[i] += (ans[i + 1] / 10);
            ans[i + 1] %= 10;
        }
        if(ans[0] > 9) {
            ans.insert(ans.begin(), 1);
            ans[1] %= 10;
        }
        LongNum res(ans, maxprec, 1);
        res.NoZeroesBegin();
        res.NoZeroesEnd();
        return res;
    }

    LongNum LongNum::Diff(const LongNum &other) const {
        if(*this == 0_LN) {
            LongNum res = other;
            res.sign = res.sign * (-1);
            return res;
        }
        LongNum htis = *this, hother = other;
        htis.sign = 1; hother.sign = 1;
        bool cmp = htis > hother; //теперь 1 число будет обозначено за большее, 2 за меньшее

        long prec1 = cmp ? precision : other.precision;
        long prec2 = cmp ? other.precision : precision;
        long prec = std::max(prec1, prec2);

        std::vector<int> first = cmp ? number : other.number;
        std::vector<int> second = cmp ? other.number : number;

        while (prec1 != prec) {
            first.push_back(0);
            prec1++;
        }
        while (prec2 != prec) {
            second.push_back(0);
            prec2++;
        }

        int maxlen = std::max(first.size() - prec1, second.size() - prec2);
        while(first.size() - prec1 < maxlen) {
            first.insert(first.begin(), 0);
        }
        while(second.size() - prec2 < maxlen) {
            second.insert(second.begin(), 0);
        }

        int size = std::max(first.size(), second.size());
        std::vector<int> ans(size);
        for (int i = size - 1; i >= 0; i--) {
            if(second.size() > i && first.size() > i) {
                ans[i] = first[i] - second[i];
            } else if(second.size() > i) {
                ans[i] = second[i];
            } else if(first.size() > i) {
                ans[i] = first[i];
            }
        }
        for (int i = size - 1; i > 0; i--) {
            if (ans[i] < 0) {
                ans[i] += 10;
                ans[i - 1]--;
            }
        }

        LongNum res(ans, prec, cmp ? 1 : -1);
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

    LongNum LongNum::Div(const LongNum &other, int cntsymbols) const {
        if (other == 0_LN) {
            throw "DivisionByZero";
        }

        const int Precision = 100;
        LongNum divided = *this;
        divided.sign = 1;
        LongNum divider = other;
        divider.sign = 1;
        LongNum res;
        res.sign = sign * other.sign;
        res.precision = 0;
        int explen = (number.size() - precision) - (other.number.size() - other.precision);
        while (divided.number.size() - divided.precision < divider.number.size() - divider.precision) {
            divided.number.push_back(0);
            res.number.push_back(0);
            res.precision++;
        }

        while (res.number.size() - explen < Precision && divided != 0_LN) {
            int cur = 0;
            while(divided >= divider) {
                cur++;
                divided = divided - divider;
            }
            res.number.push_back(cur);
            if(divided != 0_LN) {
                if (divided.precision != 0) {
                    divided.precision--;
                } else {
                    divided.number.push_back(0);
                    res.precision++;
                }
            }
        }
        res.NoZeroesEnd();
        res.NoZeroesBegin();
        return res;
    }

    void LongNum::Round(int cnt) {
        if (cnt < 0) {
            return;
        }
        if (precision <= cnt) {
            return;
        }

        while (precision > cnt) {
            number.pop_back();
            precision--;
        }
    }

    LongNum LongNum::operator+(const LongNum &other) const {
        if(sign == other.sign) {
            LongNum ans = this->Sum(other);
            ans.sign = sign;
            return ans;
        }
        if(sign == -1) {
            return other.Diff(*this);
        }
        return this->Diff(other);
    }

    LongNum LongNum::operator-(const LongNum &other) const {
        if(sign == 1 && other.sign == 1) {
            return this->Diff(other);
        }
        if(sign == -1 && other.sign == -1) {
            return other.Diff(*this);
        }
        if(sign == 1 && other.sign == -1) {
            return this->Sum(other);
        }
        LongNum res = this->Sum(other);
        res.sign = -1;
        return res;
    }

    LongNum LongNum::operator-() const {
        return Zero.Diff(*this);
    }

    LongNum LongNum::operator*(const LongNum &other) const {
        LongNum ans = this->Mul(other);
        ans.sign = sign * other.sign;
        return ans;
    }

    LongNum LongNum::operator/(const LongNum &other) const {
        return this->Div(other, std::max(this->precision, other.precision));
    }

    bool LongNum::operator==(const LongNum &other) const {
        LongNum first = *this, second = other;
        first.NoZeroesBegin(); first.NoZeroesEnd();
        second.NoZeroesBegin(); second.NoZeroesEnd();
        if (first.sign != second.sign || first.precision != second.precision || first.number.size() != second.number.size()) {
            return false;
        }
        for(int i = 0; i < first.number.size(); i++) {
            if(first.number[i] != second.number[i]) {
                return false;
            }
        }
        return true;
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
        int i, j;
        for (i = 0, j = 0; i < number.size() && j < other.number.size(); i++, j++) {
            if (number[i] < other.number[j]) {
                if(sign == 1) {
                    return true;
                } else {
                    return false;
                }
            }
            if (number[i] > other.number[j]) {
                if(sign == 1) {
                    return false;
                } else {
                    return true;
                }
            }
        }
        if (i != number.size()) {
            if(sign == 1) {
                return false;
            } else {
                return true;
            }
        } else {
            if(sign == 1) {
                return true;
            } else {
                return false;
            }
        }
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