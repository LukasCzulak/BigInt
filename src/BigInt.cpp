#include "BigInt.hpp"

BigInt::BigInt(int val) : value(val) {}

BigInt BigInt::operator+(const BigInt& other) const { return BigInt(this->value + other.value); }

int BigInt::toInt() const { return value; }
