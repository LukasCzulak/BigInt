#include <iostream>

int main() {
    int x = 69;
    std::cout << "value of x before: " << x << std::endl;
    int* x_p = &x;
    *x_p = 0;
    std::cout << "value of x after: " << x << std::endl;
    return x;
}
