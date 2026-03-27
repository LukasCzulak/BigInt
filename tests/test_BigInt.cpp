#include <gtest/gtest.h>

#include "BigInt.hpp"

TEST(BigIntTest, BasicAddition) {
    BigInt a(42);
    BigInt b(27);
    BigInt res = a + b;

    EXPECT_EQ(res.toInt(), 69);
}

TEST(BigIntTest, AdditionWithZero) {
    BigInt a(42);
    BigInt zero(0);
    BigInt res = a + zero;

    EXPECT_EQ(res.toInt(), 42);
}
