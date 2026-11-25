#include <chrono>
#include <iostream>
#include <random>
#include <utility>


static int partitionLomuto(int *a, const int l, const int r) {
    const int pivot = a[r];
    int i = l - 1;
    for (int j = l; j < r; ++j)
        if (a[j] <= pivot)
            std::swap(a[++i], a[j]);
    std::swap(a[i + 1], a[r]);
    return i + 1;
}


static void quickSort(int *a, const int l, const int r) {
    if (l >= r) return;
    const int p = partitionLomuto(a, l, r);
    quickSort(a, l, p - 1);
    quickSort(a, p + 1, r);
}


int main() {
    constexpr int N = 20000;
    const auto a = new int[N];
    std::mt19937 gen(time(nullptr));
    std::uniform_int_distribution dist(0, 1000000);

    for (const int n: {1000, 5000, 20000}) {
        for (int i = 0; i < n; ++i)
            a[i] = dist(gen);

        auto t1 = std::chrono::high_resolution_clock::now();
        quickSort(a, 0, n - 1);
        auto t2 = std::chrono::high_resolution_clock::now();

        std::cout << "quickSort N=" << n << ": "
                << std::chrono::duration<double, std::milli>(t2 - t1).count()
                << " ms" << std::endl;
    }
    delete[] a;
    return 0;
}
