CC ?= gcc

BUILDDIR := build

# Libs
INCLUDES := -Iinclude $(shell llvm-config --includedir)
LIBS := $(shell llvm-config --libs core analysis executionengine native \
        x86codegen x86desc x86info x86asmparser x86disassembler \
        mcjit orcjit passes support target)
LIBS := $(LIBS) $(shell llvm-config --system-libs) -ldl -lpthread

# Flags
CFLAGS := -Wall -std=c11 -D_POSIX_C_SOURCE=200809L $(INCLUDES)
ifeq ($(DEBUG),1)
    CFLAGS += -g -O0 -DDEBUG
else
    CFLAGS += -O3
endif

ifeq ($(NATIVE),1)
    CFLAGS += -march=native
endif

LDFLAGS := $(LIBS)

# Sources
SRC := $(shell find src -name '*.c')
OBJ := $(patsubst src/%.c,$(BUILDDIR)/%.o,$(SRC))
TARGET := compiler

# Rules
.PHONY: all clean debug

all: clean $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# Compila i .c in build/%.o
$(BUILDDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

debug: clean
	$(MAKE) DEBUG=1

clean:
	rm -rf $(BUILDDIR) $(TARGET)

