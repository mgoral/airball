PROJECT_NAME=airball

#==============================================================================
# Basic commands

RM = rm -f
MKDIR = mkdir -p
CD = cd
GDB = gdb

#==============================================================================
# CMake specific flags and settings

CMAKE_FLAGS = -DCMAKE_BUILD_TYPE=Debug
CMAKE_BUILD_DIR = ./build
CMAKE = $(CD) $(CMAKE_BUILD_DIR) && cmake $(CMAKE_FLAGS)

#==============================================================================
# Make specific flags and settings
MAKE_FLAGS = --no-print-directory
MAKE = $(CD) $(CMAKE_BUILD_DIR) && make $(MAKE_FLAGS)

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

# check is just alias
check: ut

ut: prepare
	$(MAKE) $(PROJECT_NAME)_ut_run

ut/gdb: prepare
	$(MAKE) $(PROJECT_NAME)_ut
	$(CD) $(CMAKE_BUILD_DIR)/tests && $(GDB) airball_ut


.PHONY: clean
clean:
	$(MAKE) clean

.PHONY: distclean
distclean:
	$(RM) -r $(CMAKE_BUILD_DIR)

