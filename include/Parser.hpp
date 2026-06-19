#pragma once
#include <memory>

#include "AST.hpp"
#include "Token.hpp"

class Parser {
private:
    std::vector<Token> tokens;

public:
    Parser(std::vector<Token> ts) : tokens(ts) {}
    ~Parser() = default;

    std::unique_ptr<ASTNode> parse();
};
