#include <gtest/gtest.h>

#include "Lexer.hpp"

TEST(LexerTest, SingleCharacters) {
    Lexer lexer("+ * ( )");
    std::vector<Token> tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 5);  // 4 symbols + end
    EXPECT_EQ(tokens[0].type, TokenType::PLUS);
    EXPECT_EQ(tokens[1].type, TokenType::MULT);
    EXPECT_EQ(tokens[2].type, TokenType::LPAREN);
    EXPECT_EQ(tokens[3].type, TokenType::RPAREN);
    EXPECT_EQ(tokens[4].type, TokenType::END_OF_FILE);
}

TEST(LexerTest, SimpleNumber) {
    Lexer lexer("1234");
    std::vector<Token> tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);  // number and end
    EXPECT_EQ(tokens[0].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[0].text, "1234");

    ASSERT_TRUE(tokens[0].value.has_value());
    EXPECT_EQ(tokens[0].value.value().toInt(), 1234);
}

TEST(LexerTest, SimpleExpressionAndWhitespaces) {
    Lexer lexer("  58   + \n 319 \t \r * ( 2 )  ");
    std::vector<Token> tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 8);  // 58, +, 319, *, (, 2, ), EOF
    EXPECT_EQ(tokens[0].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[0].value.value().toInt(), 58);

    EXPECT_EQ(tokens[1].type, TokenType::PLUS);

    EXPECT_EQ(tokens[2].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[2].value.value().toInt(), 319);

    EXPECT_EQ(tokens[3].type, TokenType::MULT);
    EXPECT_EQ(tokens[4].type, TokenType::LPAREN);

    EXPECT_EQ(tokens[5].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[5].value.value().toInt(), 2);

    EXPECT_EQ(tokens[6].type, TokenType::RPAREN);
    EXPECT_EQ(tokens[7].type, TokenType::END_OF_FILE);
}