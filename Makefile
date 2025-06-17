# Compiler & Flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Source and Target
SRC = $(wildcard src/*.cpp)
EXEC = build/minios.exe

# Default target
all: $(EXEC)

# Link object files into executable
$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Run the executable
run: all
	.\$(EXEC)

# Clean build files
clean:
	@if exist $(EXEC) del /Q $(EXEC)
