#pragma once
#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

class BigInt {
private:
    /*
    Little endian
    Example: Number "1234" will be [4,3,2,1]
    */
    std::vector<uint8_t> digits;

public:
    // Constructors
    BigInt(uint8_t val = 0);
    BigInt(const std::string& val);

    // Destructor
    ~BigInt() = default;

    // Copy Constructor
    BigInt(const BigInt& other) = default;

    // Copy assignment operator
    BigInt& operator=(const BigInt& other) = default;

    // Move constructor
    BigInt(BigInt&& other) noexcept = default;

    // Move Assignment operator
    BigInt& operator=(BigInt&& other) noexcept = default;

    // add operator overload
    BigInt operator+(const BigInt& other) const;

    // mult operator overload
    BigInt operator*(const BigInt& other) const;

    /// @brief function used to access digits.
    /// @param index the index in the number.
    /// @return the digit at @p index or 0 if out of bounds.
    uint8_t get_digit(size_t index) const;

    /// @brief function to get the number of digits in the number.
    /// @return the number of digits.
    size_t num_digits() const;

    /// @brief removed leading zeros.
    void normalize();

    /// @brief extends the vector to have @p num_digits digits after the call by adding leading zeros.
    /// @param num_digits the amount of digits wanted after calling this function.
    /// @attention only extends! Cannot make the number smaller than before!
    void set_number_of_digits(size_t num_digits);

    /// @brief tries to fit the number into a single ints.
    /// @return this number as an int.
    /// @attention Not safe for large numbers!
    int toInt() const;
};
