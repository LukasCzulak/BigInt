#pragma once
#include <string>
#include <vector>

#include "Token.hpp"

class Lexer {
private:
    std::string text;
    bool is_whitespace(char c) const;
    bool is_digit(char c) const;

public:
    Lexer(std::string t) : text(t) {}
    ~Lexer() = default;

    std::vector<Token> tokenize();
};
