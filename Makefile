CC 			?= gcc
DEF_FLAGS 	:= -Wall -Wextra -Wpedantic -std=gnu17
DEB_FLAGS	:= -O0 -g -DDEBUG
OPT_FLAGS	:= -O2 -march=native 
LDLIBS 		:= $(shell llvm-config --libs core analysis executionengine native \
          		x86codegen x86desc x86info x86asmparser x86disassembler \
          		mcjit orcjit passes support target) $(shell llvm-config --system-libs) -ldl -lpthread

SRC_DIR		:= src
INCLUDE_DIR	:= include
BUILD_DIR	:= build
SRC_FILES	:= $(shell find $(SRC_DIR) -type f -name "*.c")

NAME 		:= glang
OUTPUT		:= $(BUILD_DIR)/$(NAME)

all: build

build: clean
	mkdir -p $(BUILD_DIR)
	$(CC) $(DEF_FLAGS) $(OPT_FLAGS) -o $(OUTPUT) -I$(INCLUDE_DIR) $(LDLIBS) $(SRC_FILES)

debug: clean
	mkdir -p $(BUILD_DIR)
	$(CC) $(DEF_FLAGS) $(DEB_FLAGS) -o $(OUTPUT) -I$(INCLUDE_DIR) $(LDLIBS) $(SRC_FILES)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all build clean
