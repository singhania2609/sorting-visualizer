#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <fstream>
#include <sstream>
#include "sorting_analyzer.h"

class SortingVisualizer {
private:
    std::vector<int> data;
    std::vector<std::vector<int>> steps;
    
public:
    SortingVisualizer() = default;
    
    void generateRandomData(int size, int min = 1, int max = 100) {
        data.clear();
        steps.clear();
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        
        for (int i = 0; i < size; ++i) {
            data.push_back(dis(gen));
        }
        
        // Store initial state
        steps.push_back(data);
    }
    
    void loadDataFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return;
        }
        
        data.clear();
        steps.clear();
        
        int value;
        while (file >> value) {
            data.push_back(value);
        }
        
        steps.push_back(data);
        file.close();
    }
    
    void bubbleSort() {
        steps.clear();
        steps.push_back(data);
        
        std::vector<int> arr = data;
        int n = arr.size();
        
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    steps.push_back(arr);
                }
            }
        }
    }
    
    void quickSort() {
        steps.clear();
        steps.push_back(data);
        
        std::vector<int> arr = data;
        quickSortHelper(arr, 0, arr.size() - 1);
    }
    
    void quickSortHelper(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSortHelper(arr, low, pi - 1);
            quickSortHelper(arr, pi + 1, high);
        }
    }
    
    int partition(std::vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = (low - 1);
        
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
                steps.push_back(arr);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        steps.push_back(arr);
        return (i + 1);
    }
    
    void mergeSort() {
        steps.clear();
        steps.push_back(data);
        
        std::vector<int> arr = data;
        mergeSortHelper(arr, 0, arr.size() - 1);
    }
    
    void mergeSortHelper(std::vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortHelper(arr, left, mid);
            mergeSortHelper(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }
    
    void merge(std::vector<int>& arr, int left, int mid, int right) {
        int i, j, k;
        int n1 = mid - left + 1;
        int n2 = right - mid;
        
        std::vector<int> L(n1), R(n2);
        
        for (i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];
        
        i = 0;
        j = 0;
        k = left;
        
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }
        
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
        
        steps.push_back(arr);
    }
    
    void exportSteps(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not create file " << filename << std::endl;
            return;
        }
        
        for (const auto& step : steps) {
            for (size_t i = 0; i < step.size(); ++i) {
                file << step[i];
                if (i < step.size() - 1) file << " ";
            }
            file << std::endl;
        }
        
        file.close();
        std::cout << "Steps exported to " << filename << std::endl;
    }
    
    void printData() const {
        std::cout << "Current data: ";
        for (int val : data) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    
    void printSteps() const {
        std::cout << "Sorting steps (" << steps.size() << " total):" << std::endl;
        for (size_t i = 0; i < steps.size(); ++i) {
            std::cout << "Step " << i << ": ";
            for (int val : steps[i]) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }
    
    const std::vector<std::vector<int>>& getSteps() const {
        return steps;
    }
    
    const std::vector<int>& getData() const {
        return data;
    }
};

int main() {
    SortingVisualizer visualizer;
    
    std::cout << "=== Sorting Visualizer ===" << std::endl;
    
    // Generate random data
    visualizer.generateRandomData(10);
    std::cout << "Generated random data:" << std::endl;
    visualizer.printData();
    
    // Test different sorting algorithms
    std::cout << "\n=== Bubble Sort ===" << std::endl;
    visualizer.bubbleSort();
    visualizer.printSteps();
    
    // Generate new data for next test
    visualizer.generateRandomData(8);
    std::cout << "\n=== Quick Sort ===" << std::endl;
    visualizer.quickSort();
    visualizer.printSteps();
    
    // Generate new data for next test
    visualizer.generateRandomData(12);
    std::cout << "\n=== Merge Sort ===" << std::endl;
    visualizer.mergeSort();
    visualizer.printSteps();
    
    // Export steps to file
    visualizer.exportSteps("sorting_steps.txt");
    
    return 0;
}