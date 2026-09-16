// ============================================================================
//  benchmark_dsa.cpp — Academic Data Structure & Algorithm Benchmarking Suite
//  Hilbert Grand Hotel & Resort
// ============================================================================

#include "../include/dynamic_array.h"
#include "../include/algorithms.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <string>
#include <iomanip>
#include <algorithm>

struct BenchmarkBooking {
    int bookingId;
    int roomId;
    int price;
    std::string guestName;
    std::string checkInDate;

    bool operator<(const BenchmarkBooking& other) const {
        return price < other.price;
    }
};

using Clock = std::chrono::high_resolution_clock;

static double toMilliseconds(Clock::time_point start, Clock::time_point end) {
    return std::chrono::duration<double, std::milli>(end - start).count();
}

int main() {
    std::cout << "\033[1;36m====================================================================\033[0m\n";
    std::cout << "\033[1;36m HILBERT GRAND HOTEL — ACADEMIC DSA BENCHMARKING SUITE\033[0m\n";
    std::cout << "\033[1;36m====================================================================\033[0m\n";
    std::cout << "Dataset Size: \033[1;33m100,000 synthetic booking records\033[0m\n";
    std::cout << "Compiler: GCC/G++ with -O2 optimization\n";
    std::cout << "Data Structures: Custom DynamicArray<T> vs std::vector<T>\n";
    std::cout << "Algorithms: Custom QuickSort vs std::sort, BinarySearch vs Linear\n";
    std::cout << "--------------------------------------------------------------------\n\n";

    constexpr size_t N = 100000;
    std::mt19937 rng(1337); // deterministic seed for reproducibility
    std::uniform_int_distribution<int> roomDist(101, 599);
    std::uniform_int_distribution<int> priceDist(1200, 15000);
    std::uniform_int_distribution<int> dayDist(1, 28);

    // ------------------------------------------------------------------------
    // BENCHMARK 1: DynamicArray vs std::vector (100k Insertions & Traversal)
    // ------------------------------------------------------------------------
    std::cout << "\033[1;35m[1/3] BENCHMARKING DYNAMIC ALLOCATION & SEQUENTIAL ACCESS (N = 100,000)\033[0m\n";

    // 1.1 Custom DynamicArray push_back
    auto t1 = Clock::now();
    DynamicArray<BenchmarkBooking> customArr;
    for (size_t i = 0; i < N; ++i) {
        customArr.push_back({
            static_cast<int>(i + 1),
            roomDist(rng),
            priceDist(rng),
            "Guest_" + std::to_string(i),
            "2026-10-" + std::to_string(dayDist(rng))
        });
    }
    auto t2 = Clock::now();
    double customPushMs = toMilliseconds(t1, t2);

    // 1.2 std::vector push_back
    rng.seed(1337);
    auto t3 = Clock::now();
    std::vector<BenchmarkBooking> stlVec;
    for (size_t i = 0; i < N; ++i) {
        stlVec.push_back({
            static_cast<int>(i + 1),
            roomDist(rng),
            priceDist(rng),
            "Guest_" + std::to_string(i),
            "2026-10-" + std::to_string(dayDist(rng))
        });
    }
    auto t4 = Clock::now();
    double stlPushMs = toMilliseconds(t3, t4);

    // 1.3 Custom DynamicArray Traversal
    auto t5 = Clock::now();
    long long customTotalRev = 0;
    for (size_t i = 0; i < customArr.size(); ++i) {
        customTotalRev += customArr[i].price;
    }
    auto t6 = Clock::now();
    double customScanMs = toMilliseconds(t5, t6);

    // 1.4 std::vector Traversal
    auto t7 = Clock::now();
    long long stlTotalRev = 0;
    for (size_t i = 0; i < stlVec.size(); ++i) {
        stlTotalRev += stlVec[i].price;
    }
    auto t8 = Clock::now();
    double stlScanMs = toMilliseconds(t7, t8);

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "  • DynamicArray::push_back(100k): \033[32m" << customPushMs << " ms\033[0m\n";
    std::cout << "  • std::vector::push_back(100k):  \033[34m" << stlPushMs << " ms\033[0m\n";
    std::cout << "  • DynamicArray Linear Scan:      \033[32m" << customScanMs << " ms\033[0m (Sum = " << customTotalRev << ")\n";
    std::cout << "  • std::vector Linear Scan:       \033[34m" << stlScanMs << " ms\033[0m (Sum = " << stlTotalRev << ")\n\n";

    // ------------------------------------------------------------------------
    // BENCHMARK 2: Custom QuickSort vs std::sort (Sorting 100,000 Records)
    // ------------------------------------------------------------------------
    std::cout << "\033[1;35m[2/3] BENCHMARKING SORTING ALGORITHMS (N = 100,000)\033[0m\n";

    DynamicArray<BenchmarkBooking> sortCustom = customArr;
    std::vector<BenchmarkBooking> sortStl = stlVec;

    // 2.1 Custom QuickSort by price
    auto ts1 = Clock::now();
    algorithms::quickSort(sortCustom, [](const BenchmarkBooking& a, const BenchmarkBooking& b) {
        return a.price < b.price;
    });
    auto ts2 = Clock::now();
    double customSortMs = toMilliseconds(ts1, ts2);

    // 2.2 std::sort by price
    auto ts3 = Clock::now();
    std::sort(sortStl.begin(), sortStl.end(), [](const BenchmarkBooking& a, const BenchmarkBooking& b) {
        return a.price < b.price;
    });
    auto ts4 = Clock::now();
    double stlSortMs = toMilliseconds(ts3, ts4);

    // Verification of sorting correctness
    bool isCustomSorted = true;
    for (size_t i = 1; i < sortCustom.size(); ++i) {
        if (sortCustom[i - 1].price > sortCustom[i].price) {
            isCustomSorted = false;
            break;
        }
    }

    std::cout << "  • Custom QuickSort (Lomuto):     \033[32m" << customSortMs << " ms\033[0m "
              << (isCustomSorted ? "[\033[32mVALIDATED SORT ORDER\033[0m]" : "[\033[31mINVALID\033[0m]") << "\n";
    std::cout << "  • std::sort (IntroSort):         \033[34m" << stlSortMs << " ms\033[0m\n\n";

    // ------------------------------------------------------------------------
    // BENCHMARK 3: Binary Search O(log N) vs Linear Search O(N) (1,000 Queries)
    // ------------------------------------------------------------------------
    std::cout << "\033[1;35m[3/3] BENCHMARKING SEARCH COMPLEXITY: O(log N) vs O(N) (1,000 Lookups)\033[0m\n";

    // Prepare sorted array by booking ID
    DynamicArray<BenchmarkBooking> idSortedArr = customArr;
    algorithms::quickSort(idSortedArr, [](const BenchmarkBooking& a, const BenchmarkBooking& b) {
        return a.bookingId < b.bookingId;
    });

    constexpr int NUM_QUERIES = 1000;
    std::uniform_int_distribution<int> idDist(1, static_cast<int>(N));
    std::vector<int> targetIds(NUM_QUERIES);
    for (int i = 0; i < NUM_QUERIES; ++i) {
        targetIds[i] = idDist(rng);
    }

    // 3.1 Binary Search
    auto tbs1 = Clock::now();
    int binaryFoundCount = 0;
    for (int target : targetIds) {
        int idx = algorithms::binarySearch(idSortedArr, target, [](const BenchmarkBooking& b) {
            return b.bookingId;
        });
        if (idx != -1) binaryFoundCount++;
    }
    auto tbs2 = Clock::now();
    double binarySearchMs = toMilliseconds(tbs1, tbs2);

    // 3.2 Linear Search
    auto tls1 = Clock::now();
    int linearFoundCount = 0;
    for (int target : targetIds) {
        int idx = algorithms::linearSearch(idSortedArr, target, [](const BenchmarkBooking& b) {
            return b.bookingId;
        });
        if (idx != -1) linearFoundCount++;
    }
    auto tls2 = Clock::now();
    double linearSearchMs = toMilliseconds(tls1, tls2);

    double speedup = linearSearchMs / (binarySearchMs > 0.0001 ? binarySearchMs : 0.0001);

    std::cout << "  • Binary Search O(log N) [1000 queries]: \033[1;32m" << binarySearchMs << " ms\033[0m (Found: " << binaryFoundCount << ")\n";
    std::cout << "  • Linear Search O(N)     [1000 queries]: \033[1;31m" << linearSearchMs << " ms\033[0m (Found: " << linearFoundCount << ")\n";
    std::cout << "  • Empirical Algorithmic Speedup:         \033[1;33m" << speedup << "x FASTER\033[0m\n\n";

    // ------------------------------------------------------------------------
    // SUMMARY COMPARISON TABLE
    // ------------------------------------------------------------------------
    std::cout << "\033[1;36m+------------------------------------+-----------------+-----------------+----------------+\033[0m\n";
    std::cout << "\033[1;36m| Operation                          | Custom DSA      | C++ STL / Base  | Complexity     |\033[0m\n";
    std::cout << "\033[1;36m+------------------------------------+-----------------+-----------------+----------------+\033[0m\n";
    std::cout << "| 100k Records Allocation & Append   | " << std::setw(12) << customPushMs << " ms | " << std::setw(12) << stlPushMs << " ms | O(1) amortized |\n";
    std::cout << "| 100k Elements Sequential Scan      | " << std::setw(12) << customScanMs << " ms | " << std::setw(12) << stlScanMs << " ms | O(N)           |\n";
    std::cout << "| 100k Records Sort by Nightly Rate  | " << std::setw(12) << customSortMs << " ms | " << std::setw(12) << stlSortMs << " ms | O(N log N)     |\n";
    std::cout << "| 1,000 Search Queries (Lookup)      | " << std::setw(12) << binarySearchMs << " ms | " << std::setw(12) << linearSearchMs << " ms | O(log N) vs O(N)|\n";
    std::cout << "\033[1;36m+------------------------------------+-----------------+-----------------+----------------+\033[0m\n";
    std::cout << "\033[1;32m[OK] Academic DSA benchmark run completed successfully.\033[0m\n\n";

    return 0;
}
