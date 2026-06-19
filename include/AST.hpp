#pragma once
#include <memory>

#include "BigInt.hpp"

/// @brief Base class for all AST nodes
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual BigInt evaluate() const = 0;
};

/// @brief BigInt leaf node
class NumberNode : public ASTNode {
private:
    BigInt value;

public:
    NumberNode(const BigInt& val) : value(val) {}
    BigInt evaluate() const override { return value; }
};

/// @brief Node to store an addition
class AddNode : public ASTNode {
private:
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;

public:
    AddNode(std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r)
        : left(std::move(l)), right(std::move(r)) {}

    BigInt evaluate() const override {
        return left->evaluate() + right->evaluate();
    }
};

/// @brief Node to store a multiplication
class MultNode : public ASTNode {
private:
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;

public:
    MultNode(std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r)
        : left(std::move(l)), right(std::move(r)) {}

    BigInt evaluate() const override {
        return left->evaluate() * right->evaluate();
    }
};
