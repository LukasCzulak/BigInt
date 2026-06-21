#include <gtest/gtest.h>

#include "Lexer.hpp"
#include "Parser.hpp"
#include "Utils.hpp"

TEST(ParserTest, SingleNumber) {
    BigInt res = parse_and_evaluate("5");
    EXPECT_EQ(res.toInt(), 5);
}

TEST(ParserTest, BasicAddition) {
    BigInt res = parse_and_evaluate("5 + 13");
    EXPECT_EQ(res.toInt(), 18);

    res = parse_and_evaluate("5 + 13 + 2 + 5");
    EXPECT_EQ(res.toInt(), 25);
}

TEST(ParserTest, BigAddition) {
    std::string str = "0";
    for (int i = 0; i < 1000; ++i) {
        str = str + " + 1";
    }
    BigInt res = parse_and_evaluate(str);
    EXPECT_EQ(res.toInt(), 1000);
}

TEST(ParserTest, BasicMultiplication) {
    BigInt res = parse_and_evaluate("5 * 3");
    EXPECT_EQ(res.toInt(), 15);

    res = parse_and_evaluate("5 * 3 * 2 * 2");
    EXPECT_EQ(res.toInt(), 60);
}

TEST(ParserTest, OperatorPrecedence) {
    BigInt result = parse_and_evaluate("10 + 2 * 3");
    EXPECT_EQ(result.toInt(), 16);
}

TEST(ParserTest, ParenthesisSyntax) {
    BigInt res = parse_and_evaluate("(5 * 3)");
    EXPECT_EQ(res.toInt(), 15);
}

TEST(ParserTest, ParenthesisNested) {
    BigInt res = parse_and_evaluate("5 * (3 * 4) + (2 * (1 + (4 + 1)))");
    EXPECT_EQ(res.toInt(), 72);
}

TEST(ParserTest, ParenthesisPrecedence1) {
    BigInt res = parse_and_evaluate("(5 + 3) * 2");
    EXPECT_EQ(res.toInt(), 16);

    res = parse_and_evaluate("2 * (5 + 3) * 2");
    EXPECT_EQ(res.toInt(), 32);
}

TEST(ParserTest, SyntaxErrorThrows) {
    EXPECT_THROW(parse_and_evaluate("10 + + 5"), std::runtime_error);
    EXPECT_THROW(parse_and_evaluate("( 5 + 5"), std::runtime_error);
}
