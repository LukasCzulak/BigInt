#include "Parser.hpp"

#include "AST.hpp"

Token Parser::peek() const {
    if (current < tokens.size()) {
        return tokens[current];
    } else {  // safety
        return tokens.back();
    }
}

void Parser::step() { current++; }

std::unique_ptr<ASTNode> Parser::parse() {
    std::unique_ptr<ASTNode> root = parse_addition();
    expect(TokenType::END_OF_FILE, "Expected Nothing more, but got something!");
    return root;
}

std::unique_ptr<ASTNode> Parser::parse_addition() {
    // get the left side of the (possible) addition
    std::unique_ptr<ASTNode> left = parse_multiplication();

    // while we see another plus, create the AST to repeatedly add 2 components
    // for left-to-right evaluation
    while (peek().type == TokenType::PLUS) {
        step();  // '+'
        std::unique_ptr<ASTNode> right = parse_multiplication();
        left = std::make_unique<AddNode>(std::move(left), std::move(right));
    }

    return left;
}

std::unique_ptr<ASTNode> Parser::parse_multiplication() {
    // get the left side of the (possible) multiplication
    std::unique_ptr<ASTNode> left = parse_primary();

    // while we see another mult, create the AST to repeatedly mult 2 components
    // for left-to-right evaluation
    while (peek().type == TokenType::MULT) {
        step();  // '*'
        std::unique_ptr<ASTNode> right = parse_primary();
        left = std::make_unique<MultNode>(std::move(left), std::move(right));
    }

    return left;
}

std::unique_ptr<ASTNode> Parser::parse_primary() {
    if (peek().type == TokenType::NUMBER) {
        std::unique_ptr<NumberNode> num =
            std::make_unique<NumberNode>(peek().value.value());
        step();  // the number
        return num;
    }

    if (peek().type == TokenType::LPAREN) {
        step();  // '('
        std::unique_ptr<ASTNode> expr = parse_addition();
        expect(TokenType::RPAREN, "Expected ')' to end parenthesis");
        step();  // ')'
        return expr;
    }

    throw std::runtime_error("Syntax error! Reached end of primary_parser!");
}

void Parser::expect(TokenType type, const std::string& error_message) {
    if (peek().type == type) {
        return;
    }
    throw std::runtime_error(error_message);
}
