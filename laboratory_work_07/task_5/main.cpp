#include <iostream>
#include <chrono>
#include <cstring>

long long memo[55];

long long memoryFib(int n) {
    if (n <= 2) return 1;
    if (memo[n] != -1) return memo[n];
    return memo[n] = memoryFib(n - 1) + memoryFib(n - 2);
}

long long defaultFib(int n) {
    if (n <= 2) return 1;
    return defaultFib(n - 1) + defaultFib(n - 2);
}

int main() {
    int n = 50;

    std::memset(memo, -1, sizeof(memo));
    auto start1 = std::chrono::high_resolution_clock::now();
    long long res1 = memoryFib(n);
    auto end1 = std::chrono::high_resolution_clock::now();
    
    auto duration1 = std::chrono::duration_cast<std::chrono::seconds>(end1 - start1);

    auto start2 = std::chrono::high_resolution_clock::now();
    long long res2 = defaultFib(n);
    auto end2 = std::chrono::high_resolution_clock::now();
    
    auto duration2 = std::chrono::duration_cast<std::chrono::seconds>(end2 - start2);

    std::cout << "memoryFib(" << n << ") = " << res1 
    << " | Time: " << duration1.count() << " sec" << std::endl;
    std::cout << "defaultFib(" << n << ") = " << res2 
    << " | Time: " << duration2.count() << " sec" << std::endl;

    return 0;
}
