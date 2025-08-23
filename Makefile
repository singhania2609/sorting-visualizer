# Sorting Visualizer and Pathfinding Makefile
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g
TARGET = sorting_visualizer
PATHFINDING_TARGET = pathfinding_demo
SRCDIR = src
OBJDIR = obj
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Filter out pathfinding_main.cpp for sorting target
SORTING_SOURCES = $(filter-out $(SRCDIR)/pathfinding_main.cpp, $(SOURCES))
SORTING_OBJECTS = $(SORTING_SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Pathfinding sources (exclude main.cpp)
PATHFINDING_SOURCES = $(filter-out $(SRCDIR)/main.cpp, $(SOURCES))
PATHFINDING_OBJECTS = $(PATHFINDING_SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Default target
all: $(TARGET) $(PATHFINDING_TARGET)

# Create object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link the sorting visualizer executable
$(TARGET): $(SORTING_OBJECTS)
	$(CXX) $(SORTING_OBJECTS) -o $(TARGET)

# Link the pathfinding demo executable
$(PATHFINDING_TARGET): $(PATHFINDING_OBJECTS)
	$(CXX) $(PATHFINDING_OBJECTS) -o $(PATHFINDING_TARGET)

# Run the sorting program
run: $(TARGET)
	./$(TARGET)

# Run the pathfinding program
run-pathfinding: $(PATHFINDING_TARGET)
	./$(PATHFINDING_TARGET)

# Clean build files
clean:
	rm -rf $(OBJDIR) $(TARGET) $(PATHFINDING_TARGET)

# Clean and rebuild
rebuild: clean all

# Install dependencies (for Ubuntu/Debian)
install-deps:
	sudo apt-get update
	sudo apt-get install -y build-essential

# Install dependencies (for macOS)
install-deps-mac:
	brew install gcc

# Install dependencies (for Windows with MinGW)
install-deps-windows:
	# Assuming MinGW is already installed
	# If not, download from: https://www.mingw-w64.org/

# Test the sorting program
test: $(TARGET)
	./$(TARGET) > test_output.txt
	@echo "Test completed. Check test_output.txt for results."

# Test the pathfinding program
test-pathfinding: $(PATHFINDING_TARGET)
	./$(PATHFINDING_TARGET) > pathfinding_test_output.txt
	@echo "Pathfinding test completed. Check pathfinding_test_output.txt for results."

# Benchmark mode
benchmark: $(TARGET)
	./$(TARGET)

# Debug build
debug: CXXFLAGS += -DDEBUG -g3
debug: $(TARGET)

# Release build
release: CXXFLAGS += -DNDEBUG -O3
release: clean $(TARGET)

# Generate documentation
docs:
	@echo "Generating documentation..."
	@echo "# Sorting Visualizer Documentation" > docs/README.md
	@echo "" >> docs/README.md
	@echo "## Features" >> docs/README.md
	@echo "- Basic sorting algorithms (Bubble, Quick, Merge)" >> docs/README.md
	@echo "- Performance metrics and analysis" >> docs/README.md
	@echo "- Step-by-step visualization" >> docs/README.md
	@echo "- Data export and import" >> docs/README.md
	@echo "Documentation generated in docs/README.md"

# Create project structure
setup:
	mkdir -p docs
	mkdir -p examples
	mkdir -p frontend
	@echo "Project structure created"

# Help target
help:
	@echo "Available targets:"
	@echo "  all              - Build both sorting visualizer and pathfinding demo"
	@echo "  sorting          - Build only the sorting visualizer"
	@echo "  pathfinding      - Build only the pathfinding demo"
	@echo "  run              - Build and run the sorting program"
	@echo "  run-pathfinding  - Build and run the pathfinding program"
	@echo "  clean            - Remove build files"
	@echo "  rebuild          - Clean and rebuild"
	@echo "  test             - Run sorting tests"
	@echo "  test-pathfinding - Run pathfinding tests"
	@echo "  benchmark        - Run sorting program with benchmarking"
	@echo "  debug            - Build with debug symbols"
	@echo "  release          - Build optimized release version"
	@echo "  docs             - Generate documentation"
	@echo "  setup            - Create project structure"
	@echo "  help             - Show this help message"
	@echo ""
	@echo "Sorting Features:"
	@echo "  - Basic sorting algorithms (Bubble, Quick, Merge)"
	@echo "  - Performance metrics and analysis"
	@echo "  - Step-by-step visualization"
	@echo "  - Data export and import"
	@echo ""
	@echo "Pathfinding Features:"
	@echo "  - Multiple pathfinding algorithms (Dijkstra, Bellman-Ford, Floyd-Warshall, A*)"
	@echo "  - City network with real coordinates"
	@echo "  - Distance and time optimization"
	@echo "  - Route visualization and comparison"
	@echo ""
	@echo "Dependency installation:"
	@echo "  install-deps       - Install dependencies (Ubuntu/Debian)"
	@echo "  install-deps-mac   - Install dependencies (macOS)"
	@echo "  install-deps-windows - Install dependencies (Windows)"

# Phony targets
.PHONY: all run run-pathfinding clean rebuild test test-pathfinding benchmark debug release docs setup help install-deps install-deps-mac install-deps-windows sorting pathfinding
