#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <limits>

/**
 * Pathfinding Algorithms Implementation
 * Implements various graph traversal and shortest path algorithms
 */

struct City {
    std::string name;
    double latitude;
    double longitude;
    int population;
    
    City(const std::string& n, double lat, double lon, int pop) 
        : name(n), latitude(lat), longitude(lon), population(pop) {}
};

struct Route {
    std::string from;
    std::string to;
    double distance; // in kilometers
    double time;     // in hours
    std::string transport; // "air" or "road"
    
    Route(const std::string& f, const std::string& t, double dist, double t_time, const std::string& trans)
        : from(f), to(t), distance(dist), time(t_time), transport(trans) {}
};

struct PathResult {
    std::vector<std::string> path;
    double totalDistance;
    double totalTime;
    std::vector<Route> routeDetails;
    std::string algorithm;
    
    PathResult() : totalDistance(0.0), totalTime(0.0) {}
};

class PathfindingVisualizer {
private:
    std::vector<City> cities;
    std::vector<Route> routes;
    std::map<std::string, std::map<std::string, Route>> graph;
    
public:
    PathfindingVisualizer();
    
    // Graph building and management
    void buildGraph();
    void addCity(const City& city);
    void addRoute(const Route& route);
    
    // Pathfinding algorithms
            PathResult dijkstra(const std::string& source, const std::string& destination);
        PathResult breadthFirstSearch(const std::string& source, const std::string& destination);
        PathResult depthFirstSearch(const std::string& source, const std::string& destination);
    
    // Algorithm comparison
    std::vector<PathResult> compareAlgorithms(const std::string& source, const std::string& destination);
    
    // Utility functions
    double calculateHeuristic(const std::string& city1, const std::string& city2);
    std::vector<std::string> getNeighbors(const std::string& city);
    bool cityExists(const std::string& cityName);
    void printPath(const PathResult& result);
    
    // Data export/import
    void exportResults(const std::vector<PathResult>& results, const std::string& filename);
    void loadCitiesFromFile(const std::string& filename);
    void loadRoutesFromFile(const std::string& filename);
    
    // Analysis functions
    void analyzeGraphProperties();
    void findConnectedComponents();
    void calculateAveragePathLength();
    
private:
    // Helper functions for algorithms
    std::string findMinDistanceCity(const std::map<std::string, double>& distances, const std::set<std::string>& unvisited);
    std::vector<std::string> reconstructPath(const std::map<std::string, std::string>& previous, 
                                           const std::string& source, const std::string& destination);
    double haversineDistance(double lat1, double lon1, double lat2, double lon2);
    void dfsHelper(const std::string& current, const std::string& destination, 
                  std::map<std::string, bool>& visited, std::map<std::string, std::string>& previous,
                  bool& found);
};

#endif // PATHFINDING_H
