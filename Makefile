# Makefile for DSA Sorting and Pathfinding Visualizer
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g
LDFLAGS = 

# Directories
SRC_DIR = src
BUILD_DIR = build
EXAMPLES_DIR = examples

# Source files
SORTING_SOURCES = $(SRC_DIR)/main.cpp
PATHFINDING_SOURCES = $(SRC_DIR)/pathfinding.cpp $(SRC_DIR)/pathfinding_main.cpp

# Executables
SORTING_EXEC = sorting_visualizer
PATHFINDING_EXEC = pathfinding_visualizer

# Default target
all: $(SORTING_EXEC) $(PATHFINDING_EXEC)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile sorting visualizer
$(SORTING_EXEC): $(SORTING_SOURCES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$@ $^ $(LDFLAGS)
	@echo "Sorting visualizer compiled successfully!"

# Compile pathfinding visualizer
$(PATHFINDING_EXEC): $(PATHFINDING_SOURCES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$@ $^ $(LDFLAGS)
	@echo "Pathfinding visualizer compiled successfully!"

# Run sorting visualizer
run-sorting: $(SORTING_EXEC)
	./$(BUILD_DIR)/$(SORTING_EXEC)

# Run pathfinding visualizer
run-pathfinding: $(PATHFINDING_EXEC)
	./$(BUILD_DIR)/$(PATHFINDING_EXEC)

# Clean build files
clean:
	rm -rf $(BUILD_DIR)
	rm -f *.txt
	@echo "Build files cleaned!"

# Clean and rebuild
rebuild: clean all

# Install dependencies (for Ubuntu/Debian)
install-deps:
	sudo apt-get update
	sudo apt-get install -y build-essential g++ make

# Install dependencies (for CentOS/RHEL/Fedora)
install-deps-rpm:
	sudo yum groupinstall -y "Development Tools"
	# or for newer versions: sudo dnf groupinstall -y "Development Tools"

# Install dependencies (for macOS)
install-deps-mac:
	xcode-select --install

# Show help
help:
	@echo "Available targets:"
	@echo "  all              - Build both visualizers (default)"
	@echo "  sorting_visualizer - Build only sorting visualizer"
	@echo "  pathfinding_visualizer - Build only pathfinding visualizer"
	@echo "  run-sorting      - Build and run sorting visualizer"
	@echo "  run-pathfinding  - Build and run pathfinding visualizer"
	@echo "  clean            - Remove build files"
	@echo "  rebuild          - Clean and rebuild everything"
	@echo "  install-deps     - Install build dependencies (Ubuntu/Debian)"
	@echo "  install-deps-rpm - Install build dependencies (CentOS/RHEL/Fedora)"
	@echo "  install-deps-mac - Install build dependencies (macOS)"
	@echo "  help             - Show this help message"

# Phony targets
.PHONY: all clean rebuild install-deps install-deps-rpm install-deps-mac help run-sorting run-pathfinding

# Create examples directory and sample files
examples: $(EXAMPLES_DIR)
	@echo "Creating example files..."
	@echo "Sample test data for sorting algorithms" > $(EXAMPLES_DIR)/test_data.txt
	@echo "64 34 25 12 22 11 90" >> $(EXAMPLES_DIR)/test_data.txt
	@echo "Benchmark results will be saved here" > $(EXAMPLES_DIR)/benchmark_results.txt
	@echo "Examples directory created with sample files!"

$(EXAMPLES_DIR):
	mkdir -p $(EXAMPLES_DIR)

# Debug build
debug: CXXFLAGS += -DDEBUG -g3
debug: all

# Release build
release: CXXFLAGS += -O3 -DNDEBUG
release: all

# Profile build
profile: CXXFLAGS += -pg
profile: LDFLAGS += -pg
profile: all

# Static linking
static: LDFLAGS += -static
static: all
