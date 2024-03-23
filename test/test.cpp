#include <gtest/gtest.h>
#include <exception>
#include <string>
#include "../includes/LongNum.h"

using namespace MyLongNum;

TEST(AddOperation, PosNumbers) {
    LongNum first = 1.01_LN;
    LongNum second = 1.01_LN;
    EXPECT_EQ(first + second, 2.02_LN);

    first = 2.5_LN;
    second = 2.535_LN;
    EXPECT_EQ(first + second, 5.035_LN);
}

TEST(AddOperation, NegNumbers) {
    LongNum first = -1.01_LN;
    LongNum second = -1.01_LN;
    EXPECT_EQ(first + second, -2.02_LN);

    first = -2.5_LN;
    second = -2.535_LN;
    EXPECT_EQ(first + second, -5.035_LN);
}

TEST(AddOperation, DifSignNumbers) {
    LongNum first = -1.01_LN;
    LongNum second = 1.01_LN;
    EXPECT_EQ(first + second, 0_LN);

    first = 10.0005_LN;
    second = -1.01_LN;
    EXPECT_EQ(first + second, 8.9905_LN);

    first = -10.0005_LN;
    second = 1.01_LN;
    EXPECT_EQ(first + second, -8.9905_LN);
}

TEST(DiffOperation, PosNumbers) {
    LongNum first = 1.01_LN;
    LongNum second = 1.01_LN;
    EXPECT_EQ(first - second, 0_LN);

    first = 10.0005_LN;
    second = 1.01_LN;
    EXPECT_EQ(first - second , 8.9905_LN);
}

TEST(DiffOperation, NegativeNumbers) {
    LongNum first = -1.01_LN;
    LongNum second = -1.01_LN;
    EXPECT_EQ(first - second , 0_LN);

    first = -10.0005_LN;
    second = -1.01_LN;
    EXPECT_EQ(first - second , -8.9905_LN);
}

TEST(DiffOperation, DifSignNumbers) {
    LongNum first = -1.01_LN;
    LongNum second = 1.01_LN;
    EXPECT_EQ(first - second , -2.02_LN);

    first = 10.0005_LN;
    second = -1.01_LN;
    EXPECT_EQ(first - second , 11.0105_LN);
}

TEST(MulOperationTest, Numbers) {
    LongNum first = 1.01_LN;
    LongNum second = 1.01_LN;
    EXPECT_EQ(first * second , 1.0201_LN);

    first = 105.0005_LN;
    second = 0_LN;
    EXPECT_EQ(first * second , 0_LN);

    first = 0_LN;
    second = 15.535_LN;
    EXPECT_EQ(first * second , 0_LN);

    first = -1.01_LN;
    second = 1.01_LN;
    EXPECT_EQ(first * second , -1.0201_LN);

    first = -1.01_LN;
    second = -1.01_LN;
    EXPECT_EQ(first * second , 1.0201_LN);
}

TEST(DivOperationTest, Numbers) {
    LongNum first = 1.01_LN;
    LongNum second = 1.01_LN;
    EXPECT_EQ(first / second , 1_LN);

    first = 1.01_LN;
    second = 0_LN;
    EXPECT_ANY_THROW(first / second);

    first = 0_LN;
    second = 1.01_LN;
    EXPECT_EQ(first / second , 0_LN);

    first = -1.01_LN;
    second = 100_LN;
    EXPECT_EQ(first / second , -0.0101_LN);
}

TEST(LogicTest, Equals) {
    bool ans;
    LongNum first = 1.01_LN;
    LongNum second = 1.01_LN;
    ans = true;
    EXPECT_EQ(first == second, ans) ;

    first = -1.01_LN;
    second = 1.01_LN;
    ans = false;
    EXPECT_EQ(first == second, ans) ;

    first = 1.010001_LN;
    second = 1.01_LN;
    ans = false;
    EXPECT_EQ(first == second, ans) ;

    first = 0.000_LN;
    second = 0_LN;
    ans = true;
    EXPECT_EQ(first == second, ans) ;

    first = 0.000_LN;
    second = -0_LN;
    ans = true;
    EXPECT_EQ(first == second, ans) ;
}

TEST(LogicTest, NotEquals) {
    LongNum first = 1.01_LN;
    LongNum second = 1.01_LN;
    EXPECT_EQ(first != second, false);

    first = -1.01_LN;
    second = 1.01_LN;
    EXPECT_EQ(first != second, true);

    first = 1.010001_LN;
    second = 1.01_LN;
    EXPECT_EQ(first != second, true);

    first = 0.000_LN;
    second = 0_LN;
    EXPECT_EQ(first != second, false);

    first = 0.000_LN;
    second = -0_LN;
    EXPECT_EQ(first != second, false);
}

TEST(LogicTest, More) {
    LongNum first = 1.01_LN;
    LongNum second = 1.01_LN;
    EXPECT_EQ(first > second, false);

    first = 1.01001_LN;
    second = 1.01_LN;
    EXPECT_EQ(first > second, true);

    first = -1.01_LN;
    second = 1.01_LN;
    EXPECT_EQ(first > second, false);

    first = 1.01_LN;
    second = -1.01_LN;
    EXPECT_EQ(first > second, true);
}

TEST(LogicTest, Less) {
    LongNum first = 1.01_LN;
    LongNum second = 1.01_LN;
    EXPECT_EQ(first < second, false) ;

    first = 1.01001_LN;
    second = 1.01_LN;
    EXPECT_EQ(first < second, false) ;

    first = -1.01_LN;
    second = 1.01_LN;
    EXPECT_EQ(first < second, true) ;

    first = 1.01_LN;
    second = -1.01_LN;
    EXPECT_EQ(first < second, false) ;
}
/*

TEST(PiCalc, More) {
    LongNum first = PiCalc(100);
    std::string ans = "3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679";
    EXPECT_EQ(first.ToString(), ans) << first.ToString() << " " << ans;

    first = PiCalc(1);
    ans = "3.1";
    EXPECT_EQ(first.ToString(), ans) << first.ToString() << " " << ans;

    first = PiCalc(0);
    ans = "3";
    EXPECT_EQ(first.ToString(), ans) << first.ToString() << " " << ans;

    EXPECT_ANY_THROW(PiCalc(-1));

}*/
