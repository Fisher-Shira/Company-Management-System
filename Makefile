# Detect OS (Windows or Unix-based)
ifeq ($(OS),Windows_NT)
    MKDIR = if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
    RM = rmdir /s /q $(BUILD_DIR)
    SHELL := cmd.exe
else
    MKDIR = mkdir -p $(BUILD_DIR)
    RM = rm -rf $(BUILD_DIR)
endif

# Project details
CC = gcc
SRC_DIR = src
BUILD_DIR = build
TARGET = company_management

# Run the program
run: compile
	./$(BUILD_DIR)/$(TARGET)

# Compile the C program
compile:
	$(MKDIR)
	$(CC) -o $(BUILD_DIR)/$(TARGET) $(SRC_DIR)/$(TARGET).c
	@echo "Compilation completed."

# Clean the executable
clean:
	$(RM)
	@echo "Build cleaned."
