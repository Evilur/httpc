# Build type
BUILD ?= Release

# Compiler and its flags
CC ?= gcc
ifeq ($(BUILD),Debug)
	CFLAGS = -Werror -g3 -O0 -std=c99\
	-Wall -Wextra -Wpedantic -Wshadow -Wcast-align -Wformat=2 -Wconversion\
	-Wsign-conversion -Wmissing-declarations -Wmissing-prototypes -Wlogical-op\
	-Wold-style-definition -Wstrict-prototypes -Wundef -Wwrite-strings\
	-Wswitch-enum -Wfloat-equal -Wpointer-arith -Winit-self -Wredundant-decls\
	-Wnested-externs -Wlogical-op -Wduplicated-cond -Wduplicated-branches\
	-Wstrict-aliasing=2 -Winline -Wstack-protector -Wstack-protector\
	-Wstrict-overflow=5 -Wcast-qual -Wmissing-noreturn -Wjump-misses-init
else
	CFLAGS = -std=c99 -O2 -march=native -mtune=native -flto -funroll-loops
endif

# Set the app name
TARGET ?= httpc

# Set source and object directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Get all source files and object file names
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Set targets that do not create new files
.PHONY: clean

# Default target
all: $(BINDIR)/$(TARGET)

# Link the target
$(BINDIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Compile all source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean all compiled C binaries
clean:
	rm -rf $(OBJDIR) $(BINDIR)
