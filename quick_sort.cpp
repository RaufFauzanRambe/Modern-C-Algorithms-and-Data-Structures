#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread> 

struct QuickSortTracker {
    int step = 0;

    template <typename T>
    void logSwap(int i, int j, const std::vector<T>& arr) {
        ++step;
        std::cout << "[Step " << step << "] Swap index " << i << " and " << j << ":\n";
        printArrayVisual(arr, i, j, -1);
    }

    template <typename T>
    void logPivot(int pivotIndex, const T& pivotValue, const std::vector<T>& arr) {
        ++step;
        std::cout << "[Step " << step << "] Pivot chosen at index " << pivotIndex 
                  << " (value: " << pivotValue << ")\n";
        printArrayVisual(arr, -1, -1, pivotIndex);
    }

    template <typename T>
    void printArrayVisual(const std::vector<T>& arr, int highlight1, int highlight2, int pivotIndex) {
        for (size_t i = 0; i < arr.size(); ++i) {
            if ((int)i == highlight1 || (int)i == highlight2) std::cout << "[" << arr[i] << "]";
            else if ((int)i == pivotIndex) std::cout << "{" << arr[i] << "}";
            else std::cout << " " << arr[i] << " ";
        }
        std::cout << "\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
    }
};

t
template <typename T>
int partition(std::vector<T>& arr, int low, int high, QuickSortTracker& tracker) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(low, high);
    int pivotIndex = dist(gen);
    std::swap(arr[pivotIndex], arr[high]); 
    tracker.logPivot(high, arr[high], arr);

    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
            tracker.logSwap(i, j, arr);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    tracker.logSwap(i + 1, high, arr);
    return i + 1;
}

template <typename T>
void quickSortVisual(std::vector<T>& arr, int low, int high, QuickSortTracker& tracker) {
    while (low < high) {
        int pivotIndex = partition(arr, low, high, tracker);
        if (pivotIndex - low < high - pivotIndex) {
            quickSortVisual(arr, low, pivotIndex - 1, tracker);
            low = pivotIndex + 1;
        } else {
            quickSortVisual(arr, pivotIndex + 1, high, tracker);
            high = pivotIndex - 1;
        }
    }
}

template <typename T>
void quickSortVisual(std::vector<T>& arr) {
    if (!arr.empty()) {
        QuickSortTracker tracker;
        quickSortVisual(arr, 0, arr.size() - 1, tracker);
    }
}

template <typename T>
void printArray(const std::vector<T>& arr) {
    for (const auto& el : arr) std::cout << el << " ";
    std::cout << "\n";
}

#ifdef QUICK_SORT_VISUAL_TEST
int main() {
    std::vector<int> data = {34, 7, 23, 32, 5, 62};
    std::cout << "Original array: ";
    printArray(data);

    quickSortVisual(data);

    std::cout << "Sorted array: ";
    printArray(data);
    return 0;
}
#endif
