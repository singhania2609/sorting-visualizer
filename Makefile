# Sorting Visualizer Makefile
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g
TARGET = sorting_visualizer
SRCDIR = src
OBJDIR = obj
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Default target
all: $(TARGET)

# Create object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean build files
clean:
	rm -rf $(OBJDIR) $(TARGET)

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

# Test the program
test: $(TARGET)
	./$(TARGET) > test_output.txt
	@echo "Test completed. Check test_output.txt for results."

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
	@echo "  all              - Build the sorting visualizer"
	@echo "  run              - Build and run the program"
	@echo "  clean            - Remove build files"
	@echo "  rebuild          - Clean and rebuild"
	@echo "  test             - Run tests"
	@echo "  benchmark        - Run program with benchmarking"
	@echo "  debug            - Build with debug symbols"
	@echo "  release          - Build optimized release version"
	@echo "  docs             - Generate documentation"
	@echo "  setup            - Create project structure"
	@echo "  help             - Show this help message"
	@echo ""
	@echo "Features:"
	@echo "  - Basic sorting algorithms (Bubble, Quick, Merge)"
	@echo "  - Performance metrics and analysis"
	@echo "  - Step-by-step visualization"
	@echo "  - Data export and import"
	@echo ""
	@echo "Dependency installation:"
	@echo "  install-deps       - Install dependencies (Ubuntu/Debian)"
	@echo "  install-deps-mac   - Install dependencies (macOS)"
	@echo "  install-deps-windows - Install dependencies (Windows)"

# Phony targets
.PHONY: all run clean rebuild test benchmark debug release docs setup help install-deps install-deps-mac install-deps-windows
