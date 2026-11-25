#include <iostream>
#include <chrono>
#include <cstring>

static long long memo[55];

static long long memoryFib(const int n) {
    if (n <= 2) return 1;
    if (memo[n] != -1) return memo[n];
    return memo[n] = memoryFib(n - 1) + memoryFib(n - 2);
}

static long long defaultFib(const int n) {
    if (n <= 2) return 1;
    return defaultFib(n - 1) + defaultFib(n - 2);
}

int main() {
    constexpr int n = 50;

    std::memset(memo, -1, sizeof(memo));
    const auto start1 = std::chrono::high_resolution_clock::now();
    const long long res1 = memoryFib(n);
    const auto end1 = std::chrono::high_resolution_clock::now();

    const auto duration1 = std::chrono::duration_cast<std::chrono::seconds>(end1 - start1);

    const auto start2 = std::chrono::high_resolution_clock::now();
    const long long res2 = defaultFib(n);
    const auto end2 = std::chrono::high_resolution_clock::now();

    const auto duration2 = std::chrono::duration_cast<std::chrono::seconds>(end2 - start2);

    std::cout << "memoryFib(" << n << ") = " << res1
            << " | Time: " << duration1.count() << " sec" << std::endl;
    std::cout << "defaultFib(" << n << ") = " << res2
            << " | Time: " << duration2.count() << " sec" << std::endl;

    return 0;
}
