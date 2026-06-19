#include "Lexer.hpp"

bool Lexer::is_whitespace(char c) const {
    return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

bool Lexer::is_digit(char c) const { return c >= '0' && c <= '9'; }

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    size_t i = 0;

    // basic loop to go through the whole text
    while (i < text.length()) {
        char c = text[i];

        if (is_whitespace(c)) {  // whitespaces are just ignored
            i++;
        } else if (c == '+') {
            tokens.push_back({TokenType::PLUS, "+"});
            i++;
        } else if (c == '*') {
            tokens.push_back({TokenType::MULT, "*"});
            i++;
        } else if (c == '(') {
            tokens.push_back({TokenType::LPAREN, "("});
            i++;
        } else if (c == ')') {
            tokens.push_back({TokenType::RPAREN, ")"});
            i++;
        } else if (is_digit(c)) {
            // BigInt literal was found. Put chars in the number_str until we
            // are done
            std::string number_str = "";
            while (i < text.length() && is_digit(text[i])) {
                number_str += text[i];
                i++;
            }
            const Token number_token = {TokenType::NUMBER, number_str,
                                        BigInt(number_str)};
            tokens.push_back(number_token);
        } else {
            // Something unexpected
            tokens.push_back({TokenType::INVALID, ""});
            i++;
        }
    }

    // Always put a EOF at the end
    tokens.push_back({TokenType::END_OF_FILE, ""});
    return tokens;
}
