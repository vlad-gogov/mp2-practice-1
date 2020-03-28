#include <iostream>
#include <random>
#include "TArrayController.h"

constexpr int size = 10;

int main()
{
    std::random_device rd;
    std::mt19937 generator(rd()); // Mersenne

    int arr[size] = { 0 };
    for (int i = 0; i < size; i++)
    {
        arr[i] = static_cast<int>(generator() % 1000U);
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';

    TArrayController::heapSort(arr, size);
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << ' ';
    std::cout << '\n';
}