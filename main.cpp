#include <iostream>
#include "includes/LongNum.h"
#include <ctime>

using namespace MyLongNum;

LongNum PiCalc(int precision) {
    if (precision < 0) {
        throw "Negative number of characters";
    }

    LongNum coef1 = 5_LN;
    LongNum coef2 = 239_LN;
    LongNum coefi = 0_LN;
    LongNum coef1step2 = coef1 * coef1;
    LongNum coef2step2 = coef2 * coef2;
    LongNum ans = 0_LN;
    LongNum const1 = 1_LN;
    LongNum const2 = 2_LN;
    LongNum const4 = 4_LN;

    for(int i = 0; i < precision; i++) {
        ans = ans + (i % 2 ? -const1 : const1) *
                (const4 / (coef1 * (const2 * coefi + const1)) - const1 / (coef2 * (const2 * coefi + const1)));
        coefi = coefi + 1_LN;
        coef1 = coef1 * coef1step2;
        coef2 = coef2 * coef2step2;
    }

    ans = ans * const4;
    ans.Round(precision);
    return ans;
}

int main() {
    clock_t start_time = clock();
    LongNum pi = PiCalc(100);
    clock_t end_time = clock();
    double search_time = (double) (end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << search_time << std::endl;
    std::cout << pi.ToString() << std::endl;
    return 0;
}