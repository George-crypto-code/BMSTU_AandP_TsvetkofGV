#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdlib>
#include <iomanip>


static void selectionSort(std::vector<int> &a) {
    int n = static_cast<int>(a.size());
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j)
            if (a[j] < a[minIdx]) minIdx = j;
        if (minIdx != i) std::swap(a[i], a[minIdx]);
    }
}


static void bubbleSort(std::vector<int> &a) {
    int n = static_cast<int>(a.size());
    bool swapped = true;
    for (int pass = 0; swapped && pass < n - 1; ++pass) {
        swapped = false;
        for (int j = 0; j < n - 1 - pass; ++j)
            if (a[j] > a[j + 1]) {
                std::swap(a[j], a[j + 1]);
                swapped = true;
            }
    }
}


static void insertionSort(std::vector<int> &a) {
    int n = static_cast<int>(a.size());
    for (int i = 1; i < n; ++i) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}


static void selectionSort_(std::vector<int> &a, long long &comparisons, long long &swaps) {
    comparisons = 0;
    swaps = 0;
    int n = static_cast<int>(a.size());
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            comparisons++;
            if (a[j] < a[minIdx]) minIdx = j;
        }
        if (minIdx != i) {
            std::swap(a[i], a[minIdx]);
            swaps++;
        }
    }
}


static void bubbleSort_(std::vector<int> &a, long long &comparisons, long long &swaps) {
    comparisons = 0;
    swaps = 0;
    int n = static_cast<int>(a.size());
    bool swapped = true;
    for (int pass = 0; swapped && pass < n - 1; ++pass) {
        swapped = false;
        for (int j = 0; j < n - 1 - pass; ++j) {
            comparisons++;
            if (a[j] > a[j + 1]) {
                std::swap(a[j], a[j + 1]);
                swaps++;
                swapped = true;
            }
        }
    }
}


static void insertionSort_(std::vector<int> &a, long long &comparisons, long long &swaps) {
    comparisons = 0;
    swaps = 0;
    int n = static_cast<int>(a.size());
    for (int i = 1; i < n; ++i) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0) {
            comparisons++;
            if (a[j] > key) {
                a[j + 1] = a[j];
                swaps++; // считаем сдвиг элемента как операцию перемещения
                j--;
            } else {
                break;
            }
        }
        a[j + 1] = key;
    }
}


static bool isSorted(const std::vector<int> &a) {
    for (std::size_t i = 1; i < a.size(); ++i)
        if (a[i - 1] > a[i])
            return false;
    return true;
}


static std::vector<int> randomArray(const int n,
                                    const unsigned seed, const float percent = 1.) {
    if (n <= 0) return {};
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(0, 100);
    std::vector<int> a(n);
    for (auto &elem: a) elem = dist(gen);
    if (percent >= 0.9) return a;

    std::uniform_int_distribution<int> index(0, n - 1);
    std::sort(std::begin(a), std::end(a));
    const int pairs = n * static_cast<int>(percent / 2);
    for (int i = 0; i < pairs; i++)
        std::swap(a[index(gen)], a[index(gen)]);
    return a;
}


static double timeSort(void (*sortFn)(std::vector<int> &),
                       const std::vector<int> &src) {
    std::vector<int> a = src;
    auto t0 = std::chrono::steady_clock::now();
    sortFn(a);
    auto t1 = std::chrono::steady_clock::now();
    if (!isSorted(a)) {
        std::cerr << "ОШИБКА: массив не отсортирован!" << std::endl;
        std::exit(1);
    }
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}


static void testFullRandomArray() {
    constexpr int sizes[] = {1000, 5000, 10000};

    std::cout << "    <<======== Full random array ========>>" << std::endl;
    std::cout << "--------+------------+------------+------------" << std::endl;
    std::cout << "n      " << " | "
            << std::setw(10) << "selection " << " | "
            << std::setw(10) << "bubble    " << " | "
            << std::setw(10) << "insert    " << std::endl;
    std::cout << "--------+------------+------------+------------" << std::endl;

    std::cout << std::fixed << std::setprecision(2);

    for (const int n: sizes) {
        constexpr int runs = 5;
        std::vector<int> fullRandomArray = randomArray(n, time(nullptr));
        double t1 = 0, t2 = 0, t3 = 0;
        for (int k = 0; k < runs; k++) {
            t1 += timeSort(selectionSort, fullRandomArray);
            t2 += timeSort(bubbleSort, fullRandomArray);
            t3 += timeSort(insertionSort, fullRandomArray);
        }
        std::cout << std::setw(7) << n << " | "
                << std::setw(10) << t1 / runs << " | "
                << std::setw(10) << t2 / runs << " | "
                << std::setw(10) << t3 / runs << std::endl;
    }
    std::cout << "--------+------------+------------+------------" << std::endl;
    std::cout << "    <<======== - - - - - - - - - ========>>\n\n\n";
}


static void testHalfRandomArray() {
    constexpr int sizes[] = {1000, 5000, 10000};

    std::cout << "    <<======== Half random array ========>>" << std::endl;
    std::cout << "--------+------------+------------+------------" << std::endl;
    std::cout << "n      " << " | "
            << std::setw(10) << "selection " << " | "
            << std::setw(10) << "bubble    " << " | "
            << std::setw(10) << "insert    " << std::endl;
    std::cout << "--------+------------+------------+------------" << std::endl;

    std::cout << std::fixed << std::setprecision(2);

    for (const int n: sizes) {
        constexpr int runs = 5;
        std::vector<int> halfRandomArray = randomArray(n, time(nullptr), 0.5);
        double t1 = 0, t2 = 0, t3 = 0;
        for (int k = 0; k < runs; k++) {
            t1 += timeSort(selectionSort, halfRandomArray);
            t2 += timeSort(bubbleSort, halfRandomArray);
            t3 += timeSort(insertionSort, halfRandomArray);
        }
        std::cout << std::setw(7) << n << " | "
                << std::setw(10) << t1 / runs << " | "
                << std::setw(10) << t2 / runs << " | "
                << std::setw(10) << t3 / runs << std::endl;
    }
    std::cout << "--------+------------+------------+------------" << std::endl;
    std::cout << "    <<======== - - - - - - - - - ========>>\n\n\n";
}


static void testBitRandomArray() {
    constexpr int sizes[] = {1000, 5000, 10000};

    std::cout << "    <<========= Bit random array ========>>" << std::endl;
    std::cout << "--------+------------+------------+------------" << std::endl;
    std::cout << "n      " << " | "
            << std::setw(10) << "selection " << " | "
            << std::setw(10) << "bubble    " << " | "
            << std::setw(10) << "insert    " << std::endl;
    std::cout << "--------+------------+------------+------------" << std::endl;

    std::cout << std::fixed << std::setprecision(2);

    for (const int n: sizes) {
        constexpr int runs = 5;
        std::vector<int> bitRandomArray = randomArray(n, time(nullptr), 0.1);
        double t1 = 0, t2 = 0, t3 = 0;
        for (int k = 0; k < runs; k++) {
            t1 += timeSort(selectionSort, bitRandomArray);
            t2 += timeSort(bubbleSort, bitRandomArray);
            t3 += timeSort(insertionSort, bitRandomArray);
        }
        std::cout << std::setw(7) << n << " | "
                << std::setw(10) << t1 / runs << " | "
                << std::setw(10) << t2 / runs << " | "
                << std::setw(10) << t3 / runs << std::endl;
    }
    std::cout << "--------+------------+------------+------------" << std::endl;
    std::cout << "    <<======== - - - - - - - - - ========>>\n\n\n";
}


static void operationsTest() {
    constexpr int n = 10000;

    const std::vector<int> src = randomArray(n, time(nullptr));
    long long c1 = 0, s1 = 0;
    long long c2 = 0, s2 = 0;
    long long c3 = 0, s3 = 0;

    std::vector<int> a1 = src;
    selectionSort_(a1, c1, s1);

    std::vector<int> a2 = src;
    bubbleSort_(a2, c2, s2);

    std::vector<int> a3 = src;
    insertionSort_(a3, c3, s3);

    std::cout << "     <<======= Operations count =======>>" << std::endl;
    std::cout << "--------+------------+------------+------------" << std::endl;
    std::cout << "        | selection  | bubble     | insert     " << std::endl;
    std::cout << "--------+------------+------------+------------" << std::endl;

    std::cout << "comp   " << " | "
            << std::setw(10) << c1 << " | "
            << std::setw(10) << c2 << " | "
            << std::setw(10) << c3 << std::endl;

    std::cout << "swaps  " << " | "
            << std::setw(10) << s1 << " | "
            << std::setw(10) << s2 << " | "
            << std::setw(10) << s3 << std::endl;

    std::cout << "--------+------------+------------+------------" << std::endl;
    std::cout << "     <<======== - - - - - - - - - ========>>\n\n\n";
}


static long long digitSum(const long long x) {
    if (x < 10)
        return x;
    return x % 10 + digitSum(x / 10);
}


static bool compare(const long long current, const long long next) {
    return current > next;
}


static bool digit(const long long current, const long long next) {
    if (digitSum(current) > digitSum(next)) return true;
    if (digitSum(current) == digitSum(next)) return current > next;
    return false;
}


template<typename Compare>

static void bubbleSortKey(std::vector<int> &src, Compare key) {
    const auto size = src.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (key(src[j], src[j + 1]))
                std::swap(src[j], src[j + 1]);
        }
    }
}


int main() {
    // testFullRandomArray();
    // testHalfRandomArray();
    // testBitRandomArray();
    // operationsTest();
    constexpr int n = 5;
    std::vector src = {11, 2, 15, 20, 100};
    bubbleSortKey(src, digit);
    for (int i = 0; i < n; i++) std::cout << src[i] << " ";
    std::cout << std::endl;
    return 0;
}
