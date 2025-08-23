#ifndef SORTING_ANALYZER_H
#define SORTING_ANALYZER_H

#include <vector>
#include <string>
#include <chrono>
#include <functional>

class SortingAnalyzer {
public:
    struct SortResult {
        std::string algorithm_name;
        double execution_time_ms;
        int comparisons;
        int swaps;
        bool is_sorted;
    };
    
    // Performance analysis functions
    static SortResult analyzeSort(const std::string& name, 
                                 std::function<void(std::vector<int>&)> sort_func,
                                 std::vector<int> data);
    
    static bool isSorted(const std::vector<int>& data);
    static int countComparisons(const std::vector<int>& original, 
                               const std::vector<int>& sorted);
    static int countSwaps(const std::vector<int>& original, 
                         const std::vector<int>& sorted);
    
    // Data generation utilities
    static std::vector<int> generateRandomData(int size, int min = 1, int max = 100);
    static std::vector<int> generateSortedData(int size, bool ascending = true);
    static std::vector<int> generateReverseSortedData(int size);
    static std::vector<int> generateNearlySortedData(int size, double disorder_percentage = 0.1);
    
    // Benchmarking functions
    static std::vector<SortResult> benchmarkAlgorithms(
        const std::vector<std::pair<std::string, std::function<void(std::vector<int>&)>>>& algorithms,
        const std::vector<int>& data);
    
    static void exportBenchmarkResults(const std::vector<SortResult>& results, 
                                      const std::string& filename);
    
    // Visualization helpers
    static std::string arrayToString(const std::vector<int>& arr);
    static void printArray(const std::vector<int>& arr);
    static void printArrayWithHighlights(const std::vector<int>& arr, 
                                       const std::vector<int>& highlights);
};

#endif // SORTING_ANALYZER_H