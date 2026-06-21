#pragma once
#include <memory>

#include "AST.hpp"
#include "Token.hpp"

class Parser {
private:
    std::vector<Token> tokens;
    size_t current = 0;

    /// @brief returns the next token. If this is called when at the end, it
    /// will simply return another end token
    Token peek() const;

    /// @brief advances the internal current position
    void step();

    /// @brief using recursive descent parsing, starts parsing at addition
    /// precedence level
    std::unique_ptr<ASTNode> parse_addition();

    /// @brief using recursive descent parsing, starts parsing at multiplication
    /// precedence level
    std::unique_ptr<ASTNode> parse_multiplication();

    /// @brief using recursive descent parsing, starts parsing at atomic
    /// expression precedence level
    std::unique_ptr<ASTNode> parse_primary();

    /// @brief checks if the next token is of the expected @p type. If not,
    /// throws the @p error_message
    void expect(TokenType type, const std::string& error_message);

public:
    Parser(std::vector<Token> ts) : tokens(ts) {}
    ~Parser() = default;

    /// @brief entry point of the parser. This then starts the actual parsing
    /// using recursive descent.
    std::unique_ptr<ASTNode> parse();
};
