# Build type
BUILD ?= Release

# Compiler and its flags
CC ?= gcc
ifeq ($(BUILD),Debug)
	CFLAGS := -Werror -g3 -O0 -std=c99\
			 -Wall -Wextra -Wpedantic -Wshadow -Wcast-align -Wformat=2 \
			 -Wconversion -Wsign-conversion -Wmissing-declarations\
			 -Wmissing-prototypes -Wlogical-op -Wold-style-definition\
			 -Wstrict-prototypes -Wundef -Wwrite-strings -Wswitch-enum\
			 -Wfloat-equal -Wpointer-arith -Winit-self -Wredundant-decls\
			 -Wnested-externs -Wlogical-op -Wduplicated-cond\
			 -Wduplicated-branches -Wstrict-aliasing=2 -Winline\
			 -Wstack-protector -Wstack-protector -Wstrict-overflow=5\
			 -Wcast-qual -Wmissing-noreturn -Wjump-misses-init
else
	CFLAGS := -std=c99 -static -O2 -flto -funroll-loops
endif

# Set the app name and version
TARGET  := httpc
VERSION := 1.3.0

# Set source and object directories
SRCDIR := src
OBJDIR := obj
BINDIR := bin
DEBDIR := deb
AURDIR := AUR

# Prefixes
PREFIX    ?= /usr/local
BINPREFIX ?= $(PREFIX)/bin

# Get all source files and object file names
SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Set targets that do not create new files
.PHONY: all clean install uninstall deb aur

# Default target
all: $(BINDIR)/$(TARGET)

# Clean all compiled C binaries
clean:
	rm -rf $(OBJDIR) $(BINDIR) $(DEBDIR)

# Install the binary to the system
install: $(BINDIR)/$(TARGET)
	@mkdir -p $(BINPREFIX)
	cp $(BINDIR)/$(TARGET) $(BINPREFIX)
	chmod 755 $(BINPREFIX)/$(TARGET)

# Uninstall the binary from the system
uninstall:
	rm $(BINPREFIX)/$(TARGET)

# Build deb package
deb: PACKAGEDIR=$(DEBDIR)/$(TARGET)_$(DEST)_$(ARCH)
deb:
ifeq ($(ARCH),)
	$(error ARCH variable is not defined)
	exit -1
endif
ifeq ($(DEST),)
	$(error DEST variable is not defined)
	exit -1
endif
	# Create DEBIAN directory
	mkdir -p $(PACKAGEDIR)/DEBIAN
	printf "\
	Package: $(TARGET)\n\
	Version: $(VERSION)\n\
	Architecture: $(ARCH)\n\
	Maintainer: Andrew Shershunov (Evilur) <the.evilur@gmail.com>\n\
	Description: Simple zero-conf http server on C\n\
	 A Simple zero-conf http 1.1 server to use instead of the python http.server.\n\
	 Distributed as a binary or a source code for running on any platform \n\
	 where other servers cannot be run\n\
	Section: net\n\
	Priority: optional\n\
	Homepage: https://github.com/Evilur/httpc\n" > $(PACKAGEDIR)/DEBIAN/control

	# Install binary to the package root
	$(MAKE) install PREFIX=$(PACKAGEDIR)$(PREFIX)

	# Build package
	dpkg-deb --root-owner-group --build $(PACKAGEDIR)

aur:
ifeq ($(SHA512SUM),)
	$(error SHA512SUM variable is not defined)
	exit -1
endif
ifeq ($(SHA256SUM),)
	$(error SHA256SUM variable is not defined)
	exit -1
endif
	# Create an AUR PKGBUILD
	mkdir -p $(AURDIR)
	printf "\
	pkgname=$(TARGET)\n\
	pkgver=$(VERSION)\n\
	pkgrel=1\n\
	pkgdesc='A Simple zero-conf http 1.1 server to use instead of the python http.server'\n\
	arch=('x86_64')\n\
	url='https://github.com/Evilur/httpc'\n\
	license=('MIT')\n\
	source=(\"https://github.com/Evilur/httpc/archive/refs/tags/v\$$pkgver.tar.gz\")\n\
	sha512sums=('$(SHA512SUM)')\n\
	sha256sums=('$(SHA256SUM)')\n\
	makedepends=('make' 'gcc')\n\
	\n\
	build() {\n\
		cd \"\$$srcdir/\$$pkgname-\$$pkgver\"\n\
		make\n\
	}\n\
	\n\
	package() {\n\
		cd \"\$$srcdir/\$$pkgname-\$$pkgver\"\n\
		install -Dm755 $(BINDIR)/$(TARGET) \"\$$pkgdir/usr/bin/httpc\"\n\
	}" > $(AURDIR)/PKGBUILD

	# Make .SRCINFO
	cd $(AURDIR) && makepkg --printsrcinfo > .SRCINFO

# Link the target
$(BINDIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Compile all source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
