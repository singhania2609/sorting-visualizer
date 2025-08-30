/**
 * Node.js HTTP Server for Algorithm Visualizers
 * Serves both Sorting and Pathfinding visualizers
 */

const http = require('http');
const fs = require('fs');
const path = require('path');
const url = require('url');

// Configuration
const PORT = 3000 || "https://sorting-visualizer-ggxr.onrender.com";
const DIRECTORY = 'frontend';

// MIME types for different file extensions
const mimeTypes = {
    '.html': 'text/html',
    '.js': 'text/javascript',
    '.css': 'text/css',
    '.json': 'application/json',
    '.png': 'image/png',
    '.jpg': 'image/jpeg',
    '.gif': 'image/gif',
    '.svg': 'image/svg+xml',
    '.ico': 'image/x-icon',
    '.txt': 'text/plain'
};

// Create HTTP server
const server = http.createServer((req, res) => {
    // Parse URL
    const parsedUrl = url.parse(req.url);
    let pathname = parsedUrl.pathname;
    
    // Default to combined.html if root is requested
    if (pathname === '/') {
        pathname = '/combined.html';
    }
    
    // Get file path
    const filePath = path.join(__dirname, DIRECTORY, pathname);
    
    // Get file extension
    const ext = path.extname(filePath).toLowerCase();
    const contentType = mimeTypes[ext] || 'application/octet-stream';
    
    // Read file
    fs.readFile(filePath, (err, data) => {
        if (err) {
            // File not found
            if (err.code === 'ENOENT') {
                res.writeHead(404, { 'Content-Type': 'text/html' });
                res.end(`
                    <!DOCTYPE html>
                    <html>
                    <head>
                        <title>404 - Page Not Found</title>
                        <style>
                            body { font-family: Arial, sans-serif; text-align: center; padding: 50px; }
                            .error { color: #e74c3c; font-size: 72px; margin-bottom: 20px; }
                            .message { color: #34495e; font-size: 18px; margin-bottom: 30px; }
                            .links { margin-top: 30px; }
                            .links a { display: inline-block; margin: 10px; padding: 10px 20px; 
                                      background: #3498db; color: white; text-decoration: none; 
                                      border-radius: 5px; }
                            .links a:hover { background: #2980b9; }
                        </style>
                    </head>
                    <body>
                        <div class="error">404</div>
                        <div class="message">Page not found: ${pathname}</div>
                        <div class="links">
                            <a href="/combined.html">🏠 Combined Interface</a>
                            <a href="/index.html">📊 Sorting Visualizer</a>
                            <a href="/pathfinding.html">🗺️ Pathfinding Visualizer</a>
                        </div>
                    </body>
                    </html>
                `);
            } else {
                // Server error
                res.writeHead(500, { 'Content-Type': 'text/plain' });
                res.end('Internal Server Error');
            }
            return;
        }
        
        // Set CORS headers
        res.setHeader('Access-Control-Allow-Origin', '*');
        res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS');
        res.setHeader('Access-Control-Allow-Headers', 'Content-Type');
        
        // Set content type and send response
        res.writeHead(200, { 'Content-Type': contentType });
        res.end(data);
    });
});

// Start server
server.listen(PORT, () => {
    console.log('🚀 Algorithm Visualizers Server Started!');
    console.log(`📍 Server running at: http://localhost:${PORT}`);
    console.log(`📁 Serving files from: ${path.join(__dirname, DIRECTORY)}`);
    console.log('🌐 Available pages:');
    console.log(`   • Combined Interface: http://localhost:${PORT}/combined.html`);
    console.log(`   • Sorting Visualizer: http://localhost:${PORT}/index.html`);
    console.log(`   • Pathfinding Visualizer: http://localhost:${PORT}/pathfinding.html`);
    console.log('🔧 Press Ctrl+C to stop the server');
    console.log('-'.repeat(60));
    
    // Try to open the combined interface in default browser (Windows compatible)
    try {
        const { exec } = require('child_process');
        const platform = process.platform;
        
        let command;
        if (platform === 'win32') {
            command = `start http://localhost:${PORT}/combined.html`;
        } else if (platform === 'darwin') {
            command = `open http://localhost:${PORT}/combined.html`;
        } else {
            command = `xdg-open http://localhost:${PORT}/combined.html`;
        }
        
        exec(command, (error) => {
            if (error) {
                console.log('⚠️  Could not open browser automatically');
                console.log(`   Please manually open: http://localhost:${PORT}/combined.html`);
            } else {
                console.log('✅ Opened combined interface in your default browser');
            }
        });
    } catch (error) {
        console.log('⚠️  Could not open browser automatically');
        console.log(`   Please manually open: http://localhost:${PORT}/combined.html`);
    }
    
    console.log('-'.repeat(60));
});

// Handle server shutdown
process.on('SIGINT', () => {
    console.log('\n🛑 Server stopped by user');
    server.close(() => {
        console.log('✅ Server closed gracefully');
        process.exit(0);
    });
});

// Handle uncaught exceptions
process.on('uncaughtException', (err) => {
    console.error('❌ Uncaught Exception:', err);
    server.close(() => {
        process.exit(1);
    });
});

// Handle unhandled promise rejections
process.on('unhandledRejection', (reason, promise) => {
    console.error('❌ Unhandled Rejection at:', promise, 'reason:', reason);
    server.close(() => {
        process.exit(1);
    });
});
