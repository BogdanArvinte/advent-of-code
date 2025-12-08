# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g -Iinclude -std=c23

# Source files and output
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=obj/%.o)
TARGET = aoc

# Default target
all: $(TARGET)

# Linking the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compiling source files into object files
obj/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf obj $(TARGET)

# Phony targets
.PHONY: all clean
