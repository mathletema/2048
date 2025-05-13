# Set project name
TARGET = 2048

# Compiler
CC = gcc

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = build

# Homebrew paths
HOMEBREW_INC = /opt/homebrew/include
HOMEBREW_LIB = /opt/homebrew/lib

# Compiler and linker flags
CFLAGS = -Wall -Wextra -I$(INC_DIR) -I$(SRC_DIR) -I$(HOMEBREW_INC)
LDFLAGS = -L$(HOMEBREW_LIB) -lSDL2

# Source and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LDFLAGS) -o $@

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure build directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
