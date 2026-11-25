#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <iomanip>


static std::vector<std::vector<int> > makeMatrix(const int n) {
    std::vector<std::vector<int> > matrix;
    for (int i = 0; i < n; i++) {
        std::vector<int> row;
        for (int j = 0; j < n; j++)
            row.push_back(std::pow(n * i + j + 1, 2));
        matrix.push_back(row);
    }
    return matrix;
}


static void print(const std::vector<std::vector<int> > &matrix) {
    int max = 0;
    for (const auto &row: matrix)
        for (const int elem: row)
            if (std::abs(elem) > max)
                max = std::abs(elem);

    const int max_width = std::to_string(max).length();

    std::cout << "[" << std::endl;
    for (int i = 0; i < matrix.size(); ++i) {
        std::cout << " [";
        for (int j = 0; j < matrix[i].size(); ++j) {
            std::cout << std::right << std::setw(max_width) << matrix[i][j];
            if (j < matrix[i].size() - 1) std::cout << " ";
        }
        std::cout << "]";
        if (i < matrix.size() - 1) std::cout << "," << std::endl;
        else std::cout << std::endl;
    }
    std::cout << "]" << std::endl;
}


static int sumDiagonal(const std::vector<std::vector<int> > &matrix) {
    int sum = 0;
    for (int i = 0; i < matrix.size(); i++) sum += matrix[i][i];
    return sum;
}


int main() {
    int size;
    std::cout << "Enter size of matrix: ";
    std::cin >> size;
    const std::vector<std::vector<int> > matrix = makeMatrix(size);
    std::cout << "Input matrix:\n";
    print(matrix);
    std::cout << "Sum of main diagonal:\n"
            << sumDiagonal(matrix) << std::endl;
    return 0;
}
