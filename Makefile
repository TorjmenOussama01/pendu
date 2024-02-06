CC = gcc
CFLAGS =  -Werror -w -Iinclude
LDFLAGS =

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# List the source files
MAIN_SRC = main.c
HELPER_SRC = $(wildcard $(SRC_DIR)/helpers/*.c)
UTILITIES_SRC = $(wildcard $(SRC_DIR)/utilities/*.c)

# Generate object file names
MAIN_OBJ = $(BUILD_DIR)/main.o
HELPER_OBJ = $(patsubst $(SRC_DIR)/helpers/%.c, $(BUILD_DIR)/%.o, $(HELPER_SRC))
UTILITIES_OBJ = $(patsubst $(SRC_DIR)/utilities/%.c, $(BUILD_DIR)/%.o, $(UTILITIES_SRC))

# Set the executable name
EXECUTABLE = exec

all: $(EXECUTABLE)

$(EXECUTABLE): $(MAIN_SRC) $(HELPER_SRC) $(UTILITIES_SRC)
	$(CC) $(CFLAGS) $^ -o $@