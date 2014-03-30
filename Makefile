#==============================================================================
# Compilation and installation options

# Probably the easiest way to configure most installation variables is to change them here. These
# are the directories where Airball will be installed. Of course you can also change these values on
# make call. Example:
# $ make run PROJECT_NAME=my_airball_woohoo PREFIX=/usr/
#
# Note however that this way you'll have to specify them every time.

# Specifies executable name
PROJECT_NAME=airball

# Prefix directory which is the first part of absolute installation path. By default Airball will be
# installed in user home directory (${HOME}/.local/)
PREFIX = ${HOME}/.local

# This is where all Airball files actually go (absolute path: $PREFIX/$DATADIR). Usually you don't
# want to change it.
DATADIR = share

# This is where Airball start script goes (absolute path: $PREFIX/$BIN). Usually this directory
# should be visible in your $PATH to simplify running Airball. Usually you don't want to change it.
BINDIR = bin

# If you'd like to use different flag set (CMake or g++ ones) it's probably the easiest to add them
# here.
ADDITIONAL_CXX_FLAGS =
CMAKE_FLAGS = -DCMAKE_BUILD_TYPE=Debug

#==============================================================================
# CMake specific settings and invocations
# WARNING: DO NOT change the following lines if you don't know what you're doing!

CMAKE_BUILD_DIR = ./build
CMAKE_BIN_DIR = ./bin  # CMake creates this directory automatically
CMAKE = $(CD) $(CMAKE_BUILD_DIR) && cmake $(CMAKE_FLAGS) \
		-DAIRBALL_PROJECT_NAME="$(PROJECT_NAME)" \
		-DCMAKE_INSTALL_PREFIX="$(PREFIX)" \
		-DAIRBALL_INSTALL_DIR="$(DATADIR)/$(PROJECT_NAME)" \
		-DAIRBALL_BIN_DIR="$(BINDIR)" \
		-DADDITIONAL_CXX_FLAGS="$(ADDITIONAL_CXX_FLAGS)"

#==============================================================================
# Make specific flags and settings

MAKE_FLAGS = --no-print-directory
MAKE = $(CD) $(CMAKE_BUILD_DIR) && make $(MAKE_FLAGS)

#==============================================================================
# Basic commands

RM = rm -f
MKDIR = mkdir -p
CD = cd
GDB = gdb

#==============================================================================
# Build targets

.DEFAULT_GOAL = all

.PHONY: prepare
prepare:
	$(MKDIR) $(CMAKE_BUILD_DIR)
	$(CMAKE) ..

.PHONY: all
all: prepare
	$(MAKE)

.PHONY: install
install: prepare
	$(MAKE) install

# uninstall will fail if there's no install_manifest from previous installation.
.PHONY: uninstall
uninstall: $(CMAKE_BUILD_DIR)/install_manifest.txt
	$(MAKE) uninstall
	$(RM) -r $(PREFIX)/$(DATADIR)/$(PROJECT_NAME)
	$(RM) $(PREFIX)/$(BINDIR)/$(PROJECT_NAME)

.PHONY: run
run: install
	$(CD) $(PREFIX)/$(DATADIR)/$(PROJECT_NAME) && ./$(PROJECT_NAME)

run/gdb: install
	$(CD) $(PREFIX)/$(DATADIR)/$(PROJECT_NAME) && $(GDB) ./$(PROJECT_NAME)

# check is just an alias
.PHONY: check
check: ut

.PHONY: ut
ut: prepare
	$(MAKE) $(PROJECT_NAME)_ut_run

ut/gdb: prepare
	$(MAKE) $(PROJECT_NAME)_ut
	$(CD) $(CMAKE_BIN_DIR)/tests && $(GDB) $(PROJECT_NAME)_ut

.PHONY: clean
clean:
	$(MAKE) clean

.PHONY: distclean
distclean:
	$(RM) -r $(CMAKE_BUILD_DIR)
	$(RM) -r $(CMAKE_BIN_DIR)

