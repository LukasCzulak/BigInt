#include <iostream>

#include "BigInt.hpp"

int main() {
    BigInt a(0);
    BigInt b("123");
    std::cout << "value of a before: " << a.toInt() << std::endl;
    a = BigInt(a.toInt() + b.toInt());
    std::cout << "value of a after: " << a.toInt() << std::endl;

    return 0;
}
