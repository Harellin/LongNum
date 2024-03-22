#include <iostream>
#include "includes/LongNum.h"
#include <ctime>

using namespace MyLongNum;

int main(){
    clock_t start_time =  clock();
    LongNum pi = PiCalc(100);
    clock_t end_time = clock();
    double search_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << search_time << std::endl;
    std::cout << pi.ToString() << std::endl;
    return 0;
}