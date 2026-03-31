#include <gtest/gtest.h>

#include "BigInt.hpp"

TEST(BigIntTest, BasicMultiplication) {
    BigInt a(2);
    BigInt b(3);
    BigInt res = a * b;

    EXPECT_EQ(res.toInt(), 6);
}

TEST(BigIntTest, MultiplicationWithZero) {
    BigInt a(4);
    BigInt zero(0);
    BigInt res = a * zero;

    EXPECT_EQ(res.toInt(), 0);
}

TEST(BigIntTest, MultiplicationWithOne) {
    BigInt a(4);
    BigInt one(1);
    BigInt res = a * one;

    EXPECT_EQ(res.toInt(), 4);
}

TEST(BigIntTest, MultiplicationCarryDigits) {
    BigInt a(4);
    BigInt b(7);
    BigInt res = a * b;

    EXPECT_EQ(res.toInt(), 28);
}

TEST(BigIntTest, MultiplicationBiggerNumbers) {
    BigInt a(53);
    BigInt b(27);
    BigInt res = a * b;

    EXPECT_EQ(res.toInt(), 1431);
}

TEST(BigIntTest, MultiplicationBiggerNumbers2) {
    BigInt a(125);
    BigInt b(130);
    BigInt res = a * b;

    EXPECT_EQ(res.toInt(), 16250);
}

TEST(BigIntTest, MultiplicationBiggerNumbers3) {
    BigInt a(99);
    BigInt b(99);
    BigInt res = a * b;

    EXPECT_EQ(res.toInt(), 9801);
}
