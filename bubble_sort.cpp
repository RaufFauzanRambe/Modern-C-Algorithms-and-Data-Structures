#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

template <typename T>
struct SortStats {
    long long comparisons = 0;
    long long swaps = 0;
};

template <typename T>
SortStats<T> bubbleSort(vector<T>& arr) {
    SortStats<T> stats;
    size_t n = arr.size();

    for (size_t i = 0; i < n - 1; i++) {
        bool swapped = false;

        for (size_t j = 0; j < n - i - 1; j++) {
            stats.comparisons++;

            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                stats.swaps++;
                swapped = true;
            }
        }

        if (!swapped) break; // optimization
    }

    return stats;
}

template <typename T>
void printVector(const vector<T>& arr) {
    for (const auto& v : arr)
        cout << v << " ";
    cout << endl;
}

vector<int> generateRandomData(size_t n) {
    vector<int> data(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 1000);

    for (auto& v : data)
        v = dist(gen);

    return data;
}

int main() {

    size_t size = 15;

    vector<int> data = generateRandomData(size);

    cout << "Original Data:\n";
    printVector(data);

    auto start = chrono::high_resolution_clock::now();

    auto stats = bubbleSort(data);

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> duration = end - start;

    cout << "\nSorted Data:\n";
    printVector(data);

    cout << "\nStatistics:\n";
    cout << "Comparisons : " << stats.comparisons << endl;
    cout << "Swaps       : " << stats.swaps << endl;
    cout << "Time (ms)   : " << duration.count() << endl;

    return 0;
}