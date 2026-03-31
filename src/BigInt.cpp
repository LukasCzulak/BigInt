#include "BigInt.hpp"

BigInt::BigInt(uint8_t val) {
    while (val != 0) {
        this->digits.push_back(val % 10);
        val /= 10;
    }
}

BigInt::BigInt(const std::string& val) {
    // reserve at the start to avoid multiple reallocs
    digits.reserve(val.size());

    for (auto it = val.rbegin(); it != val.rend(); ++it) {
        const char c = *it;

        if (c >= '0' && c <= '9') {
            digits.push_back(static_cast<uint8_t>(c - '0'));
        } else {
            throw std::invalid_argument("Encountered non digits in string constructor!");
        }
    }

    this->normalize();
}

// Safely gets a digit, or returns 0 if we've read past the end of the number
uint8_t BigInt::get_digit(size_t index) const {
    if (index < this->digits.size()) {
        return this->digits[index];
    }
    return 0;
}

// sets number of digits in the number by adding leading zeros
void BigInt::set_number_of_digits(size_t numDigits) {
    if (numDigits > this->digits.size()) {
        this->digits.resize(numDigits, 0);  // Fills up to numDigits with 0s
    }
}

// safely removes any leading zeros in the number
void BigInt::normalize() {
    while (!(this->digits.empty()) && this->digits.back() == 0) {
        this->digits.pop_back();
    }
}

// returns the number of digits
size_t BigInt::num_digits() const { return this->digits.size(); }

BigInt BigInt::operator+(const BigInt& other) const {
    BigInt res;
    uint8_t carry = 0;

    // Find out which number has more digits
    size_t maxSize = std::max(this->num_digits(), other.num_digits());

    // loop from lowest digit to highest
    for (size_t i = 0; i < maxSize; ++i) {
        uint8_t sum = this->get_digit(i) + other.get_digit(i) + carry;

        carry = sum / 10;
        res.digits.push_back(sum % 10);
    }

    // last carry
    if (carry > 0) {
        res.digits.push_back(carry);
    }

    return res;
}

BigInt BigInt::operator*(const BigInt& other) const {
    BigInt res;

    // Result cannot have more than this digits
    const size_t total_size_max = this->num_digits() + other.num_digits();

    res.set_number_of_digits(total_size_max);

    // loop through every digit in the first number: Outer loop
    for (size_t i = 0; i < this->num_digits(); ++i) {
        // I use a carry for the addition within the inner loop
        uint8_t carry = 0;
        const uint8_t digit_outer = this->get_digit(i);

        for (size_t j = 0; j < other.num_digits(); ++j) {
            const uint8_t digit_inner = other.get_digit(j);
            const uint8_t previous_digit = res.get_digit(i + j);

            // new digit is digits from original numbers multiplied + carry from inner loop + carry between loop
            const uint8_t new_digit = digit_outer * digit_inner + carry + previous_digit;
            carry = new_digit / 10;  // split number
            res.digits[i + j] = new_digit % 10;
        }
        res.digits[i + other.num_digits()] = carry;  // after each loop store the carry for the next loop
    }

    res.normalize();  // possible leading zeros
    return res;
}

int BigInt::toInt() const {
    int acc = 0;
    int multiplier = 1;
    for (const uint8_t digit : this->digits) {
        acc += digit * multiplier;
        multiplier *= 10;
    }
    return acc;
}
