#include <gtest/gtest.h>

#include "BigInt.hpp"

TEST(BigIntTest, NumDigitsZero) {
    BigInt a(0);

    EXPECT_EQ(a.num_digits(), 0);
}

TEST(BigIntTest, NumDigitsNonZero) {
    BigInt a(123);

    EXPECT_EQ(a.num_digits(), 3);
}

TEST(BigIntTest, StringConstructor) {
    BigInt a("5");

    EXPECT_EQ(a.toInt(), 5);
}

TEST(BigIntTest, StringConstructor2) {
    BigInt a("25");

    EXPECT_EQ(a.toInt(), 25);
}

TEST(BigIntTest, StringConstructor3) {
    BigInt a("9999");

    EXPECT_EQ(a.toInt(), 9999);
}

TEST(BigIntTest, StringConstructorInvalid) {
    try {
        BigInt a("abc");
        ASSERT_TRUE(false);  // shouldn't be reached
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "Encountered non digits in string constructor!");
    }
}

TEST(BigIntTest, StringConstructorBig) {
    std::string s = "1234567890";
    const size_t iterations = 10;
    size_t size = s.size();
    for (size_t i = 0; i < iterations; ++i) {
        s += s;  // doubles each time
        size *= 2;
    }
    BigInt a(s);

    EXPECT_EQ(a.num_digits(), size);
}

TEST(BigIntTest, NormalizeZero) {
    BigInt a;
    BigInt b(0);
    a.normalize();
    b.normalize();

    EXPECT_EQ(a.num_digits(), 0);
    EXPECT_EQ(b.num_digits(), 0);
}

TEST(BigIntTest, SetDigits) {
    BigInt a;
    a.set_number_of_digits(10);

    EXPECT_EQ(a.num_digits(), 10);
}

TEST(BigIntTest, SetDigitsThenNormalize) {
    BigInt a;
    a.set_number_of_digits(10);
    a.normalize();

    EXPECT_EQ(a.num_digits(), 0);
}
