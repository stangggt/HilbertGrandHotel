#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "dynamic_array.h"
#include <functional>
#include <utility>

namespace algorithms {

    /**
     * @brief Partition helper function for QuickSort with median-of-three pivot.
     */
    template <typename T, typename Compare>
    int partition(DynamicArray<T>& arr, int low, int high, Compare comp) {
        // Median-of-three pivot selection (low, mid, high)
        int mid = low + (high - low) / 2;
        if (comp(arr[mid], arr[low])) std::swap(arr[low], arr[mid]);
        if (comp(arr[high], arr[low])) std::swap(arr[low], arr[high]);
        if (comp(arr[mid], arr[high])) std::swap(arr[mid], arr[high]);

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
     * @brief Recursive QuickSort with tail-call optimization: guarantees O(log N) stack depth.
     */
    template <typename T, typename Compare>
    void quickSortHelper(DynamicArray<T>& arr, int low, int high, Compare comp) {
        while (low < high) {
            int pi = partition(arr, low, high, comp);

            // Recurse into the smaller partition to limit stack depth to O(log N)
            if (pi - low < high - pi) {
                quickSortHelper(arr, low, pi - 1, comp);
                low = pi + 1;
            } else {
                quickSortHelper(arr, pi + 1, high, comp);
                high = pi - 1;
            }
        }
    }

    /**
     * @brief Custom QuickSort implementation: O(N log N) average, O(log N) call stack space.
     */
    template <typename T, typename Compare = std::less<T>>
    void quickSort(DynamicArray<T>& arr, Compare comp = Compare()) {
        if (arr.size() > 1) {
            quickSortHelper(arr, 0, static_cast<int>(arr.size()) - 1, comp);
        }
    }

    /**
     * @brief Custom Binary Search on sorted DynamicArray: O(log N) time complexity.
     * @return index of matched element, or -1 if not found.
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
     * @brief Linear Search on DynamicArray: O(N) baseline for empirical comparison.
     */
    template <typename T, typename KeyType, typename KeyExtractor>
    int linearSearch(const DynamicArray<T>& arr, const KeyType& targetKey, KeyExtractor keyExtractor) {
        for (size_t i = 0; i < arr.size(); ++i) {
            if (keyExtractor(arr[i]) == targetKey) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

} // namespace algorithms

#endif // ALGORITHMS_H
