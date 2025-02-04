# Compiler
CC = g++

# Compiler flags
CFLAGS = -g -std=c++17 -I$(LIBS)

# Linker flags
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Include directory
LIBS = ./lib

# Executable name
EXEC = Simulator

# Find all .cpp files and generate .o file names
SRCS = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJS = $(patsubst src/%.cpp,build/%.o,$(SRCS))
# OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compile .cpp files to .o files
# %.o: %.cpp
#	$(CC) $(CFLAGS) -c $< -o $@

# Compile .cpp files to .o files in the build directory
build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
# 	rm -f $(OBJS) $(EXEC)
	rm -rf build $(EXEC)

.PHONY: all clean
