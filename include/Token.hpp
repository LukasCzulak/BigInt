#pragma once
#include <optional>

#include "BigInt.hpp"
#include "Token.hpp"

enum class TokenType {
    NUMBER,
    PLUS,
    MULT,
    LPAREN,
    RPAREN,
    END_OF_FILE,
    INVALID
};

struct Token {
    TokenType type;
    std::string text;
    std::optional<BigInt> value;
};
