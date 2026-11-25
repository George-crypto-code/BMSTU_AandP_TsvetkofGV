#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>
#include <fstream>
#include <string>


static void pprint(double array[], const int size, std::ofstream &file) {
    file << std::fixed << std::setprecision(5);
    file << "[";
    for (int i = 0; i < size - 1; i++)
        file << ((i % 5 == 0 && i != 0) ? "\n " : "")
                << std::setw(8) << std::right << array[i] << "...  ";

    file << (((size - 1) % 5 == 0) ? "\n " : "") << std::setw(8)
            << std::right << array[size - 1] << "...]" << std::endl;
}


static double mean(const double array[], const int size) {
    double s = 0;
    for (int i = 0; i < size; i++) s += array[i];
    return s / size;
}


static double sumSquSub(double array[], const int size, const double mean) {
    double s = 0;
    for (int i = 0; i < size; i++)
        s += std::pow(array[i] - mean, 2);
    return s;
}


static void sort(double array[], const int size) {
    for (int j = 0; j < size; j++)
        for (int i = 0; i < size - 1; i++)
            if (array[i + 1] > array[i]) {
                const double temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
}


int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution distrib(-5., 5.);

    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) return 1;
    std::string line;
    std::getline(inputFile, line);
    int n = std::stoi(line);
    inputFile.close();
    if (n < 0 || n > 30) return 1;
    double array[n];

    for (int i = 0; i < n; i++) array[i] = distrib(gen);

    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) return 1;

    double mn = mean(array, n);

    outputFile << "start array:" << std::endl;
    pprint(array, n, outputFile);

    outputFile << std::setprecision(5) << "\n\nMean of array: \n"
            << mn << "..." << std::endl;

    outputFile << std::setprecision(5)
            << "\n\nSum of square's subtraction: \n"
            << sumSquSub(array, n, mn) << "..." << std::endl;

    sort(array, n);
    for (int i = 0; i < n; i++) array[i] -= mn;

    outputFile << "\n\nSorted array:" << std::endl;
    pprint(array, n, outputFile);

    outputFile.close();
    return 0;
}
