#include <gtest/gtest.h>

#include "Lexer.hpp"
#include "Parser.hpp"
#include "Utils.hpp"

TEST(LargeNumbers, SingleNumber) {
    std::string res = parse_and_evaluate("123456789").toString();
    EXPECT_EQ(res, "123456789");
}

TEST(LargeNumbers, BigAddition) {
    std::string task = "123456789 + 123456789";
    std::string res = parse_and_evaluate(task).toString();
    EXPECT_EQ(res, "246913578");
}

TEST(LargeNumbers, BigMultiplication1) {
    std::string task = "123456789 * 123456789";
    std::string res = parse_and_evaluate(task).toString();
    EXPECT_EQ(res, "15241578750190521");
}

TEST(LargeNumbers, BigMultiplication2) {
    std::string task =
        "123456789 * 123456789 * 123456789 * 123456789 * 123456789 * 123456789";
    std::string res = parse_and_evaluate(task).toString();
    // 3540705968149597751242378595390670323015412790761
    // When the numbers get too big, I cannot write down the actual strings by
    // hand, but only a few key-digits
    EXPECT_EQ(res[0], '3');
    EXPECT_EQ(res[1], '5');
    EXPECT_EQ(res[2], '4');
    EXPECT_EQ(res[3], '0');
    EXPECT_EQ(res[4], '7');

    EXPECT_EQ(res[res.size() - 5], '9');
    EXPECT_EQ(res[res.size() - 4], '0');
    EXPECT_EQ(res[res.size() - 3], '7');
    EXPECT_EQ(res[res.size() - 2], '6');
    EXPECT_EQ(res[res.size() - 1], '1');
}