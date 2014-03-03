PROJECT_NAME=airball

#==============================================================================
# Basic commands

RM = rm -f
MKDIR = mkdir -p
CD = cd
GDB = gdb

#==============================================================================
# CMake specific flags and settings

ADDITIONAL_CXX_FLAGS =
CMAKE_FLAGS = -DCMAKE_BUILD_TYPE=Debug
CMAKE_BUILD_DIR = ./build
CMAKE_BIN_DIR = ./bin  # CMake creates this directory automatically
CMAKE = $(CD) $(CMAKE_BUILD_DIR) && cmake $(CMAKE_FLAGS) -DADDITIONAL_CXX_FLAGS="$(ADDITIONAL_CXX_FLAGS)"

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

.PHONY: run
run: all
	$(CD) $(CMAKE_BIN_DIR) && ./$(PROJECT_NAME)

run/gdb: all
	$(CD) $(CMAKE_BIN_DIR) && $(GDB) $(PROJECT_NAME)


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

