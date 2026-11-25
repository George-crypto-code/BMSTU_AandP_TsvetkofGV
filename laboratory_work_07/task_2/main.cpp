#include <iostream>


static int moves = 0;

static void hanoi(const int n, const int from, const int to, const int via) {
    if (n == 0)
        return;
    hanoi(n - 1, from, via, to);
    std::cout << from << " -> " << to << "\n";
    ++moves;
    hanoi(n - 1, via, to, from);
}

int main() {
    int n;
    std::cout << "Enter n: ";
    if (!(std::cin >> n) || n < 1) {
        std::cout << "Incorrect input: " << std::endl;
        return 1;
    }

    hanoi(n, 1, 3, 2);

    long long expect = (1LL << n) - 1; // 2^n - 1
    std::cout << "All steps: " << moves
            << " (expect 2^n - 1 = " << expect << ")" << std::endl;

    return 0;
}
