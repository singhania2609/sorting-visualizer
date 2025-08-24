#ifndef SORTING_ANALYZER_H
#define SORTING_ANALYZER_H

#include <vector>
#include <string>
#include <chrono>
#include <functional>

/**
 * Sorting Algorithm Analyzer
 * Provides analysis and benchmarking for various sorting algorithms
 */

class SortingAnalyzer {
public:
    // Performance metrics structure
    struct PerformanceMetrics {
        long long comparisons;
        long long swaps;
        long long executionTime; // in microseconds
        bool isCorrectlySorted;
        std::string algorithmName;
        
        PerformanceMetrics() : comparisons(0), swaps(0), executionTime(0), isCorrectlySorted(false) {}
    };
    
    // Algorithm comparison result
    struct AlgorithmComparison {
        std::string name;
        double timeComplexity; // theoretical complexity
        PerformanceMetrics metrics;
        
        AlgorithmComparison(const std::string& n, double tc) : name(n), timeComplexity(tc) {}
    };
    
    // Benchmark different algorithms
    static std::vector<AlgorithmComparison> benchmarkAlgorithms(
        const std::vector<int>& data,
        const std::vector<std::pair<std::string, std::function<void(std::vector<int>&)>>>& algorithms
    );
    
    // Generate test data
    static std::vector<int> generateRandomData(int size, int min = 1, int max = 1000);
    static std::vector<int> generateNearlySortedData(int size, double disorderPercentage = 0.1);
    static std::vector<int> generateReverseSortedData(int size);
    static std::vector<int> generateDuplicateData(int size, int uniqueValues = 10);
    
    // Analysis functions
    static void analyzeTimeComplexity(const std::vector<AlgorithmComparison>& results);
    static void generateReport(const std::vector<AlgorithmComparison>& results, const std::string& filename);
    
    // Utility functions
    static bool isSorted(const std::vector<int>& data);
    static void printArray(const std::vector<int>& data, int maxElements = 20);
    static double calculateAverage(const std::vector<long long>& values);
    static long long calculateMedian(const std::vector<long long>& values);
};

#endif // SORTING_ANALYZER_H
