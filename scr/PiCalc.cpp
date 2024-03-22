#include "../includes/LongNum.h"
namespace MyLongNum
{
    // 1 / 16^i * (4 / (8i + 1) - 2 / (8i + 4) - 1 / (8i + 5) - (1 / (8i + 6)) 
    LongNum PiCalc(int precision) {
        if (precision < 0) {
            throw "Negative number of characters";
        }

        LongNum ans("0.0");
        LongNum coef("1");
        LongNum j("0");
        for (int i = 0; i < precision + 2; i++) {
            ans = ans + 1_LN/coef * (4_LN/(8_LN * j + 1_LN) - 2_LN/(8_LN * j + 4_LN) - 1_LN/(8_LN * j + 5_LN) - 1_LN/(8_LN * j + 6_LN));
            j = j + 1_LN;
            coef = coef * 16_LN;
        }

        ans.Round(precision);
        return ans;
    }
}