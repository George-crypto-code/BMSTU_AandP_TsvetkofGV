#include <iostream>


static long long factorial(const int n) {
    if (n <= 1)
        return 1;
    return n * factorial(n - 1);
}


static long long digitSum(const long long x) {
    if (x < 10)
        return x;
    return x % 10 + digitSum(x / 10);
}


int main() {
    int n;
    std::cout << "Enter n: ";
    if (!(std::cin >> n) || n < 0) {
        std::cout << "Incorrect input!" << std::endl;
        return 1;
    }
    std::cout << "factorial(" << n << ") = " << factorial(n) << std::endl;

    long long x;
    std::cout << "Enter some number: ";
    if (!(std::cin >> x) || x <= 0) {
        std::cout << "Incorrect input!" << std::endl;
        return 1;
    }
    std::cout << "Sum of digits: " << digitSum(x) << std::endl;
    return 0;
}
