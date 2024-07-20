# Compiler
CC = g++

# Compiler flags
CFLAGS = -g -std=c++11

# Executable name
EXEC = Graph

# Find all .cpp files and generate .o file names
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .cpp files to .o files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean