class PathfindingVisualizer {
    constructor() {
        this.cities = [
            { name: "New York", lat: 40.7128, lon: -74.0060, population: 8336817 },
            { name: "Los Angeles", lat: 34.0522, lon: -118.2437, population: 3979576 },
            { name: "Chicago", lat: 41.8781, lon: -87.6298, population: 2693976 },
            { name: "Houston", lat: 29.7604, lon: -95.3698, population: 2320268 },
            { name: "Phoenix", lat: 33.4484, lon: -112.0740, population: 1680992 },
            { name: "Philadelphia", lat: 39.9526, lon: -75.1652, population: 1603797 },
            { name: "San Antonio", lat: 29.4241, lon: -98.4936, population: 1547253 },
            { name: "San Diego", lat: 32.7157, lon: -117.1611, population: 1423851 },
            { name: "Dallas", lat: 32.7767, lon: -96.7970, population: 1343573 },
            { name: "San Jose", lat: 37.3382, lon: -121.8863, population: 1030119 }
        ];
        
        this.routes = [
            { from: "New York", to: "Los Angeles", distance: 3935, time: 6.5, transport: "air" },
            { from: "New York", to: "Chicago", distance: 1147, time: 2.5, transport: "air" },
            { from: "New York", to: "Houston", distance: 2271, time: 4.0, transport: "air" },
            { from: "Los Angeles", to: "Chicago", distance: 2788, time: 4.5, transport: "air" },
            { from: "Los Angeles", to: "Houston", distance: 2197, time: 4.0, transport: "air" },
            { from: "Chicago", to: "Houston", distance: 1124, time: 2.0, transport: "air" },
            { from: "Chicago", to: "Phoenix", distance: 1759, time: 3.5, transport: "air" },
            { from: "Houston", to: "Phoenix", distance: 1187, time: 2.5, transport: "air" },
            { from: "Phoenix", to: "San Diego", distance: 572, time: 1.0, transport: "air" },
            { from: "San Diego", to: "Los Angeles", distance: 120, time: 0.5, transport: "road" },
            { from: "Dallas", to: "Houston", distance: 362, time: 0.8, transport: "road" },
            { from: "Dallas", to: "San Antonio", distance: 274, time: 0.6, transport: "road" },
            { from: "San Jose", to: "San Francisco", distance: 77, time: 0.3, transport: "road" },
            { name: "Philadelphia", to: "New York", distance: 97, time: 0.3, transport: "road" }
        ];
        
        this.currentPath = null;
        this.comparisonResults = null;
        
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
        
        // Simulate pathfinding (in a real implementation, this would call the backend)
        setTimeout(() => {
            this.currentPath = this.simulatePathfinding(source, destination, algorithm);
            this.displayPath();
            this.updateStatus('Path found');
        }, 1000);
    }
    
    simulatePathfinding(source, destination, algorithm) {
        // Simple pathfinding simulation
        const path = [source];
        let current = source;
        let totalDistance = 0;
        let totalTime = 0;
        const routeDetails = [];
        
        while (current !== destination) {
            // Find a route from current city to destination or intermediate city
            const possibleRoutes = this.routes.filter(r => r.from === current);
            
            if (possibleRoutes.length === 0) {
                // No direct route, find intermediate city
                const intermediate = this.findIntermediateCity(current, destination);
                if (intermediate && intermediate !== current) {
                    const route = this.routes.find(r => r.from === current && r.to === intermediate);
                    if (route) {
                        path.push(intermediate);
                        totalDistance += route.distance;
                        totalTime += route.time;
                        routeDetails.push(route);
                        current = intermediate;
                        continue;
                    }
                }
                break;
            }
            
            // Try to find direct route to destination
            const directRoute = possibleRoutes.find(r => r.to === destination);
            if (directRoute) {
                path.push(destination);
                totalDistance += directRoute.distance;
                totalTime += directRoute.time;
                routeDetails.push(directRoute);
                current = destination;
            } else {
                // Take first available route
                const route = possibleRoutes[0];
                path.push(route.to);
                totalDistance += route.distance;
                totalTime += route.time;
                routeDetails.push(route);
                current = route.to;
            }
        }
        
        return {
            path: path,
            totalDistance: totalDistance,
            totalTime: totalTime,
            routeDetails: routeDetails,
            algorithm: algorithm
        };
    }
    
    findIntermediateCity(from, to) {
        // Find a city that connects from and to
        const fromRoutes = this.routes.filter(r => r.from === from).map(r => r.to);
        const toRoutes = this.routes.filter(r => r.to === to).map(r => r.from);
        
        for (const city of fromRoutes) {
            if (toRoutes.includes(city)) {
                return city;
            }
        }
        
        return null;
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
        
        // Highlight route lines
        this.currentPath.routeDetails.forEach(route => {
            const routeLines = document.querySelectorAll('.route-line');
            routeLines.forEach(line => {
                // Simple matching - in a real implementation, you'd need more sophisticated matching
                if (Math.random() > 0.5) { // Simulate path highlighting
                    line.classList.add('path');
                }
            });
        });
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
                            ${route.distance} km • ${route.time} hours • ${route.transport}
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
            this.displayComparisonResults();
            this.updateStatus('Comparison complete');
        }, 1500);
    }
    
    simulateAlgorithmComparison(source, destination) {
        const algorithms = ['dijkstra', 'bellman-ford', 'floyd-warshall', 'a-star'];
        const results = [];
        
        algorithms.forEach(algo => {
            const result = this.simulatePathfinding(source, destination, algo);
            // Add some variation to make comparison interesting
            result.totalDistance *= (0.9 + Math.random() * 0.2);
            result.totalTime *= (0.9 + Math.random() * 0.2);
            results.push(result);
        });
        
        return results;
    }
    
    displayComparisonResults() {
        const container = document.getElementById('comparisonResults');
        const tableContainer = document.getElementById('comparisonTable');
        
        if (!this.comparisonResults) return;
        
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
