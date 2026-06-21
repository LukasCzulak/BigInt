#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Lexer.hpp"
#include "Parser.hpp"

// inline such that all files only use this one definitions and dont collide
inline BigInt parse_and_evaluate(const std::string& input) {
    Lexer lexer(input);
    std::vector<Token> tokens = lexer.tokenize();

    Parser parser(tokens);
    std::unique_ptr<ASTNode> root = parser.parse();

    return root->evaluate();
}