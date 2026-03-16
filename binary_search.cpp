#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

template <typename T>
int binarySearchIterative(const std::vector<T>& arr, T target) {
    if(arr.empty()) return -1;
    int left = 0, right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

template <typename T>
int binarySearchRecursive(const std::vector<T>& arr, T target, int left, int right) {
    if(left > right || arr.empty()) return -1;

    int mid = left + (right - left) / 2;
    if (arr[mid] == target)
        return mid;
    else if (arr[mid] < target)
        return binarySearchRecursive(arr, target, mid + 1, right);
    else
        return binarySearchRecursive(arr, target, left, mid - 1);
}

// STL version using lower_bound
template <typename T>
int binarySearchSTL(const std::vector<T>& arr, T target) {
    if(arr.empty()) return -1;
    auto it = std::lower_bound(arr.begin(), arr.end(), target);
    if(it != arr.end() && *it == target)
        return it - arr.begin();
    return -1;
}

int main() {
    std::vector<int> data = {1,3,5,7,9,11,13,15};

    int target;
    std::cout << "Enter number to search: ";
    std::cin >> target;

    int idxIter = binarySearchIterative(data, target);
    int idxRec = binarySearchRecursive(data, target, 0, data.size()-1);
    int idxSTL = binarySearchSTL(data, target);

    std::cout << "\nResults:\n";
    std::cout << "Iterative: " << (idxIter != -1 ? std::to_string(idxIter) : "Not found") << "\n";
    std::cout << "Recursive: " << (idxRec != -1 ? std::to_string(idxRec) : "Not found") << "\n";
    std::cout << "STL: " << (idxSTL != -1 ? std::to_string(idxSTL) : "Not found") << "\n";

    return 0;
}