#pragma once

class BigInt {
private:
    int value;  // temporary dummy

public:
    // Constructor
    BigInt(int val = 0);

    // simply add operator overload
    BigInt operator+(const BigInt& other) const;

    // helper for first tests
    int toInt() const;
};
