#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <vector>
#include <string>
#include <map>
#include <utility>
#include <limits>

struct City {
    std::string name;
    double latitude;
    double longitude;
    int population;
    
    City(const std::string& n, double lat, double lon, int pop = 0) 
        : name(n), latitude(lat), longitude(lon), population(pop) {}
};

struct Route {
    std::string from;
    std::string to;
    double distance;  // in kilometers
    double time;      // in hours (assuming average speed)
    std::string transport_type; // "road", "rail", "air"
    
    Route(const std::string& f, const std::string& t, double dist, double t_time, const std::string& type = "road")
        : from(f), to(t), distance(dist), time(t_time), transport_type(type) {}
};

struct PathResult {
    std::vector<std::string> path;
    double total_distance;
    double total_time;
    std::vector<Route> route_details;
    std::string algorithm_used;
    
    PathResult() : total_distance(0.0), total_time(0.0) {}
};

class PathFinder {
private:
    std::vector<City> cities;
    std::map<std::pair<std::string, std::string>, Route> routes;
    std::map<std::string, int> city_indices;
    
    double calculateDistance(const City& city1, const City& city2);
    double calculateTime(const Route& route, const std::string& transport_type);
    std::vector<std::string> reconstructPath(const std::vector<int>& previous, int start, int end);
    
public:
    PathFinder();
    
    // City management
    void addCity(const std::string& name, double lat, double lon, int population = 0);
    void addRoute(const std::string& from, const std::string& to, double distance, double time, const std::string& transport = "road");
    std::vector<City> getCities() const;
    std::vector<Route> getRoutes() const;
    
    // Pathfinding algorithms
    PathResult findShortestPath(const std::string& source, const std::string& destination, const std::string& algorithm = "dijkstra");
    PathResult dijkstraShortestPath(const std::string& source, const std::string& destination);
    PathResult bellmanFordShortestPath(const std::string& source, const std::string& destination);
    PathResult floydWarshallShortestPath(const std::string& source, const std::string& destination);
    PathResult aStarShortestPath(const std::string& source, const std::string& destination);
    
    // Analysis and comparison
    std::vector<PathResult> compareAlgorithms(const std::string& source, const std::string& destination);
    void analyzeNetwork();
    std::map<std::string, double> getCityDistances(const std::string& source);
    
    // Utility functions
    bool cityExists(const std::string& name) const;
    bool routeExists(const std::string& from, const std::string& to) const;
    double getHeuristicDistance(const std::string& from, const std::string& to);
    std::vector<std::string> getNeighbors(const std::string& city);
    
    // Export functions
    void exportPathToFile(const PathResult& result, const std::string& filename);
    void exportNetworkToFile(const std::string& filename);
    std::string generatePathReport(const PathResult& result);
};

#endif // PATHFINDING_H
