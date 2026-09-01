#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "DynamicArray.hpp"
#include <functional>
#include <utility>

namespace Algorithms {

    /**
     * @brief Partition function for QuickSort.
     */
    template <typename T, typename Compare>
    int partition(DynamicArray<T>& arr, int low, int high, Compare comp) {
        T pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (comp(arr[j], pivot)) {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    /**
     * @brief Recursive QuickSort implementation (O(N log N) average).
     */
    template <typename T, typename Compare>
    void quickSortHelper(DynamicArray<T>& arr, int low, int high, Compare comp) {
        if (low < high) {
            int pi = partition(arr, low, high, comp);
            quickSortHelper(arr, low, pi - 1, comp);
            quickSortHelper(arr, pi + 1, high, comp);
        }
    }

    /**
     * @brief QuickSort entry point.
     */
    template <typename T, typename Compare = std::less<T>>
    void quickSort(DynamicArray<T>& arr, Compare comp = Compare()) {
        if (arr.size() > 1) {
            quickSortHelper(arr, 0, static_cast<int>(arr.size()) - 1, comp);
        }
    }

    /**
     * @brief InsertionSort implementation (O(N^2) worst, O(N) best).
     */
    template <typename T, typename Compare = std::less<T>>
    void insertionSort(DynamicArray<T>& arr, Compare comp = Compare()) {
        int n = static_cast<int>(arr.size());
        for (int i = 1; i < n; ++i) {
            T key = arr[i];
            int j = i - 1;
            while (j >= 0 && comp(key, arr[j])) {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = key;
        }
    }

    /**
     * @brief Binary search on an array sorted by key extractor.
     * @return index if found, or -1 if not found.
     */
    template <typename T, typename KeyType, typename KeyExtractor>
    int binarySearch(const DynamicArray<T>& arr, const KeyType& targetKey, KeyExtractor keyExtractor) {
        int low = 0;
        int high = static_cast<int>(arr.size()) - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            KeyType midKey = keyExtractor(arr[mid]);

            if (midKey == targetKey) {
                return mid;
            }
            if (midKey < targetKey) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1;
    }

    /**
     * @brief Linear filter returning a new DynamicArray with elements satisfying predicate.
     */
    template <typename T, typename Predicate>
    DynamicArray<T> filter(const DynamicArray<T>& arr, Predicate pred) {
        DynamicArray<T> result;
        for (size_t i = 0; i < arr.size(); ++i) {
            if (pred(arr[i])) {
                result.push_back(arr[i]);
            }
        }
        return result;
    }

    /**
     * @brief Linear search returning index of first element matching predicate, or -1.
     */
    template <typename T, typename Predicate>
    int findIndex(const DynamicArray<T>& arr, Predicate pred) {
        for (size_t i = 0; i < arr.size(); ++i) {
            if (pred(arr[i])) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

} // namespace Algorithms

#endif // ALGORITHMS_HPP
