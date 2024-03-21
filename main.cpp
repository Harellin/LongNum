#include <iostream>
#include "include/LongNum.h"
#include <ctime>

using namespace LongNum;

int main(){
    clock_t start_time =  clock();
    LongNum pi = PiCalc(100)
    clock_t end_time = clock();
    double search_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << search_time << std::endl;
    std::cout << pi.GetLongNum() << std::endl;
    return 0;
}