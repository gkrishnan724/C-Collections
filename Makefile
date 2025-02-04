# Compiler and flags
CC = gcc
CFLAGS = -isystem inc -Wall -Wextra -g
LDFLAGS = 

# Directories
SRC_DIR = lib
INC_DIR = inc
BIN_DIR = bin
TEST_DIR = bin/tests
TEST_SRC_DIR = tests

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
TEST_SRCS = $(wildcard $(TEST_SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRCS))
TEST_BINS = $(patsubst $(TEST_SRC_DIR)/%.c, $(TEST_DIR)/%, $(TEST_SRCS))

# Default rule
all: $(TEST_BINS)

# Rule to create binaries for all .c files in the tests directory
$(TEST_DIR)/%: $(TEST_SRC_DIR)/%.c $(OBJS)
	@mkdir -p $(TEST_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Rule to compile object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(BIN_DIR) $(TEST_DIR)

.PHONY: all clean