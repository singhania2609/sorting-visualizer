class PathfindingVisualizer {
    constructor() {
        this.cities = [
            { name: "Mumbai", lat: 19.0760, lon: 72.8777 },
            { name: "Delhi", lat: 28.7041, lon: 77.1025 },
            { name: "Bangalore", lat: 12.9716, lon: 77.5946 },
            { name: "Hyderabad", lat: 17.3850, lon: 78.4867 },
            { name: "Chennai", lat: 13.0827, lon: 80.2707 },
            { name: "Kolkata", lat: 22.5726, lon: 88.3639 },
            { name: "Pune", lat: 18.5204, lon: 73.8567 },
            { name: "Ahmedabad", lat: 23.0225, lon: 72.5714 },
            { name: "Jaipur", lat: 26.9124, lon: 75.7873 },
            { name: "Surat", lat: 21.1702, lon: 72.8311 },
            { name: "Lucknow", lat: 26.8467, lon: 80.9462 },
            { name: "Kanpur", lat: 26.4499, lon: 80.3319 },
            { name: "Nagpur", lat: 21.1458, lon: 79.0882 },
            { name: "Indore", lat: 22.7196, lon: 75.8577 },
            { name: "Thane", lat: 19.2183, lon: 72.9781 },
            { name: "Bhopal", lat: 23.2599, lon: 77.4126 },
            { name: "Visakhapatnam", lat: 17.6868, lon: 83.2185 },
            { name: "Patna", lat: 25.5941, lon: 85.1376 },
            { name: "Vadodara", lat: 22.3072, lon: 73.1812 },
            { name: "Ghaziabad", lat: 28.6692, lon: 77.4538 }
        ];
        
        this.routes = [
            // City connections (simplified without transport modes)
            { from: "Mumbai", to: "Delhi", distance: 1154, time: 2.0 },
            { from: "Mumbai", to: "Bangalore", distance: 983, time: 1.8 },
            { from: "Mumbai", to: "Hyderabad", distance: 707, time: 1.5 },
            { from: "Mumbai", to: "Chennai", distance: 1038, time: 1.9 },
            { from: "Mumbai", to: "Kolkata", distance: 1654, time: 2.5 },
            { from: "Delhi", to: "Bangalore", distance: 1740, time: 2.8 },
            { from: "Delhi", to: "Hyderabad", distance: 1215, time: 2.2 },
            { from: "Delhi", to: "Chennai", distance: 1760, time: 2.9 },
            { from: "Delhi", to: "Kolkata", distance: 1304, time: 2.1 },
            { from: "Delhi", to: "Jaipur", distance: 268, time: 0.8 },
            { from: "Delhi", to: "Lucknow", distance: 497, time: 1.2 },
            { from: "Delhi", to: "Kanpur", distance: 432, time: 1.0 },
            { from: "Delhi", to: "Bhopal", distance: 588, time: 1.4 },
            { from: "Delhi", to: "Patna", distance: 847, time: 1.8 },
            { from: "Delhi", to: "Ghaziabad", distance: 19, time: 0.5 },
            { from: "Bangalore", to: "Hyderabad", distance: 569, time: 1.2 },
            { from: "Bangalore", to: "Chennai", distance: 347, time: 0.8 },
            { from: "Bangalore", to: "Pune", distance: 619, time: 1.3 },
            { from: "Hyderabad", to: "Chennai", distance: 626, time: 1.1 },
            { from: "Hyderabad", to: "Visakhapatnam", distance: 671, time: 1.3 },
            { from: "Chennai", to: "Kolkata", distance: 1359, time: 2.3 },
            { from: "Chennai", to: "Visakhapatnam", distance: 800, time: 1.5 },
            { from: "Kolkata", to: "Patna", distance: 532, time: 1.1 },
            { from: "Kolkata", to: "Visakhapatnam", distance: 883, time: 1.7 },
            { from: "Pune", to: "Mumbai", distance: 148, time: 0.5 },
            { from: "Pune", to: "Ahmedabad", distance: 655, time: 1.4 },
            { from: "Ahmedabad", to: "Mumbai", distance: 523, time: 1.1 },
            { from: "Ahmedabad", to: "Surat", distance: 263, time: 0.6 },
            { from: "Ahmedabad", to: "Vadodara", distance: 110, time: 0.3 },
            { from: "Jaipur", to: "Ahmedabad", distance: 650, time: 1.3 },
            { from: "Jaipur", to: "Bhopal", distance: 598, time: 1.2 },
            { from: "Surat", to: "Mumbai", distance: 260, time: 0.6 },
            { from: "Surat", to: "Vadodara", distance: 153, time: 0.4 },
            { from: "Lucknow", to: "Kanpur", distance: 79, time: 0.3 },
            { from: "Lucknow", to: "Patna", distance: 350, time: 0.8 },
            { from: "Kanpur", to: "Bhopal", distance: 156, time: 0.4 },
            { from: "Nagpur", to: "Bhopal", distance: 245, time: 0.6 },
            { from: "Nagpur", to: "Hyderabad", distance: 500, time: 1.0 },
            { from: "Indore", to: "Bhopal", distance: 186, time: 0.4 },
            { from: "Indore", to: "Mumbai", distance: 585, time: 1.2 },
            { from: "Thane", to: "Mumbai", distance: 25, time: 0.1 },
            { from: "Thane", to: "Pune", distance: 123, time: 0.3 },
            { from: "Bhopal", to: "Indore", distance: 186, time: 0.4 },
            { from: "Bhopal", to: "Nagpur", distance: 245, time: 0.6 },
            { from: "Visakhapatnam", to: "Hyderabad", distance: 671, time: 1.3 },
            { from: "Visakhapatnam", to: "Chennai", distance: 800, time: 1.5 },
            { from: "Patna", to: "Kolkata", distance: 532, time: 1.1 },
            { from: "Patna", to: "Lucknow", distance: 350, time: 0.8 },
            { from: "Vadodara", to: "Ahmedabad", distance: 110, time: 0.3 },
            { from: "Vadodara", to: "Surat", distance: 153, time: 0.4 },
            { from: "Ghaziabad", to: "Delhi", distance: 19, time: 0.5 },
            { from: "Ghaziabad", to: "Lucknow", distance: 478, time: 1.1 }
        ];
        
        this.currentPath = null;
        this.comparisonResults = null;
        this.person = null; // Person character for path animation
        
        this.initializeEventListeners();
        this.populateCitySelects();
        this.renderMap();
    }
    
    initializeEventListeners() {
        document.getElementById('findPathBtn').addEventListener('click', () => this.findPath());
        document.getElementById('compareBtn').addEventListener('click', () => this.compareAlgorithms());
        document.getElementById('resetBtn').addEventListener('click', () => this.reset());
        document.getElementById('exportBtn').addEventListener('click', () => this.exportResults());
    }
    
    populateCitySelects() {
        const sourceSelect = document.getElementById('sourceCity');
        const destSelect = document.getElementById('destCity');
        
        this.cities.forEach(city => {
            const sourceOption = document.createElement('option');
            sourceOption.value = city.name;
            sourceOption.textContent = city.name;
            sourceSelect.appendChild(sourceOption);
            
            const destOption = document.createElement('option');
            destOption.value = city.name;
            destOption.textContent = city.name;
            destSelect.appendChild(destOption);
        });
    }
    
    renderMap() {
        const container = document.getElementById('mapContainer');
        container.innerHTML = '';
        
        // Calculate map bounds
        const bounds = this.calculateMapBounds();
        const mapWidth = container.offsetWidth;
        const mapHeight = container.offsetHeight;
        const padding = 40;
        
        // Render cities
        this.cities.forEach(city => {
            const x = ((city.lon - bounds.minLon) / (bounds.maxLon - bounds.minLon)) * (mapWidth - 2 * padding) + padding;
            const y = ((bounds.maxLat - city.lat) / (bounds.maxLat - bounds.minLat)) * (mapHeight - 2 * padding) + padding;
            
            const cityNode = document.createElement('div');
            cityNode.className = 'city-node';
            cityNode.style.left = x + 'px';
            cityNode.style.top = y + 'px';
            cityNode.textContent = city.name.charAt(0);
            cityNode.title = city.name;
            
            const cityLabel = document.createElement('div');
            cityLabel.className = 'city-label';
            cityLabel.textContent = city.name;
            cityLabel.style.left = (x + 15) + 'px';
            cityLabel.style.top = (y - 10) + 'px';
            
            container.appendChild(cityNode);
            container.appendChild(cityLabel);
        });
        
        // Render routes
        this.routes.forEach(route => {
            const fromCity = this.cities.find(c => c.name === route.from);
            const toCity = this.cities.find(c => c.name === route.to);
            
            if (fromCity && toCity) {
                const x1 = ((fromCity.lon - bounds.minLon) / (bounds.maxLon - bounds.minLon)) * (mapWidth - 2 * padding) + padding;
                const y1 = ((bounds.maxLat - fromCity.lat) / (bounds.maxLat - bounds.minLat)) * (mapHeight - 2 * padding) + padding;
                const x2 = ((toCity.lon - bounds.minLon) / (bounds.maxLon - bounds.minLon)) * (mapWidth - 2 * padding) + padding;
                const y2 = ((bounds.maxLat - toCity.lat) / (bounds.maxLat - bounds.minLat)) * (mapHeight - 2 * padding) + padding;
                
                const routeLine = document.createElement('div');
                routeLine.className = 'route-line';
                routeLine.style.left = x1 + 'px';
                routeLine.style.top = (y1 - 1) + 'px';
                routeLine.style.width = Math.sqrt(Math.pow(x2 - x1, 2) + Math.pow(y2 - y1, 2)) + 'px';
                routeLine.style.transform = `rotate(${Math.atan2(y2 - y1, x2 - x1) * 180 / Math.PI}deg)`;
                
                container.appendChild(routeLine);
            }
        });
        
        // Create person character
        this.createPerson();
    }
    
    // Create the person character
    createPerson() {
        const container = document.getElementById('mapContainer');
        
        this.person = document.createElement('div');
        this.person.className = 'person-character';
        this.person.innerHTML = '👤';
        this.person.style.position = 'absolute';
        this.person.style.fontSize = '20px';
        this.person.style.zIndex = '1000';
        this.person.style.transition = 'all 0.5s ease-in-out';
        this.person.style.display = 'none';
        this.person.style.cursor = 'pointer';
        this.person.title = 'Click for journey details';
        
        // Add click event for person details
        this.person.addEventListener('click', () => this.showPersonDetails());
        
        container.appendChild(this.person);
    }
    
    // Show detailed information about the person's journey
    showPersonDetails() {
        if (!this.currentPath) return;
        
        const details = `
            🧭 Journey Details:
            
            🚀 Algorithm: ${this.currentPath.algorithm}
            📍 Total Cities: ${this.currentPath.path.length}
            🛣️ Total Distance: ${this.currentPath.totalDistance.toFixed(1)} km
            ⏱️ Total Time: ${this.currentPath.totalTime.toFixed(1)} hours
            
            🛤️ Route: ${this.currentPath.path.join(' → ')}
            
            💡 Click OK to continue watching the journey!
        `;
        
        alert(details);
    }
    
    // Get city position on map
    getCityPosition(cityName) {
        const bounds = this.calculateMapBounds();
        const container = document.getElementById('mapContainer');
        const mapWidth = container.offsetWidth;
        const mapHeight = container.offsetHeight;
        const padding = 40;
        
        const city = this.cities.find(c => c.name === cityName);
        if (!city) return null;
        
        const x = ((city.lon - bounds.minLon) / (bounds.maxLon - bounds.minLon)) * (mapWidth - 2 * padding) + padding;
        const y = ((bounds.maxLat - city.lat) / (bounds.maxLat - bounds.minLat)) * (mapHeight - 2 * padding) + padding;
        
        return { x, y };
    }
    
    // Animate person moving along the path
    animatePersonAlongPath() {
        if (!this.currentPath || !this.person) return;
        
        this.person.style.display = 'block';
        
        // Start from source city
        const sourcePos = this.getCityPosition(this.currentPath.path[0]);
        if (sourcePos) {
            this.person.style.left = (sourcePos.x - 10) + 'px';
            this.person.style.top = (sourcePos.y - 10) + 'px';
        }
        
        // Show progress info
        this.showPersonProgress(0);
        
        // Animate through each city in the path
        this.animatePersonStep(0);
    }
    
    // Show person's current progress
    showPersonProgress(stepIndex) {
        const progressContainer = document.getElementById('personProgress');
        if (!progressContainer) {
            // Create progress container if it doesn't exist
            const infoPanel = document.querySelector('.info-panel');
            const progressDiv = document.createElement('div');
            progressDiv.className = 'info-card';
            progressDiv.id = 'personProgress';
            progressDiv.innerHTML = `
                <h3>👤 Current Location</h3>
                <div class="value" id="personLocation">-</div>
            `;
            infoPanel.appendChild(progressDiv);
        }
        
        if (stepIndex < this.currentPath.path.length) {
            const currentCity = this.currentPath.path[stepIndex];
            const progress = Math.round(((stepIndex + 1) / this.currentPath.path.length) * 100);
            document.getElementById('personLocation').textContent = `${currentCity} (${progress}% complete)`;
        }
    }
    
    // Animate person moving to next city
    animatePersonStep(stepIndex) {
        if (stepIndex >= this.currentPath.path.length - 1) {
            // Reached destination
            this.showPersonProgress(this.currentPath.path.length - 1);
            setTimeout(() => {
                this.person.style.display = 'none';
                // Show completion message
                document.getElementById('personLocation').textContent = '🎉 Destination reached!';
            }, 1000);
            return;
        }
        
        const currentCity = this.currentPath.path[stepIndex];
        const nextCity = this.currentPath.path[stepIndex + 1];
        const route = this.currentPath.routeDetails[stepIndex];
        
        const currentPos = this.getCityPosition(currentCity);
        const nextPos = this.getCityPosition(nextCity);
        
        if (currentPos && nextPos) {
            // Update progress
            this.showPersonProgress(stepIndex);
            
            // Calculate movement duration (simplified without transport modes)
            const moveDuration = 500; // Standard movement speed
            
            // Move person to next city
            setTimeout(() => {
                this.person.style.left = (nextPos.x - 10) + 'px';
                this.person.style.top = (nextPos.y - 10) + 'px';
                
                // Continue to next step
                setTimeout(() => {
                    this.animatePersonStep(stepIndex + 1);
                }, moveDuration + 200);
            }, 500);
        }
    }
    

    
    calculateMapBounds() {
        const lats = this.cities.map(c => c.lat);
        const lons = this.cities.map(c => c.lon);
        
        return {
            minLat: Math.min(...lats),
            maxLat: Math.max(...lats),
            minLon: Math.min(...lons),
            maxLon: Math.max(...lons)
        };
    }
    
    findPath() {
        const source = document.getElementById('sourceCity').value;
        const destination = document.getElementById('destCity').value;
        const algorithm = document.getElementById('algorithm').value;
        
        if (!source || !destination) {
            alert('Please select both source and destination cities.');
            return;
        }
        
        if (source === destination) {
            alert('Source and destination cities must be different.');
            return;
        }
        
        this.updateStatus('Finding path...');
        
        // Use the selected algorithm to find the path
        setTimeout(() => {
            let result;
            switch (algorithm) {
                case 'dijkstra':
                    result = this.dijkstra(source, destination);
                    break;
                case 'bfs':
                    result = this.bfs(source, destination);
                    break;
                case 'dfs':
                    result = this.dfs(source, destination);
                    break;
                case 'bellman-ford':
                    result = this.bellmanFord(source, destination);
                    break;
                case 'floyd-warshall':
                    result = this.floydWarshall(source, destination);
                    break;
                default:
                    result = this.dijkstra(source, destination);
            }
            
            if (result) {
                this.currentPath = result;
                this.displayPath();
                this.updateStatus('Path found');
            } else {
                this.updateStatus('No path found');
                alert('No path found between the selected cities. Please try different cities.');
            }
        }, 1000);
    }
    
    // Dijkstra's Algorithm
    dijkstra(source, destination) {
        const distances = {};
        const previous = {};
        const unvisited = new Set();
        const graph = this.buildGraph();
        
        // Initialize distances
        this.cities.forEach(city => {
            distances[city.name] = Infinity;
            unvisited.add(city.name);
        });
        distances[source] = 0;
        
        while (unvisited.size > 0) {
            // Find unvisited city with minimum distance
            let current = null;
            let minDistance = Infinity;
            
            for (const city of unvisited) {
                if (distances[city] < minDistance) {
                    minDistance = distances[city];
                    current = city;
                }
            }
            
            if (current === null || current === destination) break;
            
            unvisited.delete(current);
            
            // Update distances to neighbors
            if (graph[current]) {
                for (const neighbor in graph[current]) {
                    if (unvisited.has(neighbor)) {
                        const newDistance = distances[current] + graph[current][neighbor].distance;
                        if (newDistance < distances[neighbor]) {
                            distances[neighbor] = newDistance;
                            previous[neighbor] = current;
                        }
                    }
                }
            }
        }
        
        return this.reconstructPath(source, destination, previous, distances, 'dijkstra');
    }
    
    // Breadth-First Search
    bfs(source, destination) {
        const queue = [{ city: source, path: [source], distance: 0, time: 0 }];
        const visited = new Set();
        const graph = this.buildGraph();
        
        while (queue.length > 0) {
            const { city, path, distance, time } = queue.shift();
            
            if (city === destination) {
                return {
                    path: path,
                    totalDistance: distance,
                    totalTime: time,
                    routeDetails: this.getRouteDetails(path),
                    algorithm: 'bfs'
                };
            }
            
            if (visited.has(city)) continue;
            visited.add(city);
            
            if (graph[city]) {
                for (const neighbor in graph[city]) {
                    if (!visited.has(neighbor)) {
                        const route = graph[city][neighbor];
                        queue.push({
                            city: neighbor,
                            path: [...path, neighbor],
                            distance: distance + route.distance,
                            time: time + route.time
                        });
                    }
                }
            }
        }
        
        return null;
    }
    
    // DFS Algorithm
    dfs(source, destination) {
        const visited = new Set();
        const cameFrom = {};
        let found = false;
        const graph = this.buildGraph();
        
        const dfsHelper = (current, path = [source], distance = 0, time = 0) => {
            if (found || visited.has(current)) return null;
            
            visited.add(current);
            
            if (current === destination) {
                found = true;
                return {
                    path: path,
                    totalDistance: distance,
                    totalTime: time,
                    routeDetails: this.getRouteDetails(path),
                    algorithm: 'dfs'
                };
            }
            
            if (graph[current]) {
                for (const neighbor in graph[current]) {
                    if (!visited.has(neighbor) && !found) {
                        const route = graph[current][neighbor];
                        const result = dfsHelper(
                            neighbor, 
                            [...path, neighbor], 
                            distance + route.distance, 
                            time + route.time
                        );
                        if (result) return result;
                    }
                }
            }
            
            return null;
        };
        
        return dfsHelper(source) || {
            path: [],
            totalDistance: 0,
            totalTime: 0,
            routeDetails: [],
            algorithm: 'dfs'
        };
    }
    
    // Bellman-Ford Algorithm
    bellmanFord(source, destination) {
        const distances = {};
        const previous = {};
        const graph = this.buildGraph();
        
        // Initialize distances
        this.cities.forEach(city => {
            distances[city.name] = Infinity;
        });
        distances[source] = 0;
        
        // Relax edges V-1 times
        for (let i = 0; i < this.cities.length - 1; i++) {
            for (const route of this.routes) {
                const u = route.from;
                const v = route.to;
                const w = route.distance;
                
                if (distances[u] !== Infinity && distances[u] + w < distances[v]) {
                    distances[v] = distances[u] + w;
                    previous[v] = u;
                }
                
                // Check reverse edge (since our graph is undirected)
                if (distances[v] !== Infinity && distances[v] + w < distances[u]) {
                    distances[u] = distances[v] + w;
                    previous[u] = v;
                }
            }
        }
        
        // Check for negative weight cycles (though our graph doesn't have negative weights)
        for (const route of this.routes) {
            const u = route.from;
            const v = route.to;
            const w = route.distance;
            
            if (distances[u] !== Infinity && distances[u] + w < distances[v]) {
                console.warn("Negative weight cycle detected");
                return null;
            }
        }
        
        return this.reconstructPath(source, destination, previous, distances, 'bellman-ford');
    }
    
    // Floyd-Warshall Algorithm
    floydWarshall(source, destination) {
        const n = this.cities.length;
        const cityNames = this.cities.map(city => city.name);
        const cityIndex = {};
        cityNames.forEach((name, index) => {
            cityIndex[name] = index;
        });
        
        // Initialize distance matrix
        const dist = Array(n).fill().map(() => Array(n).fill(Infinity));
        const next = Array(n).fill().map(() => Array(n).fill(null));
        
        // Initialize diagonal and direct edges
        for (let i = 0; i < n; i++) {
            dist[i][i] = 0;
        }
        
        // Add direct edges
        this.routes.forEach(route => {
            const u = cityIndex[route.from];
            const v = cityIndex[route.to];
            const w = route.distance;
            
            if (u !== undefined && v !== undefined) {
                dist[u][v] = w;
                dist[v][u] = w; // Undirected graph
                next[u][v] = v;
                next[v][u] = u;
            }
        });
        
        // Floyd-Warshall algorithm
        for (let k = 0; k < n; k++) {
            for (let i = 0; i < n; i++) {
                for (let j = 0; j < n; j++) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
        
        // Reconstruct path
        const sourceIndex = cityIndex[source];
        const destIndex = cityIndex[destination];
        
        if (dist[sourceIndex][destIndex] === Infinity) {
            return null;
        }
        
        const path = [];
        let current = sourceIndex;
        path.push(cityNames[current]);
        
        while (current !== destIndex) {
            current = next[current][destIndex];
            if (current === null) break;
            path.push(cityNames[current]);
        }
        
        // Calculate total time
        let totalTime = 0;
        for (let i = 0; i < path.length - 1; i++) {
            const route = this.routes.find(r => 
                (r.from === path[i] && r.to === path[i + 1]) ||
                (r.from === path[i + 1] && r.to === path[i])
            );
            if (route) {
                totalTime += route.time;
            }
        }
        
        return {
            path: path,
            totalDistance: dist[sourceIndex][destIndex],
            totalTime: totalTime,
            routeDetails: this.getRouteDetails(path),
            algorithm: 'floyd-warshall'
        };
    }
    
    // Heuristic function for A* (straight-line distance)
    heuristic(city1, city2) {
        const city1Data = this.cities.find(c => c.name === city1);
        const city2Data = this.cities.find(c => c.name === city2);
        
        if (!city1Data || !city2Data) return 0;
        
        const lat1 = city1Data.lat * Math.PI / 180;
        const lon1 = city1Data.lon * Math.PI / 180;
        const lat2 = city2Data.lat * Math.PI / 180;
        const lon2 = city2Data.lon * Math.PI / 180;
        
        const R = 6371; // Earth's radius in km
        const dLat = lat2 - lat1;
        const dLon = lon2 - lon1;
        
        const a = Math.sin(dLat/2) * Math.sin(dLat/2) +
                  Math.cos(lat1) * Math.cos(lat2) *
                  Math.sin(dLon/2) * Math.sin(dLon/2);
        const c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
        
        return R * c;
    }
    
    // Build graph from routes
    buildGraph() {
        const graph = {};
        
        this.routes.forEach(route => {
            if (!graph[route.from]) {
                graph[route.from] = {};
            }
            if (!graph[route.to]) {
                graph[route.to] = {};
            }
            
            graph[route.from][route.to] = route;
            // Add reverse route for undirected graph
            graph[route.to][route.from] = {
                from: route.to,
                to: route.from,
                distance: route.distance,
                time: route.time
            };
        });
        
        return graph;
    }
    
    // Reconstruct path from previous nodes
    reconstructPath(source, destination, previous, distances, algorithm) {
        const path = [];
        let current = destination;
        
        while (current !== source) {
            path.unshift(current);
            current = previous[current];
            if (!current) break;
        }
        
        if (current === source) {
            path.unshift(source);
        }
        
        const routeDetails = this.getRouteDetails(path);
        let totalDistance = 0;
        let totalTime = 0;
        
        routeDetails.forEach(route => {
            totalDistance += route.distance;
            totalTime += route.time;
        });
        
        return {
            path: path,
            totalDistance: totalDistance,
            totalTime: totalTime,
            routeDetails: routeDetails,
            algorithm: algorithm
        };
    }
    
    // Get route details for a path
    getRouteDetails(path) {
        const details = [];
        for (let i = 0; i < path.length - 1; i++) {
            const route = this.routes.find(r => 
                (r.from === path[i] && r.to === path[i + 1]) ||
                (r.from === path[i + 1] && r.to === path[i])
            );
            if (route) {
                details.push(route);
            }
        }
        return details;
    }
    
    displayPath() {
        if (!this.currentPath) return;
        
        // Update info panel
        document.getElementById('totalDistance').textContent = this.currentPath.totalDistance.toFixed(1) + ' km';
        document.getElementById('totalTime').textContent = this.currentPath.totalTime.toFixed(1) + ' hours';
        document.getElementById('algorithmUsed').textContent = this.currentPath.algorithm;
        
        // Update map visualization
        this.highlightPath();
        
        // Update path details
        this.displayPathDetails();
        
        // Start person animation
        setTimeout(() => {
            this.animatePersonAlongPath();
        }, 1000);
    }
    
    highlightPath() {
        // Reset all nodes and routes
        document.querySelectorAll('.city-node').forEach(node => {
            node.classList.remove('source', 'destination', 'path');
        });
        
        document.querySelectorAll('.route-line').forEach(line => {
            line.classList.remove('path');
        });
        
        // Highlight source and destination
        const sourceNode = document.querySelector(`[title="${this.currentPath.path[0]}"]`);
        const destNode = document.querySelector(`[title="${this.currentPath.path[this.currentPath.path.length - 1]}"]`);
        
        if (sourceNode) sourceNode.classList.add('source');
        if (destNode) destNode.classList.add('destination');
        
        // Highlight path nodes and routes
        for (let i = 1; i < this.currentPath.path.length - 1; i++) {
            const pathNode = document.querySelector(`[title="${this.currentPath.path[i]}"]`);
            if (pathNode) pathNode.classList.add('path');
        }
        
        // Highlight route lines for the actual path
        for (let i = 0; i < this.currentPath.path.length - 1; i++) {
            const from = this.currentPath.path[i];
            const to = this.currentPath.path[i + 1];
            
            // Find the route line that connects these two cities
            const routeLines = document.querySelectorAll('.route-line');
            routeLines.forEach(line => {
                // Check if this line connects the two cities in the path
                const lineFrom = this.getCityFromRouteLine(line, from);
                const lineTo = this.getCityFromRouteLine(line, to);
                
                if (lineFrom && lineTo && 
                    ((lineFrom === from && lineTo === to) || 
                     (lineFrom === to && lineTo === from))) {
                    line.classList.add('path');
                }
            });
        }
    }
    
    // Helper function to determine which cities a route line connects
    getCityFromRouteLine(line, cityName) {
        // This is a simplified approach - in a real implementation, you'd store more data
        // For now, we'll use the line's position and try to match it with city positions
        const cityNode = document.querySelector(`[title="${cityName}"]`);
        if (!cityNode) return null;
        
        const cityRect = cityNode.getBoundingClientRect();
        const lineRect = line.getBoundingClientRect();
        
        // Check if the line is close to this city
        const tolerance = 20; // pixels
        if (Math.abs(cityRect.left - lineRect.left) < tolerance && 
            Math.abs(cityRect.top - lineRect.top) < tolerance) {
            return cityName;
        }
        
        return null;
    }
    
    displayPathDetails() {
        const detailsContainer = document.getElementById('pathDetails');
        
        if (!this.currentPath || this.currentPath.path.length === 0) {
            detailsContainer.innerHTML = '<p>No path found.</p>';
            return;
        }
        
        let html = '<div class="path-steps">';
        
        for (let i = 0; i < this.currentPath.path.length - 1; i++) {
            const from = this.currentPath.path[i];
            const to = this.currentPath.path[i + 1];
            const route = this.currentPath.routeDetails[i];
            
            html += `
                <div class="path-step">
                    <div class="step-number">${i + 1}</div>
                    <div class="step-details">
                        <strong>${from}</strong> → <strong>${to}</strong>
                        <div class="route-info">
                            ${route.distance} km • ${route.time} hours
                        </div>
                    </div>
                </div>
            `;
        }
        
        html += '</div>';
        detailsContainer.innerHTML = html;
    }
    
    compareAlgorithms() {
        const source = document.getElementById('sourceCity').value;
        const destination = document.getElementById('destCity').value;
        
        if (!source || !destination) {
            alert('Please select both source and destination cities.');
            return;
        }
        
        this.updateStatus('Comparing algorithms...');
        
        setTimeout(() => {
            this.comparisonResults = this.simulateAlgorithmComparison(source, destination);
            if (this.comparisonResults) {
                this.displayComparisonResults();
                this.updateStatus('Comparison complete');
            }
        }, 1500);
    }
    
    simulateAlgorithmComparison(source, destination) {
        const algorithms = ['dijkstra', 'bfs', 'dfs', 'bellman-ford', 'floyd-warshall'];
        const results = [];
        
        algorithms.forEach(algo => {
            let result;
            switch (algo) {
                case 'dijkstra':
                    result = this.dijkstra(source, destination);
                    break;
                case 'bfs':
                    result = this.bfs(source, destination);
                    break;
                case 'dfs':
                    result = this.dfs(source, destination);
                    break;
                case 'bellman-ford':
                    result = this.bellmanFord(source, destination);
                    break;
                case 'floyd-warshall':
                    result = this.floydWarshall(source, destination);
                    break;
            }
            if (result) {
                results.push(result);
            }
        });
        
        if (results.length === 0) {
            alert('No path found between the selected cities by any algorithm. Please try different cities.');
            this.updateStatus('No paths found');
            return null;
        }
        
        return results;
    }
    
    displayComparisonResults() {
        const container = document.getElementById('comparisonResults');
        const tableContainer = document.getElementById('comparisonTable');
        
        if (!this.comparisonResults || this.comparisonResults.length === 0) {
            container.style.display = 'none';
            return;
        }
        
        let html = `
            <table class="comparison-table">
                <thead>
                    <tr>
                        <th>Algorithm</th>
                        <th>Distance (km)</th>
                        <th>Time (hours)</th>
                        <th>Path</th>
                    </tr>
                </thead>
                <tbody>
        `;
        
        let bestDistance = Math.min(...this.comparisonResults.map(r => r.totalDistance));
        let bestTime = Math.min(...this.comparisonResults.map(r => r.totalTime));
        
        this.comparisonResults.forEach(result => {
            const isBestDistance = result.totalDistance === bestDistance;
            const isBestTime = result.totalTime === bestTime;
            const rowClass = (isBestDistance || isBestTime) ? 'best-result' : '';
            
            html += `
                <tr class="${rowClass}">
                    <td>${result.algorithm}</td>
                    <td>${result.totalDistance.toFixed(1)}</td>
                    <td>${result.totalTime.toFixed(1)}</td>
                    <td>${result.path.join(' → ')}</td>
                </tr>
            `;
        });
        
        html += '</tbody></table>';
        tableContainer.innerHTML = html;
        container.style.display = 'block';
    }
    
    reset() {
        this.currentPath = null;
        this.comparisonResults = null;
        
        // Hide person character
        if (this.person) {
            this.person.style.display = 'none';
        }
        
        // Remove person progress display
        const progressContainer = document.getElementById('personProgress');
        if (progressContainer) {
            progressContainer.remove();
        }
        
        // Reset form
        document.getElementById('sourceCity').value = '';
        document.getElementById('destCity').value = '';
        document.getElementById('algorithm').value = 'dijkstra';
        
        // Reset display
        document.getElementById('totalDistance').textContent = '0 km';
        document.getElementById('totalTime').textContent = '0 hours';
        document.getElementById('algorithmUsed').textContent = '-';
        document.getElementById('status').textContent = 'Ready';
        document.getElementById('pathDetails').innerHTML = '<p>Select source and destination cities to find a path.</p>';
        document.getElementById('comparisonResults').style.display = 'none';
        
        // Reset map
        this.renderMap();
    }
    
    exportResults() {
        if (!this.currentPath && !this.comparisonResults) {
            alert('No results to export. Please find a path or compare algorithms first.');
            return;
        }
        
        let exportData = 'City Pathfinding Results\n';
        exportData += '========================\n\n';
        
        if (this.currentPath) {
            exportData += `Path: ${this.currentPath.path.join(' → ')}\n`;
            exportData += `Total Distance: ${this.currentPath.totalDistance.toFixed(1)} km\n`;
            exportData += `Total Time: ${this.currentPath.totalTime.toFixed(1)} hours\n`;
            exportData += `Algorithm: ${this.currentPath.algorithm}\n\n`;
        }
        
        if (this.comparisonResults) {
            exportData += 'Algorithm Comparison:\n';
            exportData += '====================\n';
            this.comparisonResults.forEach(result => {
                exportData += `${result.algorithm}: ${result.totalDistance.toFixed(1)} km, ${result.totalTime.toFixed(1)} hours\n`;
            });
        }
        
        // Create and download file
        const blob = new Blob([exportData], { type: 'text/plain' });
        const url = URL.createObjectURL(blob);
        const a = document.createElement('a');
        a.href = url;
        a.download = 'pathfinding_results.txt';
        document.body.appendChild(a);
        a.click();
        document.body.removeChild(a);
        URL.revokeObjectURL(url);
        
        this.updateStatus('Results exported');
    }
    
    updateStatus(status) {
        document.getElementById('status').textContent = status;
    }
}

// Initialize the visualizer when the page loads
document.addEventListener('DOMContentLoaded', () => {
    new PathfindingVisualizer();
});