# Detect OS (Windows or Unix-based)
ifeq ($(OS),Windows_NT)
    RM = del /Q $(TARGET).exe
    SHELL := cmd.exe
else
    RM = rm -f $(TARGET)
endif

# Project details
CC = gcc
TARGET = company_management
SRC = company_management.c

# Run the program
run: $(TARGET)
	./$(TARGET)

# Compile the C program
$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)
	@echo "Compilation completed."

# Clean the executable
clean:
	$(RM)
	@echo "Build cleaned."
