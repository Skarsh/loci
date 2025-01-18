# Compiler settings
CC = cc
CFLAGS = -Wall -Wextra -g -I./src

# Directory settings
BUILD_DIR = build
SRC_DIR = src
OBJ_DIR = $(BUILD_DIR)/obj
BASE_DIR = $(SRC_DIR)/base
TEST_DIR = tests

# Target executable names
TARGET = $(BUILD_DIR)/oci
TEST_TARGET = $(BUILD_DIR)/test_runner

# Source files
SRCS = $(SRC_DIR)/main.c \
       $(BASE_DIR)/oci_base_memory.c \
       $(BASE_DIR)/oci_base_string.c \
       $(BASE_DIR)/oci_base_test.c

TEST_SRCS = $(TEST_DIR)/test_main.c \
            $(filter-out $(TEST_DIR)/test_main.c, $(wildcard $(TEST_DIR)/*.c))
TEST_BASE_SRCS = $(BASE_DIR)/oci_base_memory.c \
                 $(BASE_DIR)/oci_base_string.c \
                 $(BASE_DIR)/oci_base_test.c

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/tests/%.o,$(TEST_SRCS)) \
            $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_BASE_SRCS))

# Make sure the object directories exist
OBJDIRS = $(BUILD_DIR) $(OBJ_DIR) $(OBJ_DIR)/base $(OBJ_DIR)/tests

# Default target
all: clean $(OBJDIRS) $(TARGET) $(TEST_TARGET)

# Create object directories
$(OBJDIRS):
	mkdir -p $@

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Link test object files to create test executable
$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(TEST_OBJS) -o $(TEST_TARGET)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/tests/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target for removing compiled files
clean:
	rm -rf $(BUILD_DIR)
	rm -f compile_commands.json

# Test target
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Prevent make from using implicit rules
.SUFFIXES:
MAKEFLAGS += --no-builtin-rules

# Phony targets
.PHONY: all clean test
