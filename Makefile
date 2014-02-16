PROJECT_NAME=airball

RM = rm -f
MKDIR = mkdir -p
CD = cd
MAKE = make --no-print-directory
CMAKE = cmake

CMAKE_BUILD_DIR=./build

.DEFAULT_GOAL = all

.PHONY: prepare
prepare:
	$(MKDIR) $(CMAKE_BUILD_DIR)
	$(CD) $(CMAKE_BUILD_DIR) && $(CMAKE) ..

.PHONY: all
all: prepare
	$(CD) $(CMAKE_BUILD_DIR) && $(MAKE)

# check is just alias
check: ut

ut: prepare
	$(CD) $(CMAKE_BUILD_DIR) && $(MAKE) $(PROJECT_NAME)_ut_run

.PHONY: clean
clean:
	$(CD) $(CMAKE_BUILD_DIR) && $(MAKE) clean

.PHONY: distclean
distclean:
	$(RM) -r $(CMAKE_BUILD_DIR)

