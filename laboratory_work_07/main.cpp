#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>


void printNumpyStyle(const std::vector<int>& vec) 
{
    if (vec.size() < 8) 
    {
        for (int x : vec) std::cout << x << ' ';
        std::cout << std::endl;
        return;
    }
    std::cout << '[';
    for (int i = 0; i < 4; ++i) std::cout << vec[i] << ' ';
    std::cout << "... ";
    for (size_t i = vec.size() - 4; i < vec.size(); ++i)
        std::cout << vec[i] << (i + 1 < vec.size() ? " " : "");
    std::cout << "]\n";
}


std::vector<int> mergeSort(const std::vector<int>& array) 
{
    size_t size = array.size();
    if (size <= 1) return array;

    size_t mid = size / 2;
    
    std::vector<int> first_part(array.begin(), array.begin() + mid);
    std::vector<int> second_part(array.begin() + mid, array.end());

    std::vector<int> sorted_first = mergeSort(first_part);
    std::vector<int> sorted_second = mergeSort(second_part);

    std::vector<int> sorted_array;
    sorted_array.reserve(size);

    size_t i = 0;
    size_t j = 0;

    while (i < sorted_first.size() && j < sorted_second.size()) 
    {
        if (sorted_first[i] <= sorted_second[j]) 
        {
            sorted_array.push_back(sorted_first[i]);
            i++;
        } 
        else 
        {
            sorted_array.push_back(sorted_second[j]);
            j++;
        }
    }

    while (i < sorted_first.size())
        sorted_array.push_back(sorted_first[i++]);
    
    while (j < sorted_second.size())
        sorted_array.push_back(sorted_second[j++]);

    return sorted_array;
}


int partitionLomuto(std::vector<int>& a, int l, int r) 
{
    int pivot = a[r];
    int i = l - 1;
    for (int j = l; j < r; ++j)
        if (a[j] <= pivot) std::swap(a[++i], a[j]);
    std::swap(a[i + 1], a[r]);
    return i + 1;
}


void quickSort(std::vector<int>& a, int l, int r) 
{
    if (l >= r) return;
    int p = partitionLomuto(a, l, r);
    quickSort(a, l, p - 1);
    quickSort(a, p + 1, r);
}


int main() 
{
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(0, 1000000000);
    
    const int size = 1000177;
    std::vector<int> base_array;
    base_array.reserve(size);
    for (int i = 0; i < size; i++) base_array.push_back(dist(gen));

    std::cout << "Start array:       ";
    printNumpyStyle(base_array);

    std::vector<int> array_merge = base_array;
    auto start_merge = std::chrono::high_resolution_clock::now();
    array_merge = mergeSort(array_merge);
    auto end_merge = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_merge = end_merge - start_merge;

    std::vector<int> array_quick = base_array;
    auto start_quick = std::chrono::high_resolution_clock::now();
    quickSort(array_quick, 0, size - 1);
    auto end_quick = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_quick = end_quick - start_quick;

    std::cout << "MergeSort result:  ";
    printNumpyStyle(array_merge);
    std::cout << "Time mergeSort:   " << elapsed_merge.count() << " sec\n\n";

    std::cout << "QuickSort result:  ";
    printNumpyStyle(array_quick);
    std::cout << "Time quickSort:   " << elapsed_quick.count() << " sec\n";

    return 0;
}