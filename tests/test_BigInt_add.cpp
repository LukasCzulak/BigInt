#include <gtest/gtest.h>

#include "BigInt.hpp"

TEST(BigIntTest, BasicAddition) {
    BigInt a(4);
    BigInt b(2);
    BigInt res = a + b;

    EXPECT_EQ(res.toInt(), 6);
}

TEST(BigIntTest, AdditionWithZero) {
    BigInt a(4);
    BigInt zero(0);
    BigInt res = a + zero;

    EXPECT_EQ(res.toInt(), 4);
}

TEST(BigIntTest, AdditionCarryDigits) {
    BigInt a(4);
    BigInt b(7);
    BigInt res = a + b;

    EXPECT_EQ(res.toInt(), 11);
}

TEST(BigIntTest, AdditionBiggerNumbers) {
    BigInt a(42);
    BigInt b(27);
    BigInt res = a + b;

    EXPECT_EQ(res.toInt(), 69);
    EXPECT_EQ(res.num_digits(), 2);
}

TEST(BigIntTest, AdditionBiggerNumber2) {
    BigInt a(50);
    BigInt b(50);
    BigInt res = a + b;

    EXPECT_EQ(res.toInt(), 100);
    EXPECT_EQ(res.num_digits(), 3);
}

TEST(BigIntTest, AdditionBiggerNumbers3) {
    BigInt a(125);
    BigInt b(130);
    BigInt res = a + b;

    EXPECT_EQ(res.toInt(), 255);
    EXPECT_EQ(res.num_digits(), 3);
}
