#include <iostream>
#include <iomanip>
#include <chrono>
#include "pathfinding.h"

class PathfindingDemo {
private:
    PathFinder pathfinder;
    
public:
    void runDemo() {
        std::cout << "=== City Pathfinding and Route Optimization Demo ===" << std::endl;
        std::cout << "This demo showcases pathfinding algorithms for finding optimal routes between cities." << std::endl;
        
        displayNetworkInfo();
        runPathfindingExamples();
        runAlgorithmComparison();
        runNetworkAnalysis();
        exportResults();
    }
    
    void displayNetworkInfo() {
        std::cout << "\n=== Network Information ===" << std::endl;
        
        auto cities = pathfinder.getCities();
        auto routes = pathfinder.getRoutes();
        
        std::cout << "Available Cities (" << cities.size() << "):" << std::endl;
        for (const auto& city : cities) {
            std::cout << "  - " << city.name << " (Pop: " << city.population << ", Lat: " 
                      << std::fixed << std::setprecision(4) << city.latitude 
                      << ", Lon: " << city.longitude << ")" << std::endl;
        }
        
        std::cout << "\nAvailable Routes (" << routes.size() / 2 << " bidirectional):" << std::endl;
        for (const auto& route : routes) {
            std::cout << "  - " << route.from << " -> " << route.to 
                      << " (" << std::fixed << std::setprecision(1) << route.distance << " km, "
                      << route.time << " hours, " << route.transport_type << ")" << std::endl;
        }
    }
    
    void runPathfindingExamples() {
        std::cout << "\n=== Pathfinding Examples ===" << std::endl;
        
        std::vector<std::pair<std::string, std::string>> test_routes = {
            {"New York", "Los Angeles"},
            {"Chicago", "San Diego"},
            {"Houston", "Phoenix"},
            {"Philadelphia", "San Jose"}
        };
        
        for (const auto& route : test_routes) {
            std::cout << "\nFinding shortest path from " << route.first << " to " << route.second << ":" << std::endl;
            
            auto start_time = std::chrono::high_resolution_clock::now();
            PathResult result = pathfinder.findShortestPath(route.first, route.second, "dijkstra");
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
            
            if (!result.path.empty()) {
                std::cout << "  Algorithm: " << result.algorithm_used << std::endl;
                std::cout << "  Total Distance: " << std::fixed << std::setprecision(2) << result.total_distance << " km" << std::endl;
                std::cout << "  Total Time: " << std::fixed << std::setprecision(2) << result.total_time << " hours" << std::endl;
                std::cout << "  Path: ";
                for (size_t i = 0; i < result.path.size(); ++i) {
                    std::cout << result.path[i];
                    if (i < result.path.size() - 1) std::cout << " -> ";
                }
                std::cout << std::endl;
                std::cout << "  Execution Time: " << duration.count() << " microseconds" << std::endl;
                
                // Show route details
                std::cout << "  Route Details:" << std::endl;
                for (size_t i = 0; i < result.route_details.size(); ++i) {
                    const auto& route_detail = result.route_details[i];
                    std::cout << "    " << (i + 1) << ". " << route_detail.from << " -> " << route_detail.to
                              << " (" << std::fixed << std::setprecision(1) << route_detail.distance << " km, "
                              << route_detail.time << " hours, " << route_detail.transport_type << ")" << std::endl;
                }
            } else {
                std::cout << "  No path found!" << std::endl;
            }
        }
    }
    
    void runAlgorithmComparison() {
        std::cout << "\n=== Algorithm Comparison ===" << std::endl;
        
        std::string source = "New York";
        std::string destination = "Los Angeles";
        
        std::cout << "Comparing algorithms for route: " << source << " -> " << destination << std::endl;
        
        std::vector<std::string> algorithms = {"dijkstra", "bellman-ford", "floyd-warshall", "a-star"};
        
        for (const std::string& algo : algorithms) {
            std::cout << "\n" << algo << " Algorithm:" << std::endl;
            
            auto start_time = std::chrono::high_resolution_clock::now();
            PathResult result = pathfinder.findShortestPath(source, destination, algo);
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
            
            if (!result.path.empty()) {
                std::cout << "  Distance: " << std::fixed << std::setprecision(2) << result.total_distance << " km" << std::endl;
                std::cout << "  Time: " << std::fixed << std::setprecision(2) << result.total_time << " hours" << std::endl;
                std::cout << "  Execution: " << duration.count() << " microseconds" << std::endl;
                std::cout << "  Path: ";
                for (size_t i = 0; i < result.path.size(); ++i) {
                    std::cout << result.path[i];
                    if (i < result.path.size() - 1) std::cout << " -> ";
                }
                std::cout << std::endl;
            } else {
                std::cout << "  No path found!" << std::endl;
            }
        }
    }
    
    void runNetworkAnalysis() {
        std::cout << "\n=== Network Analysis ===" << std::endl;
        
        pathfinder.analyzeNetwork();
        
        // Find distances from a central city
        std::string central_city = "Chicago";
        std::cout << "\nDistances from " << central_city << ":" << std::endl;
        
        auto distances = pathfinder.getCityDistances(central_city);
        for (const auto& distance_pair : distances) {
            std::cout << "  " << distance_pair.first << ": " 
                      << std::fixed << std::setprecision(2) << distance_pair.second << " km" << std::endl;
        }
        
        // Find the most distant city
        auto max_distance = std::max_element(distances.begin(), distances.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; });
        
        if (max_distance != distances.end()) {
            std::cout << "\nMost distant city from " << central_city << ": " 
                      << max_distance->first << " (" << std::fixed << std::setprecision(2) 
                      << max_distance->second << " km)" << std::endl;
        }
    }
    
    void exportResults() {
        std::cout << "\n=== Exporting Results ===" << std::endl;
        
        // Export network data
        pathfinder.exportNetworkToFile("city_network.txt");
        
        // Export a sample path
        PathResult sample_result = pathfinder.findShortestPath("New York", "Los Angeles", "dijkstra");
        if (!sample_result.path.empty()) {
            pathfinder.exportPathToFile(sample_result, "sample_path.txt");
        }
        
        // Generate and display a comprehensive report
        std::cout << "\nComprehensive Pathfinding Report:" << std::endl;
        std::cout << "=================================" << std::endl;
        
        std::vector<std::pair<std::string, std::string>> test_cases = {
            {"New York", "Los Angeles"},
            {"Chicago", "San Diego"},
            {"Houston", "Phoenix"}
        };
        
        for (const auto& test_case : test_cases) {
            std::cout << "\nRoute: " << test_case.first << " -> " << test_case.second << std::endl;
            
            auto results = pathfinder.compareAlgorithms(test_case.first, test_case.second);
            
            for (const auto& result : results) {
                if (!result.path.empty()) {
                    std::cout << "  " << result.algorithm_used << ": " 
                              << std::fixed << std::setprecision(2) << result.total_distance << " km, "
                              << result.total_time << " hours" << std::endl;
                }
            }
        }
        
        std::cout << "\nFiles generated:" << std::endl;
        std::cout << "  - city_network.txt (network data)" << std::endl;
        std::cout << "  - sample_path.txt (sample path result)" << std::endl;
    }
};

int main() {
    PathfindingDemo demo;
    demo.runDemo();
    
    std::cout << "\n=== Pathfinding Demo Complete ===" << std::endl;
    std::cout << "Check the generated files for detailed analysis." << std::endl;
    
    return 0;
}
