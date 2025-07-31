# Compiler and its flags
CC 	   ?= gcc
CFLAGS ?= -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wuninitialized \
-Wconversion -Wlogical-op -Wnull-dereference -Wduplicated-cond \
-Wredundant-decls -Wstrict-prototypes -Wmissing-declarations \
-Wunreachable-code -Wmissing-prototypes -O2
CFLAGS += -std=c99

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