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

# Output binaries
TARGET = lltest
HMAP_TEST = hmaptest
COMBINED_TEST = run_tests

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRCS))

# Default rule
all: $(TEST_DIR)/$(TARGET) $(TEST_DIR)/$(HMAP_TEST) $(TEST_DIR)/$(COMBINED_TEST)

# Rule to create lltest binary
$(TEST_DIR)/$(TARGET): $(OBJS) $(TEST_SRC_DIR)/lltest.c
	@mkdir -p $(TEST_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Rule to create hmaptest binary
$(TEST_DIR)/$(HMAP_TEST): $(OBJS) $(TEST_SRC_DIR)/hmaptest.c
	@mkdir -p $(TEST_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Rule to create combined tests binary
$(TEST_DIR)/$(COMBINED_TEST): $(TEST_DIR)/$(TARGET) $(TEST_DIR)/$(HMAP_TEST) $(TEST_SRC_DIR)/run_tests.c
	@mkdir -p $(TEST_DIR)
	$(CC) $(CFLAGS) $(TEST_SRC_DIR)/run_tests.c -o $@ $(LDFLAGS)

# Rule to compile object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(BIN_DIR) $(TEST_DIR)

.PHONY: all clean