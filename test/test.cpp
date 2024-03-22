#include <gtest/gtest.h>
#include <exception>
#include <string>
#include "../includes/LongNum.h"

using namespace MyLongNum;

TEST(AddOperation, PosNumbers) {
LongNum first(nullptr), second(nullptr), ans(nullptr);
first = 1.01_LN;
second = 1.01_LN;
ans = 2.02_LN;
EXPECT_EQ((first + second).ToString(), ans.ToString()) << (first + second).ToString();

first = 2.5_LN;
second = 2.535_LN;
ans = 5.035_LN;
EXPECT_EQ((first + second).ToString(), ans.ToString()) << (first + second).ToString();

}

TEST(AddOperation, NegNumbers) {
LongNum first(nullptr), second(nullptr), ans(nullptr);
first = -1.01_LN;
second = -1.01_LN;
ans = -2.02_LN;
EXPECT_EQ((first + second).ToString(), ans.ToString()) << (first + second).ToString();

first = -2.5_LN;
second = -2.535_LN;
ans = -5.035_LN;
EXPECT_EQ((first + second).ToString(), ans.ToString()) << (first + second).ToString();
}

TEST(AddOperation, DifSignNumbers) {
LongNum first(nullptr), second(nullptr), ans(nullptr);
first = -1.01_LN;
second = 1.01_LN;
ans = 0_LN;
EXPECT_EQ((first + second).ToString(), ans.ToString()) << (first + second).ToString();

first = 10.0005_LN;
second = -1.01_LN;
ans = 8.995_LN;
EXPECT_EQ((first + second).ToString(), ans.ToString()) << (first + second).ToString();

first = -10.0005_LN;
second = 1.01_LN;
ans = -8.995_LN;
EXPECT_EQ((first + second).ToString(), ans.ToString()) << (first + second).ToString();
}

TEST(DiffOperation, PosNumbers) {
LongNum first(nullptr), second(nullptr), ans(nullptr);
first = 1.01_LN;
second = 1.01_LN;
ans = 0_LN;
EXPECT_EQ((first - second).ToString(), ans.ToString()) << (first - second).ToString();

first = 10.0005_LN;
second = 1.01_LN;
ans = 8.995_LN;
EXPECT_EQ((first - second).ToString(), ans.ToString()) << (first - second).ToString();
}

TEST(DiffOperation, NegativeNumbers) {
LongNum first(nullptr), second(nullptr), ans(nullptr);
first = -1.01_LN;
second = -1.01_LN;
ans = 0_LN;
EXPECT_EQ((first - second).ToString(), ans.ToString()) << (first - second).ToString();

first = -10.0005_LN;
second = -1.01_LN;
ans = -8.995_LN;
EXPECT_EQ((first - second).ToString(), ans.ToString()) << (first - second).ToString();
}

TEST(DiffOperation, DifSignNumbers) {
LongNum first(nullptr), second(nullptr), ans(nullptr);
first = -1.01_LN;
second = 1.01_LN;
ans = -2.02_LN;
EXPECT_EQ((first - second).ToString(), ans.ToString()) << (first - second).ToString();

first = 10.0005_LN;
second = -1.01_LN;
ans = 11.0105_LN;
EXPECT_EQ((first - second).ToString(), ans.ToString()) << (first - second).ToString();
}

TEST(MulOperationTest, Numbers) {
LongNum first(nullptr), second(nullptr), ans(nullptr);
first = 1.01_LN;
second = 1.01_LN;
ans = 1.0201_LN;
EXPECT_EQ((first * second).ToString(), ans.ToString()) << (first * second).ToString();

first = 105.0005_LN;
second = 0_LN;
ans = 0_LN;
EXPECT_EQ((first * second).ToString(), ans.ToString()) << (first * second).ToString();

first = 0_LN;
second = 15.535_LN;
ans = 0_LN;
EXPECT_EQ((first * second).ToString(), ans.ToString()) << (first * second).ToString();

first = -1.01_LN;
second = 1.01_LN;
ans = -1.0201_LN;
EXPECT_EQ((first * second).ToString(), ans.ToString()) << (first * second).ToString();

first = -1.01_LN;
second = -1.01_LN;
ans = 1.0201_LN;
EXPECT_EQ((first * second).ToString(), ans.ToString()) << (first * second).ToString();

}

TEST(DivOperationTest, Numbers) {
LongNum first(nullptr), second(nullptr), ans(nullptr);
first = 1.01_LN;
second = 1.01_LN;
ans = 1_LN;
EXPECT_EQ((first / second).ToString(), ans.ToString()) << (first / second).ToString();

first = 1.01_LN;
second = 0_LN;
ans = 0_LN;
EXPECT_ANY_THROW(first / second) << (first / second).ToString();

first = 0_LN;
second = 1.01_LN;
ans = 0_LN;
EXPECT_EQ((first / second).ToString(), ans.ToString()) << (first / second).ToString();

first = -1.01_LN;
second = 100_LN;
ans = -0.0101_LN;
EXPECT_EQ((first / second).ToString(), ans.ToString()) << (first / second).ToString();

}

TEST(MinusTest, Numbers) {
LongNum first(nullptr);
std::string ans;
first = -1.01_LN;
ans = "1.01";
EXPECT_EQ((-first).ToString(), ans) << (-first).ToString();

first = 1.01_LN;
ans = "-1.01";
EXPECT_EQ((-first).ToString(), ans) << (-first).ToString();

first = 0_LN;
ans = "0";
EXPECT_EQ((-first).ToString(), ans) << (-first).ToString();

first = -0_LN;
ans = "0";
EXPECT_EQ((-first).ToString(), ans) << (-first).ToString();

}

TEST(LogicTest, Equals) {
LongNum first(nullptr), second(nullptr);
bool ans;
first = 1.01_LN;
second = 1.01_LN;
ans = true;
EXPECT_EQ(first == second, ans) << first.ToString() << " " << second.ToString();

first = -1.01_LN;
second = 1.01_LN;
ans = false;
EXPECT_EQ(first == second, ans) << first.ToString() << " " << second.ToString();

first = 1.010001_LN;
second = 1.01_LN;
ans = false;
EXPECT_EQ(first == second, ans) << first.ToString() << " " << second.ToString();

first = 0.000_LN;
second = 0_LN;
ans = true;
EXPECT_EQ(first == second, ans) << first.ToString() << " " << second.ToString();

first = 0.000_LN;
second = -0_LN;
ans = true;
EXPECT_EQ(first == second, ans) << first.ToString() << " " << second.ToString();
}

TEST(LogicTest, NotEquals) {
LongNum first(nullptr), second(nullptr);
bool ans;
first = 1.01_LN;
second = 1.01_LN;
ans = false;
EXPECT_EQ(first != second, ans) << first.ToString() << " " << second.ToString();

first = -1.01_LN;
second = 1.01_LN;
ans = true;
EXPECT_EQ(first != second, ans) << first.ToString() << " " << second.ToString();

first = 1.010001_LN;
second = 1.01_LN;
ans = true;
EXPECT_EQ(first != second, ans) << first.ToString() << " " << second.ToString();

first = 0.000_LN;
second = 0_LN;
ans = false;
EXPECT_EQ(first != second, ans) << first.ToString() << " " << second.ToString();

first = 0.000_LN;
second = -0_LN;
ans = false;
EXPECT_EQ(first != second, ans) << first.ToString() << " " << second.ToString();
}

TEST(LogicTest, More) {
LongNum first(nullptr), second(nullptr);
bool ans;
first = 1.01_LN;
second = 1.01_LN;
ans = false;
EXPECT_EQ(first > second, ans) << first.ToString() << " " << second.ToString();

first = 1.01001_LN;
second = 1.01_LN;
ans = true;
EXPECT_EQ(first > second, ans) << first.ToString() << " " << second.ToString();

first = -1.01_LN;
second = 1.01_LN;
ans = false;
EXPECT_EQ(first > second, ans) << first.ToString() << " " << second.ToString();

first = 1.01_LN;
second = -1.01_LN;
ans = true;
EXPECT_EQ(first > second, ans) << first.ToString() << " " << second.ToString();
}

TEST(LogicTest, Less) {
LongNum first(nullptr), second(nullptr);
bool ans;
first = 1.01_LN;
second = 1.01_LN;
ans = false;
EXPECT_EQ(first < second, ans) << first.ToString() << " " << second.ToString();

first = 1.01001_LN;
second = 1.01_LN;
ans = false;
EXPECT_EQ(first < second, ans) << first.ToString() << " " << second.ToString();

first = -1.01_LN;
second = 1.01_LN;
ans = true;
EXPECT_EQ(first < second, ans) << first.ToString() << " " << second.ToString();

first = 1.01_LN;
second = -1.01_LN;
ans = false;
EXPECT_EQ(first < second, ans) << first.ToString() << " " << second.ToString();
}

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

}