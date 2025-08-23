#include "pathfinding.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <queue>
#include <set>
#include <cmath>
#include <algorithm>

PathFinder::PathFinder() {
    // Initialize with some default cities
    addCity("New York", 40.7128, -74.0060, 8336817);
    addCity("Los Angeles", 34.0522, -118.2437, 3979576);
    addCity("Chicago", 41.8781, -87.6298, 2693976);
    addCity("Houston", 29.7604, -95.3698, 2320268);
    addCity("Phoenix", 33.4484, -112.0740, 1680992);
    addCity("Philadelphia", 39.9526, -75.1652, 1603797);
    addCity("San Antonio", 29.4241, -98.4936, 1547253);
    addCity("San Diego", 32.7157, -117.1611, 1423851);
    addCity("Dallas", 32.7767, -96.7970, 1343573);
    addCity("San Jose", 37.3382, -121.8863, 1030119);
    
    // Add some default routes
    addRoute("New York", "Los Angeles", 3935.0, 6.5, "air");
    addRoute("New York", "Chicago", 1147.0, 2.5, "air");
    addRoute("New York", "Houston", 2271.0, 4.0, "air");
    addRoute("Los Angeles", "Chicago", 2788.0, 4.5, "air");
    addRoute("Los Angeles", "Houston", 2197.0, 4.0, "air");
    addRoute("Chicago", "Houston", 1124.0, 2.0, "air");
    addRoute("Chicago", "Phoenix", 1759.0, 3.5, "air");
    addRoute("Houston", "Phoenix", 1187.0, 2.5, "air");
    addRoute("Phoenix", "San Diego", 572.0, 1.0, "air");
    addRoute("San Diego", "Los Angeles", 120.0, 0.5, "road");
    addRoute("Dallas", "Houston", 362.0, 0.8, "road");
    addRoute("Dallas", "San Antonio", 274.0, 0.6, "road");
    addRoute("San Jose", "San Francisco", 77.0, 0.3, "road");
    addRoute("Philadelphia", "New York", 97.0, 0.3, "road");
    addRoute("Philadelphia", "Washington DC", 225.0, 0.5, "road");
}

void PathFinder::addCity(const std::string& name, double lat, double lon, int population) {
    cities.emplace_back(name, lat, lon, population);
    city_indices[name] = cities.size() - 1;
}

void PathFinder::addRoute(const std::string& from, const std::string& to, double distance, double time, const std::string& transport) {
    if (cityExists(from) && cityExists(to)) {
        routes[{from, to}] = Route(from, to, distance, time, transport);
        routes[{to, from}] = Route(to, from, distance, time, transport); // Bidirectional
    }
}

std::vector<City> PathFinder::getCities() const {
    return cities;
}

std::vector<Route> PathFinder::getRoutes() const {
    std::vector<Route> route_list;
    for (const auto& route_pair : routes) {
        route_list.push_back(route_pair.second);
    }
    return route_list;
}

double PathFinder::calculateDistance(const City& city1, const City& city2) {
    const double R = 6371; // Earth's radius in kilometers
    double lat1 = city1.latitude * M_PI / 180;
    double lat2 = city2.latitude * M_PI / 180;
    double delta_lat = (city2.latitude - city1.latitude) * M_PI / 180;
    double delta_lon = (city2.longitude - city1.longitude) * M_PI / 180;
    
    double a = sin(delta_lat/2) * sin(delta_lat/2) +
               cos(lat1) * cos(lat2) *
               sin(delta_lon/2) * sin(delta_lon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    
    return R * c;
}

double PathFinder::calculateTime(const Route& route, const std::string& transport_type) {
    double speed = 60.0; // Default speed in km/h
    
    if (transport_type == "air") {
        speed = 800.0; // Average airplane speed
    } else if (transport_type == "rail") {
        speed = 120.0; // Average train speed
    } else if (transport_type == "road") {
        speed = 80.0; // Average road speed
    }
    
    return route.distance / speed;
}

std::vector<std::string> PathFinder::reconstructPath(const std::vector<int>& previous, int start, int end) {
    std::vector<std::string> path;
    int current = end;
    
    while (current != -1) {
        path.push_back(cities[current].name);
        current = previous[current];
    }
    
    std::reverse(path.begin(), path.end());
    return path;
}

PathResult PathFinder::findShortestPath(const std::string& source, const std::string& destination, const std::string& algorithm) {
    if (algorithm == "dijkstra") {
        return dijkstraShortestPath(source, destination);
    } else if (algorithm == "bellman-ford") {
        return bellmanFordShortestPath(source, destination);
    } else if (algorithm == "floyd-warshall") {
        return floydWarshallShortestPath(source, destination);
    } else if (algorithm == "a-star") {
        return aStarShortestPath(source, destination);
    } else {
        std::cerr << "Unknown algorithm: " << algorithm << ". Using Dijkstra." << std::endl;
        return dijkstraShortestPath(source, destination);
    }
}

PathResult PathFinder::dijkstraShortestPath(const std::string& source, const std::string& destination) {
    PathResult result;
    result.algorithm_used = "Dijkstra";
    
    if (!cityExists(source) || !cityExists(destination)) {
        std::cerr << "Source or destination city not found!" << std::endl;
        return result;
    }
    
    int start = city_indices[source];
    int end = city_indices[destination];
    int n = cities.size();
    
    std::vector<double> distances(n, std::numeric_limits<double>::infinity());
    std::vector<int> previous(n, -1);
    std::vector<bool> visited(n, false);
    
    distances[start] = 0;
    
    for (int i = 0; i < n; ++i) {
        // Find unvisited vertex with minimum distance
        int u = -1;
        double min_dist = std::numeric_limits<double>::infinity();
        
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && distances[j] < min_dist) {
                min_dist = distances[j];
                u = j;
            }
        }
        
        if (u == -1) break;
        visited[u] = true;
        
        if (u == end) break;
        
        // Update distances to neighbors
        for (int v = 0; v < n; ++v) {
            if (!visited[v]) {
                std::string from = cities[u].name;
                std::string to = cities[v].name;
                
                if (routeExists(from, to)) {
                    double weight = routes[{from, to}].distance;
                    if (distances[u] + weight < distances[v]) {
                        distances[v] = distances[u] + weight;
                        previous[v] = u;
                    }
                }
            }
        }
    }
    
    if (distances[end] == std::numeric_limits<double>::infinity()) {
        std::cerr << "No path found from " << source << " to " << destination << std::endl;
        return result;
    }
    
    result.path = reconstructPath(previous, start, end);
    result.total_distance = distances[end];
    
    // Calculate total time and route details
    for (size_t i = 0; i < result.path.size() - 1; ++i) {
        std::string from = result.path[i];
        std::string to = result.path[i + 1];
        
        if (routeExists(from, to)) {
            Route route = routes[{from, to}];
            result.route_details.push_back(route);
            result.total_time += route.time;
        }
    }
    
    return result;
}

PathResult PathFinder::bellmanFordShortestPath(const std::string& source, const std::string& destination) {
    PathResult result;
    result.algorithm_used = "Bellman-Ford";
    
    if (!cityExists(source) || !cityExists(destination)) {
        std::cerr << "Source or destination city not found!" << std::endl;
        return result;
    }
    
    int start = city_indices[source];
    int end = city_indices[destination];
    int n = cities.size();
    
    std::vector<double> distances(n, std::numeric_limits<double>::infinity());
    std::vector<int> previous(n, -1);
    
    distances[start] = 0;
    
    // Relax edges n-1 times
    for (int i = 0; i < n - 1; ++i) {
        for (const auto& route_pair : routes) {
            const Route& route = route_pair.second;
            int u = city_indices[route.from];
            int v = city_indices[route.to];
            
            if (distances[u] != std::numeric_limits<double>::infinity() &&
                distances[u] + route.distance < distances[v]) {
                distances[v] = distances[u] + route.distance;
                previous[v] = u;
            }
        }
    }
    
    if (distances[end] == std::numeric_limits<double>::infinity()) {
        std::cerr << "No path found from " << source << " to " << destination << std::endl;
        return result;
    }
    
    result.path = reconstructPath(previous, start, end);
    result.total_distance = distances[end];
    
    // Calculate total time and route details
    for (size_t i = 0; i < result.path.size() - 1; ++i) {
        std::string from = result.path[i];
        std::string to = result.path[i + 1];
        
        if (routeExists(from, to)) {
            Route route = routes[{from, to}];
            result.route_details.push_back(route);
            result.total_time += route.time;
        }
    }
    
    return result;
}

PathResult PathFinder::floydWarshallShortestPath(const std::string& source, const std::string& destination) {
    PathResult result;
    result.algorithm_used = "Floyd-Warshall";
    
    if (!cityExists(source) || !cityExists(destination)) {
        std::cerr << "Source or destination city not found!" << std::endl;
        return result;
    }
    
    int start = city_indices[source];
    int end = city_indices[destination];
    int n = cities.size();
    
    // Initialize distance and next matrices
    std::vector<std::vector<double>> dist(n, std::vector<double>(n, std::numeric_limits<double>::infinity()));
    std::vector<std::vector<int>> next(n, std::vector<int>(n, -1));
    
    // Set diagonal to 0 and initialize direct edges
    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
    }
    
    for (const auto& route_pair : routes) {
        const Route& route = route_pair.second;
        int u = city_indices[route.from];
        int v = city_indices[route.to];
        dist[u][v] = route.distance;
        next[u][v] = v;
    }
    
    // Floyd-Warshall algorithm
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != std::numeric_limits<double>::infinity() &&
                    dist[k][j] != std::numeric_limits<double>::infinity() &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
    
    if (dist[start][end] == std::numeric_limits<double>::infinity()) {
        std::cerr << "No path found from " << source << " to " << destination << std::endl;
        return result;
    }
    
    // Reconstruct path
    std::vector<std::string> path;
    int current = start;
    while (current != end) {
        path.push_back(cities[current].name);
        current = next[current][end];
    }
    path.push_back(cities[end].name);
    
    result.path = path;
    result.total_distance = dist[start][end];
    
    // Calculate total time and route details
    for (size_t i = 0; i < result.path.size() - 1; ++i) {
        std::string from = result.path[i];
        std::string to = result.path[i + 1];
        
        if (routeExists(from, to)) {
            Route route = routes[{from, to}];
            result.route_details.push_back(route);
            result.total_time += route.time;
        }
    }
    
    return result;
}

PathResult PathFinder::aStarShortestPath(const std::string& source, const std::string& destination) {
    PathResult result;
    result.algorithm_used = "A*";
    
    if (!cityExists(source) || !cityExists(destination)) {
        std::cerr << "Source or destination city not found!" << std::endl;
        return result;
    }
    
    int start = city_indices[source];
    int end = city_indices[destination];
    int n = cities.size();
    
    std::vector<double> g_score(n, std::numeric_limits<double>::infinity());
    std::vector<double> f_score(n, std::numeric_limits<double>::infinity());
    std::vector<int> previous(n, -1);
    std::set<int> open_set;
    
    g_score[start] = 0;
    f_score[start] = getHeuristicDistance(source, destination);
    open_set.insert(start);
    
    while (!open_set.empty()) {
        // Find node with lowest f_score
        int current = -1;
        double min_f = std::numeric_limits<double>::infinity();
        
        for (int node : open_set) {
            if (f_score[node] < min_f) {
                min_f = f_score[node];
                current = node;
            }
        }
        
        if (current == end) {
            break;
        }
        
        open_set.erase(current);
        
        // Check neighbors
        std::vector<std::string> neighbors = getNeighbors(cities[current].name);
        for (const std::string& neighbor_name : neighbors) {
            int neighbor = city_indices[neighbor_name];
            
            if (!routeExists(cities[current].name, neighbor_name)) continue;
            
            double tentative_g = g_score[current] + routes[{cities[current].name, neighbor_name}].distance;
            
            if (tentative_g < g_score[neighbor]) {
                previous[neighbor] = current;
                g_score[neighbor] = tentative_g;
                f_score[neighbor] = g_score[neighbor] + getHeuristicDistance(neighbor_name, destination);
                
                if (open_set.find(neighbor) == open_set.end()) {
                    open_set.insert(neighbor);
                }
            }
        }
    }
    
    if (g_score[end] == std::numeric_limits<double>::infinity()) {
        std::cerr << "No path found from " << source << " to " << destination << std::endl;
        return result;
    }
    
    result.path = reconstructPath(previous, start, end);
    result.total_distance = g_score[end];
    
    // Calculate total time and route details
    for (size_t i = 0; i < result.path.size() - 1; ++i) {
        std::string from = result.path[i];
        std::string to = result.path[i + 1];
        
        if (routeExists(from, to)) {
            Route route = routes[{from, to}];
            result.route_details.push_back(route);
            result.total_time += route.time;
        }
    }
    
    return result;
}

std::vector<PathResult> PathFinder::compareAlgorithms(const std::string& source, const std::string& destination) {
    std::vector<PathResult> results;
    
    std::vector<std::string> algorithms = {"dijkstra", "bellman-ford", "floyd-warshall", "a-star"};
    
    for (const std::string& algo : algorithms) {
        PathResult result = findShortestPath(source, destination, algo);
        results.push_back(result);
    }
    
    return results;
}

void PathFinder::analyzeNetwork() {
    std::cout << "\n=== Network Analysis ===" << std::endl;
    std::cout << "Cities: " << cities.size() << std::endl;
    std::cout << "Routes: " << routes.size() / 2 << " (bidirectional)" << std::endl;
    
    // Find most connected city
    std::map<std::string, int> connections;
    for (const auto& route_pair : routes) {
        connections[route_pair.second.from]++;
    }
    
    auto max_connections = std::max_element(connections.begin(), connections.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; });
    
    if (max_connections != connections.end()) {
        std::cout << "Most connected city: " << max_connections->first 
                  << " (" << max_connections->second << " connections)" << std::endl;
    }
}

std::map<std::string, double> PathFinder::getCityDistances(const std::string& source) {
    std::map<std::string, double> distances;
    
    for (const City& city : cities) {
        if (city.name != source) {
            PathResult result = dijkstraShortestPath(source, city.name);
            distances[city.name] = result.total_distance;
        }
    }
    
    return distances;
}

bool PathFinder::cityExists(const std::string& name) const {
    return city_indices.find(name) != city_indices.end();
}

bool PathFinder::routeExists(const std::string& from, const std::string& to) const {
    return routes.find({from, to}) != routes.end();
}

double PathFinder::getHeuristicDistance(const std::string& from, const std::string& to) {
    if (!cityExists(from) || !cityExists(to)) {
        return std::numeric_limits<double>::infinity();
    }
    
    const City& city1 = cities[city_indices.at(from)];
    const City& city2 = cities[city_indices.at(to)];
    
    return calculateDistance(city1, city2);
}

std::vector<std::string> PathFinder::getNeighbors(const std::string& city) {
    std::vector<std::string> neighbors;
    
    for (const auto& route_pair : routes) {
        if (route_pair.second.from == city) {
            neighbors.push_back(route_pair.second.to);
        }
    }
    
    return neighbors;
}

void PathFinder::exportPathToFile(const PathResult& result, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not create file " << filename << std::endl;
        return;
    }
    
    file << "Pathfinding Result Report" << std::endl;
    file << "=========================" << std::endl;
    file << "Algorithm: " << result.algorithm_used << std::endl;
    file << "Total Distance: " << std::fixed << std::setprecision(2) << result.total_distance << " km" << std::endl;
    file << "Total Time: " << std::fixed << std::setprecision(2) << result.total_time << " hours" << std::endl;
    file << std::endl;
    
    file << "Path:" << std::endl;
    for (size_t i = 0; i < result.path.size(); ++i) {
        file << (i + 1) << ". " << result.path[i];
        if (i < result.path.size() - 1) {
            file << " -> ";
        }
    }
    file << std::endl << std::endl;
    
    file << "Route Details:" << std::endl;
    for (size_t i = 0; i < result.route_details.size(); ++i) {
        const Route& route = result.route_details[i];
        file << (i + 1) << ". " << route.from << " to " << route.to << std::endl;
        file << "   Distance: " << std::fixed << std::setprecision(2) << route.distance << " km" << std::endl;
        file << "   Time: " << std::fixed << std::setprecision(2) << route.time << " hours" << std::endl;
        file << "   Transport: " << route.transport_type << std::endl;
        file << std::endl;
    }
    
    file.close();
    std::cout << "Path exported to " << filename << std::endl;
}

void PathFinder::exportNetworkToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not create file " << filename << std::endl;
        return;
    }
    
    file << "City Network Data" << std::endl;
    file << "=================" << std::endl;
    
    file << "Cities:" << std::endl;
    for (const City& city : cities) {
        file << city.name << "," << city.latitude << "," << city.longitude << "," << city.population << std::endl;
    }
    
    file << std::endl << "Routes:" << std::endl;
    for (const auto& route_pair : routes) {
        const Route& route = route_pair.second;
        file << route.from << "," << route.to << "," << route.distance << "," << route.time << "," << route.transport_type << std::endl;
    }
    
    file.close();
    std::cout << "Network exported to " << filename << std::endl;
}

std::string PathFinder::generatePathReport(const PathResult& result) {
    std::ostringstream report;
    
    report << "Pathfinding Report" << std::endl;
    report << "==================" << std::endl;
    report << "Algorithm: " << result.algorithm_used << std::endl;
    report << "Total Distance: " << std::fixed << std::setprecision(2) << result.total_distance << " km" << std::endl;
    report << "Total Time: " << std::fixed << std::setprecision(2) << result.total_time << " hours" << std::endl;
    report << std::endl;
    
    report << "Path: ";
    for (size_t i = 0; i < result.path.size(); ++i) {
        report << result.path[i];
        if (i < result.path.size() - 1) {
            report << " -> ";
        }
    }
    report << std::endl;
    
    return report.str();
}
