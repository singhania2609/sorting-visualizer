#include "pathfinding.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stack>

PathfindingVisualizer::PathfindingVisualizer() {
    // Initialize with Indian cities
    cities = {
        {"Mumbai", 19.0760, 72.8777},
        {"Delhi", 28.7041, 77.1025},
        {"Bangalore", 12.9716, 77.5946},
        {"Hyderabad", 17.3850, 78.4867},
        {"Chennai", 13.0827, 80.2707},
        {"Kolkata", 22.5726, 88.3639},
        {"Pune", 18.5204, 73.8567},
        {"Ahmedabad", 23.0225, 72.5714},
        {"Jaipur", 26.9124, 75.7873},
        {"Surat", 21.1702, 72.8311},
        {"Lucknow", 26.8467, 80.9462},
        {"Kanpur", 26.4499, 80.3319},
        {"Nagpur", 21.1458, 79.0882},
        {"Indore", 22.7196, 75.8577},
        {"Thane", 19.2183, 72.9781},
        {"Bhopal", 23.2599, 77.4126},
        {"Visakhapatnam", 17.6868, 83.2185},
        {"Pimpri-Chinchwad", 18.6298, 73.7997},
        {"Patna", 25.5941, 85.1376},
        {"Vadodara", 22.3072, 73.1812}
    };
    
    // Initialize routes between cities (simplified without transport modes)
    routes = {
        {"Mumbai", "Delhi", 1150.0, 2.0},
        {"Mumbai", "Bangalore", 845.0, 1.5},
        {"Mumbai", "Hyderabad", 710.0, 1.2},
        {"Mumbai", "Chennai", 1035.0, 1.8},
        {"Mumbai", "Kolkata", 1650.0, 2.5},
        {"Delhi", "Bangalore", 1750.0, 2.8},
        {"Delhi", "Hyderabad", 1580.0, 2.5},
        {"Delhi", "Chennai", 1760.0, 2.8},
        {"Delhi", "Kolkata", 1300.0, 2.0},
        {"Bangalore", "Hyderabad", 570.0, 1.0},
        {"Bangalore", "Chennai", 350.0, 0.8},
        {"Bangalore", "Kolkata", 1550.0, 2.5},
        {"Hyderabad", "Chennai", 625.0, 1.1},
        {"Hyderabad", "Kolkata", 1200.0, 2.0},
        {"Chennai", "Kolkata", 1660.0, 2.7},
        {"Mumbai", "Pune", 150.0, 3.0},
        {"Mumbai", "Ahmedabad", 530.0, 8.0},
        {"Delhi", "Jaipur", 280.0, 5.0},
        {"Delhi", "Lucknow", 500.0, 8.0},
        {"Delhi", "Kanpur", 450.0, 7.0},
        {"Bangalore", "Mysore", 150.0, 3.0},
        {"Hyderabad", "Vijayawada", 280.0, 5.0},
        {"Chennai", "Vellore", 130.0, 2.5},
        {"Kolkata", "Howrah", 10.0, 0.5},
        {"Pune", "Mumbai", 150.0, 3.0},
        {"Ahmedabad", "Surat", 280.0, 5.0},
        {"Jaipur", "Delhi", 280.0, 5.0},
        {"Lucknow", "Kanpur", 80.0, 1.5},
        {"Nagpur", "Bhopal", 320.0, 6.0},
        {"Indore", "Bhopal", 190.0, 3.5},
        {"Thane", "Mumbai", 25.0, 1.0},
        {"Bhopal", "Indore", 190.0, 3.5},
        {"Visakhapatnam", "Vijayawada", 350.0, 6.0},
        {"Pimpri-Chinchwad", "Pune", 15.0, 0.5},
        {"Patna", "Varanasi", 250.0, 5.0},
        {"Vadodara", "Ahmedabad", 110.0, 2.0}
    };
    
    buildGraph();
}

void PathfindingVisualizer::buildGraph() {
    graph.clear();
    
    // Add all cities to graph
    for (const auto& city : cities) {
        graph[city.name] = std::map<std::string, Route>();
    }
    
    // Add routes to graph
    for (const auto& route : routes) {
        graph[route.from][route.to] = route;
        // Add reverse route for undirected graph
        Route reverseRoute(route.to, route.from, route.distance, route.time);
        graph[route.to][route.from] = reverseRoute;
    }
}

void PathfindingVisualizer::addCity(const City& city) {
    cities.push_back(city);
    graph[city.name] = std::map<std::string, Route>();
}

void PathfindingVisualizer::addRoute(const Route& route) {
    routes.push_back(route);
    graph[route.from][route.to] = route;
    // Add reverse route for undirected graph
    Route reverseRoute(route.to, route.from, route.distance, route.time);
    graph[route.to][route.from] = reverseRoute;
}

PathResult PathfindingVisualizer::dijkstra(const std::string& source, const std::string& destination) {
    PathResult result;
    result.algorithm = "Dijkstra";
    
    if (!cityExists(source) || !cityExists(destination)) {
        return result;
    }
    
    std::map<std::string, double> distances;
    std::map<std::string, std::string> previous;
    std::set<std::string> unvisited;
    
    // Initialize distances
    for (const auto& city : cities) {
        distances[city.name] = std::numeric_limits<double>::infinity();
        unvisited.insert(city.name);
    }
    distances[source] = 0.0;
    
    while (!unvisited.empty()) {
        std::string current = findMinDistanceCity(distances, unvisited);
        
        if (current == destination) {
            break;
        }
        
        unvisited.erase(current);
        
        for (const auto& neighbor : graph[current]) {
            if (unvisited.find(neighbor.first) != unvisited.end()) {
                double newDistance = distances[current] + neighbor.second.distance;
                if (newDistance < distances[neighbor.first]) {
                    distances[neighbor.first] = newDistance;
                    previous[neighbor.first] = current;
                }
            }
        }
    }
    
    // Reconstruct path
    result.path = reconstructPath(previous, source, destination);
    if (!result.path.empty()) {
    result.totalDistance = calculateTotalDistance(result.path);
    result.totalTime = calculateTotalTime(result.path);
    result.routeDetails = getRouteDetails(result.path);
}
    
    return result;
}

PathResult PathfindingVisualizer::breadthFirstSearch(const std::string& source, const std::string& destination) {
    PathResult result;
    result.algorithm = "BFS";
    
    if (!cityExists(source) || !cityExists(destination)) {
        return result;
    }
    
    std::map<std::string, std::string> previous;
    std::map<std::string, bool> visited;
    std::queue<std::string> queue;
    
    // Initialize visited map
    for (const auto& city : cities) {
        visited[city.name] = false;
    }
    
    queue.push(source);
    visited[source] = true;
    
    while (!queue.empty()) {
        std::string current = queue.front();
        queue.pop();
        
        if (current == destination) {
            break;
        }
        
        for (const auto& neighbor : graph[current]) {
            if (!visited[neighbor.first]) {
                visited[neighbor.first] = true;
                previous[neighbor.first] = current;
                queue.push(neighbor.first);
            }
        }
    }
    
    // Reconstruct path
    result.path = reconstructPath(previous, source, destination);
    if (!result.path.empty()) {
        result.totalDistance = calculateTotalDistance(result.path);
        result.totalTime = calculateTotalTime(result.path);
        result.routeDetails = getRouteDetails(result.path);
    }
    
    return result;
}

PathResult PathfindingVisualizer::depthFirstSearch(const std::string& source, const std::string& destination) {
    PathResult result;
    result.algorithm = "DFS";
    
    if (!cityExists(source) || !cityExists(destination)) {
        return result;
    }
    
    std::map<std::string, bool> visited;
    std::map<std::string, std::string> previous;
    bool found = false;
    
    // Initialize visited map
    for (const auto& city : cities) {
        visited[city.name] = false;
    }
    
    // Start DFS from source
    dfsHelper(source, destination, visited, previous, found);
    
    // Reconstruct path if found
    if (found) {
        result.path = reconstructPath(previous, source, destination);
        result.totalDistance = calculateTotalDistance(result.path);
        result.totalTime = calculateTotalTime(result.path);
        result.routeDetails = getRouteDetails(result.path);
    }
    
    return result;
}

std::vector<PathResult> PathfindingVisualizer::compareAlgorithms(const std::string& source, const std::string& destination) {
    std::vector<PathResult> results;
    
    results.push_back(dijkstra(source, destination));
    results.push_back(breadthFirstSearch(source, destination));
    results.push_back(depthFirstSearch(source, destination));
    
    return results;
}

double PathfindingVisualizer::calculateHeuristic(const std::string& city1, const std::string& city2) {
    // Find city coordinates
    double lat1 = 0, lon1 = 0, lat2 = 0, lon2 = 0;
    
    for (const auto& city : cities) {
        if (city.name == city1) {
            lat1 = city.latitude;
            lon1 = city.longitude;
        }
        if (city.name == city2) {
            lat2 = city.latitude;
            lon2 = city.longitude;
        }
    }
    
    return haversineDistance(lat1, lon1, lat2, lon2);
}

std::vector<std::string> PathfindingVisualizer::getNeighbors(const std::string& city) {
    std::vector<std::string> neighbors;
    
    if (graph.find(city) != graph.end()) {
        for (const auto& neighbor : graph[city]) {
            neighbors.push_back(neighbor.first);
        }
    }
    
    return neighbors;
}

bool PathfindingVisualizer::cityExists(const std::string& cityName) {
    for (const auto& city : cities) {
        if (city.name == cityName) {
            return true;
        }
    }
    return false;
}

void PathfindingVisualizer::printPath(const PathResult& result) {
    if (result.path.empty()) {
        std::cout << "No path found!" << std::endl;
        return;
    }
    
    std::cout << "Algorithm: " << result.algorithm << std::endl;
    std::cout << "Path: ";
    for (size_t i = 0; i < result.path.size(); ++i) {
        std::cout << result.path[i];
        if (i < result.path.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
    std::cout << "Total Distance: " << result.totalDistance << " km" << std::endl;
    std::cout << "Total Time: " << result.totalTime << " hours" << std::endl;
    std::cout << "Route Details:" << std::endl;
    
    for (const auto& route : result.routeDetails) {
        std::cout << "  " << route.from << " to " << route.to 
                  << ": " << route.distance << " km, " << route.time << " hours" << std::endl;
    }
}

void PathfindingVisualizer::exportResults(const std::vector<PathResult>& results, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    
    file << "Pathfinding Algorithm Comparison Results\n";
    file << "=======================================\n\n";
    
    for (const auto& result : results) {
        file << "Algorithm: " << result.algorithm << "\n";
        file << "Path: ";
        for (size_t i = 0; i < result.path.size(); ++i) {
            file << result.path[i];
            if (i < result.path.size() - 1) file << " -> ";
        }
        file << "\n";
        file << "Total Distance: " << result.totalDistance << " km\n";
        file << "Total Time: " << result.totalTime << " hours\n\n";
    }
    
    file.close();
}

void PathfindingVisualizer::loadCitiesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening cities file: " << filename << std::endl;
        return;
    }
    
    cities.clear();
    std::string line;
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        double lat, lon;
        
        if (iss >> name >> lat >> lon) {
            cities.emplace_back(name, lat, lon);
        }
    }
    
    file.close();
    buildGraph();
}

void PathfindingVisualizer::loadRoutesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening routes file: " << filename << std::endl;
        return;
    }
    
    routes.clear();
    std::string line;
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string from, to;
        double distance, time;
        
        if (iss >> from >> to >> distance >> time) {
            routes.emplace_back(from, to, distance, time);
        }
    }
    
    file.close();
    buildGraph();
}

void PathfindingVisualizer::analyzeGraphProperties() {
    std::cout << "Graph Analysis:\n";
    std::cout << "Cities: " << cities.size() << std::endl;
    std::cout << "Routes: " << routes.size() << std::endl;
    
    int totalConnections = 0;
    for (const auto& city : graph) {
        totalConnections += city.second.size();
    }
    
    std::cout << "Total connections: " << totalConnections << std::endl;
    std::cout << "Average connections per city: " 
              << (double)totalConnections / cities.size() << std::endl;
}

void PathfindingVisualizer::findConnectedComponents() {
    std::map<std::string, bool> visited;
    std::vector<std::vector<std::string>> components;
    
    // Initialize visited map
    for (const auto& city : cities) {
        visited[city.name] = false;
    }
    
    // DFS to find connected components
    for (const auto& city : cities) {
        if (!visited[city.name]) {
            std::vector<std::string> component;
            std::stack<std::string> stack;
            
            stack.push(city.name);
            visited[city.name] = true;
            
            while (!stack.empty()) {
                std::string current = stack.top();
                stack.pop();
                component.push_back(current);
                
                for (const auto& neighbor : graph[current]) {
                    if (!visited[neighbor.first]) {
                        visited[neighbor.first] = true;
                        stack.push(neighbor.first);
                    }
                }
            }
            
            components.push_back(component);
        }
    }
    
    std::cout << "Connected Components: " << components.size() << std::endl;
    for (size_t i = 0; i < components.size(); ++i) {
        std::cout << "Component " << (i + 1) << " (" << components[i].size() << " cities): ";
        for (const auto& city : components[i]) {
            std::cout << city << " ";
        }
        std::cout << std::endl;
    }
}

void PathfindingVisualizer::calculateAveragePathLength() {
    double totalLength = 0.0;
    int pathCount = 0;
    
    for (size_t i = 0; i < cities.size(); ++i) {
        for (size_t j = i + 1; j < cities.size(); ++j) {
            PathResult result = dijkstra(cities[i].name, cities[j].name);
            if (!result.path.empty()) {
                totalLength += result.totalDistance;
                pathCount++;
            }
        }
    }
    
    if (pathCount > 0) {
        std::cout << "Average shortest path length: " 
                  << (totalLength / pathCount) << " km" << std::endl;
    }
}

// Private helper functions
std::string PathfindingVisualizer::findMinDistanceCity(const std::map<std::string, double>& distances, 
                                                      const std::set<std::string>& unvisited) {
    std::string minCity;
    double minDistance = std::numeric_limits<double>::infinity();
    
    for (const auto& city : unvisited) {
        if (distances.at(city) < minDistance) {
            minDistance = distances.at(city);
            minCity = city;
        }
    }
    
    return minCity;
}

std::vector<std::string> PathfindingVisualizer::reconstructPath(const std::map<std::string, std::string>& previous,
                                                               const std::string& source, 
                                                               const std::string& destination) {
    std::vector<std::string> path;
    
    if (previous.find(destination) == previous.end()) {
        return path; // No path found
    }
    
    std::string current = destination;
    while (current != source) {
        path.push_back(current);
        current = previous.at(current);
    }
    path.push_back(source);
    
    std::reverse(path.begin(), path.end());
    return path;
}

double PathfindingVisualizer::haversineDistance(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371.0; // Earth's radius in kilometers
    
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    
    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) *
               sin(dLon / 2) * sin(dLon / 2);
    
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    
    return R * c;
}

// Additional helper functions for path calculations
double PathfindingVisualizer::calculateTotalDistance(const std::vector<std::string>& path) {
    double total = 0.0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        if (graph[path[i]].find(path[i + 1]) != graph[path[i]].end()) {
            total += graph[path[i]][path[i + 1]].distance;
        }
    }
    return total;
}

double PathfindingVisualizer::calculateTotalTime(const std::vector<std::string>& path) {
    double total = 0.0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        if (graph[path[i]].find(path[i + 1]) != graph[path[i]].end()) {
            total += graph[path[i]][path[i + 1]].time;
        }
    }
    return total;
}

std::vector<Route> PathfindingVisualizer::getRouteDetails(const std::vector<std::string>& path) {
    std::vector<Route> details;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        if (graph[path[i]].find(path[i + 1]) != graph[path[i]].end()) {
            details.push_back(graph[path[i]][path[i + 1]]);
        }
    }
    return details;
}

void PathfindingVisualizer::dfsHelper(const std::string& current, const std::string& destination, 
                                     std::map<std::string, bool>& visited, 
                                     std::map<std::string, std::string>& previous,
                                     bool& found) {
    if (found) return; // Stop if path already found
    
    visited[current] = true;
    
    if (current == destination) {
        found = true;
        return;
    }
    
    // Explore all neighbors
    for (const auto& neighbor : graph[current]) {
        if (!visited[neighbor.first] && !found) {
            previous[neighbor.first] = current;
            dfsHelper(neighbor.first, destination, visited, previous, found);
        }
    }
}
