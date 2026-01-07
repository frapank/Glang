# Default definition
include config.mk

SRC_DIR 	:= src
INCLUDE_DIR := include
BUILD_DIR 	:= build

SRC_FILES 	:= $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ 		:= $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

NAME 		:= glang
OUTPUT 		:= $(BUILD_DIR)/$(NAME)

# Compile
.PHONY: all build clean

all: build

build: $(OUTPUT)

$(OUTPUT): $(OBJ)
	$(CC) $(FLAGS) $(OPT_FLAGS) -o $@ -I$(INCLUDE_DIR) $(LDLIBS) $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(OPT_FLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
