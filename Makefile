# Build type
BUILD ?= Release

# Compiler and its flags
CC ?= gcc
ifeq ($(BUILD),Debug)
	CFLAGS = -Werror\
	-Wall -Wextra -Wpedantic -Wshadow -Wcast-align -Wformat=2 -Wconversion\
	-Wsign-conversion -Wmissing-declarations -Wmissing-prototypes -Wlogical-op\
	-Wold-style-definition -Wstrict-prototypes -Wundef -Wwrite-strings\
	-Wswitch-enum -Wfloat-equal -Wpointer-arith -Winit-self -Wredundant-decls\
	-Wnested-externs -Wlogical-op -Wduplicated-cond -Wduplicated-branches\
	-Wstrict-aliasing=2 -Winline -Wstack-protector -Wstack-protector\
	-Wstrict-overflow=5 -Wcast-qual -Wmissing-noreturn -Wjump-misses-init -g
endif
CFLAGS += -std=c99 -O2

# Set the app name
TARGET = httpc

# Set source and object directories
SRCDIR = src
OBJDIR = obj

# Get all source files and object file names
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Set targets that do not create new files
.PHONY: clean

# Default target
all: $(TARGET)

# Link the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Compile all source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean all compiled C binaries
clean:
	rm --force $(OBJDIR)/*.o $(TARGET)
