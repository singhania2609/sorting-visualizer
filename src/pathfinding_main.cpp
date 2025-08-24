#include "pathfinding.h"
#include <iostream>
#include <iomanip>
#include <chrono>

int main() {
    std::cout << "=== DSA Pathfinding Algorithm Visualizer ===" << std::endl;
    std::cout << "Indian Cities Network Analysis (Dijkstra, BFS, DFS)\n\n";
    
    PathfindingVisualizer pathfinder;
    
    // Display available cities
    std::cout << "Available Cities:\n";
    std::cout << "=================\n";
    for (size_t i = 0; i < 20; ++i) { // Show first 20 cities
        std::cout << std::setw(2) << (i + 1) << ". " << std::setw(20) << std::left 
                  << pathfinder.getNeighbors("Mumbai")[0] << std::endl;
    }
    std::cout << std::endl;
    
    // Test pathfinding between major cities
    std::vector<std::pair<std::string, std::string>> testRoutes = {
        {"Mumbai", "Delhi"},
        {"Bangalore", "Kolkata"},
        {"Chennai", "Hyderabad"},
        {"Pune", "Ahmedabad"},
        {"Jaipur", "Lucknow"}
    };
    
    for (const auto& route : testRoutes) {
        std::cout << "--- Route: " << route.first << " to " << route.second << " ---\n";
        
        // Compare all three algorithms
        auto start = std::chrono::high_resolution_clock::now();
        auto results = pathfinder.compareAlgorithms(route.first, route.second);
        auto end = std::chrono::high_resolution_clock::now();
        
        auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Total comparison time: " << totalTime.count() << " μs\n\n";
        
        for (const auto& result : results) {
            pathfinder.printPath(result);
            std::cout << std::endl;
        }
        
        std::cout << "========================================\n\n";
    }
    
    // Graph analysis
    std::cout << "Graph Analysis:\n";
    std::cout << "===============\n";
    pathfinder.analyzeGraphProperties();
    std::cout << std::endl;
    
    // Find connected components
    std::cout << "Connected Components Analysis:\n";
    std::cout << "=============================\n";
    pathfinder.findConnectedComponents();
    std::cout << std::endl;
    
    // Calculate average path length
    std::cout << "Average Path Length Analysis:\n";
    std::cout << "=============================\n";
    pathfinder.calculateAveragePathLength();
    std::endl;
    
    // Export results
    std::cout << "Exporting results to 'pathfinding_results.txt'...\n";
    auto allResults = pathfinder.compareAlgorithms("Mumbai", "Kolkata");
    pathfinder.exportResults(allResults, "pathfinding_results.txt");
    std::cout << "Results exported successfully!\n\n";
    
    // Interactive testing
    std::cout << "Interactive Testing:\n";
    std::cout << "====================\n";
    std::cout << "Enter source city (or 'quit' to exit): ";
    
    std::string source, destination;
    while (std::cin >> source && source != "quit") {
        std::cout << "Enter destination city: ";
        std::cin >> destination;
        
        if (source == destination) {
            std::cout << "Source and destination cannot be the same!\n\n";
            std::cout << "Enter source city (or 'quit' to exit): ";
            continue;
        }
        
        std::cout << "\nFinding path from " << source << " to " << destination << "...\n";
        
        auto results = pathfinder.compareAlgorithms(source, destination);
        
        if (results[0].path.empty()) {
            std::cout << "No path found between " << source << " and " << destination << "!\n\n";
        } else {
            std::cout << "Results:\n";
            for (const auto& result : results) {
                pathfinder.printPath(result);
                std::cout << std::endl;
            }
        }
        
        std::cout << "Enter source city (or 'quit' to exit): ";
    }
    
    std::cout << "\n=== DSA Pathfinding Analysis Complete ===" << std::endl;
    return 0;
}
