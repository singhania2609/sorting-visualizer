#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
#include <fstream>
#include "sorting_analyzer.h"

class SortingVisualizer {
private:
    std::vector<int> array;
    int comparisons;
    int swaps;
    
public:
    SortingVisualizer() : comparisons(0), swaps(0) {}
    
    void generateRandomArray(int size, int min = 1, int max = 100) {
        array.clear();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        
        for (int i = 0; i < size; ++i) {
            array.push_back(dis(gen));
        }
    }
    
    void displayArray() const {
        std::cout << "Array: ";
        for (int val : array) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    

    void bubbleSort() {
        comparisons = 0;
        swaps = 0;
        int n = array.size();
        
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                comparisons++;
                if (array[j] > array[j + 1]) {
                    std::swap(array[j], array[j + 1]);
                    swaps++;
                }
            }
        }
    }
    
    // Quick Sort - O(n log n) average, O(n²) worst case
    void quickSort() {
        comparisons = 0;
        swaps = 0;
        quickSortHelper(0, array.size() - 1);
    }
    
private:
    void quickSortHelper(int low, int high) {
        if (low < high) {
            int pi = partition(low, high);
            quickSortHelper(low, pi - 1);
            quickSortHelper(pi + 1, high);
        }
    }
    
    int partition(int low, int high) {
        int pivot = array[high];
        int i = low - 1;
        
        for (int j = low; j < high; ++j) {
            comparisons++;
            if (array[j] <= pivot) {
                i++;
                if (i != j) {
                    std::swap(array[i], array[j]);
                    swaps++;
                }
            }
        }
        
        if (i + 1 != high) {
            std::swap(array[i + 1], array[high]);
            swaps++;
        }
        
        return i + 1;
    }
    
public:
    // Merge Sort - O(n log n)
    void mergeSort() {
        comparisons = 0;
        swaps = 0;
        mergeSortHelper(0, array.size() - 1);
    }
    
private:
    void mergeSortHelper(int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortHelper(left, mid);
            mergeSortHelper(mid + 1, right);
            merge(left, mid, right);
        }
    }
    
    void merge(int left, int mid, int right) {
        std::vector<int> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;
        
        while (i <= mid && j <= right) {
            comparisons++;
            if (array[i] <= array[j]) {
                temp[k++] = array[i++];
            } else {
                temp[k++] = array[j++];
            }
        }
        
        while (i <= mid) {
            temp[k++] = array[i++];
        }
        
        while (j <= right) {
            temp[k++] = array[j++];
        }
        
        for (int x = 0; x < k; ++x) {
            array[left + x] = temp[x];
            swaps++;
        }
    }
    
public:
    // Insertion Sort - O(n²)
    void insertionSort() {
        comparisons = 0;
        swaps = 0;
        int n = array.size();
        
        for (int i = 1; i < n; ++i) {
            int key = array[i];
            int j = i - 1;
            
            while (j >= 0 && array[j] > key) {
                comparisons++;
                array[j + 1] = array[j];
                swaps++;
                j--;
            }
            array[j + 1] = key;
        }
    }
    
    // Selection Sort - O(n²)
    void selectionSort() {
        comparisons = 0;
        swaps = 0;
        int n = array.size();
        
        for (int i = 0; i < n - 1; ++i) {
            int min_idx = i;
            for (int j = i + 1; j < n; ++j) {
                comparisons++;
                if (array[j] < array[min_idx]) {
                    min_idx = j;
                }
            }
            
            if (min_idx != i) {
                std::swap(array[min_idx], array[i]);
                swaps++;
            }
        }
    }

    // Heap Sort - O(n log n)
    void heapSort() {
        comparisons = 0;
        swaps = 0;
        int n = array.size();
        
        // Build max heap
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(n, i);
        }
        
        // Extract elements from heap one by one
        for (int i = n - 1; i > 0; i--) {
            // Move current root to end
            std::swap(array[0], array[i]);
            swaps++;
            
            // Call heapify on the reduced heap
            heapify(i, 0);
        }
    }

private:
    void heapify(int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        // Compare with left child
        if (left < n) {
            comparisons++;
            if (array[left] > array[largest]) {
                largest = left;
            }
        }
        
        // Compare with right child
        if (right < n) {
            comparisons++;
            if (array[right] > array[largest]) {
                largest = right;
            }
        }
        
        // If largest is not root
        if (largest != i) {
            std::swap(array[i], array[largest]);
            swaps++;
            
            // Recursively heapify the affected sub-tree
            heapify(n, largest);
        }
    }
    
public:
    // Getter methods
    int getComparisons() const { return comparisons; }
    int getSwaps() const { return swaps; }
    const std::vector<int>& getArray() const { return array; }
    
    // Check if array is sorted
    bool isSorted() const {
        for (size_t i = 1; i < array.size(); ++i) {
            if (array[i] < array[i - 1]) return false;
        }
        return true;
    }
};

int main() {
    SortingVisualizer visualizer;
    std::cout << "=== DSA Sorting Algorithm Visualizer ===" << std::endl;
    
    // Test with different array sizes
    std::vector<int> sizes = {10, 50, 100, 500, 1000};
    
    for (int size : sizes) {
        std::cout << "\n--- Testing with array size: " << size << " ---" << std::endl;
        
        // Generate random array
        visualizer.generateRandomArray(size);
        std::cout << "Original array (first 10 elements): ";
        auto arr = visualizer.getArray();
        for (int i = 0; i < std::min(10, size); ++i) {
            std::cout << arr[i] << " ";
        }
        if (size > 10) std::cout << "...";
        std::cout << std::endl;
        
        // Test all sorting algorithms
        std::vector<std::pair<std::string, std::function<void()>>> algorithms = {
            {"Bubble Sort", [&]() { visualizer.bubbleSort(); }},
            {"Quick Sort", [&]() { visualizer.quickSort(); }},
            {"Merge Sort", [&]() { visualizer.mergeSort(); }},
            {"Insertion Sort", [&]() { visualizer.insertionSort(); }},
            {"Selection Sort", [&]() { visualizer.selectionSort(); }},
            {"Heap Sort", [&]() { visualizer.heapSort(); }}
        };
        
        for (const auto& algorithm : algorithms) {
            const std::string& name = algorithm.first;
            const auto& algo = algorithm.second;
            
            // Generate fresh array for each algorithm
            visualizer.generateRandomArray(size);
            
            auto start = std::chrono::high_resolution_clock::now();
            algo();
            auto end = std::chrono::high_resolution_clock::now();
            
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            std::cout << name << ": ";
            std::cout << "Comparisons: " << visualizer.getComparisons() << ", ";
            std::cout << "Swaps: " << visualizer.getSwaps() << ", ";
            std::cout << "Time: " << duration.count() << " μs, ";
            std::cout << "Sorted: " << (visualizer.isSorted() ? "Yes" : "No") << std::endl;
        }
    }
    
    std::cout << "\n=== DSA Analysis Complete ===" << std::endl;
    return 0;
}
