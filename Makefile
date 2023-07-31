# Makefile to build a CMake project

# Name of the CMake directories
BUILD_DIR := build

BIN_DIR := bin

LIB_DIR := lib

# Name of the CMake executable (cmake or cmake3 depending on the system)
CMAKE := $(shell which cmake3 cmake | head -n 1)

# Targets
.PHONY: all clean fclean re

all: $(BUILD_DIR)/Makefile
	@$(MAKE) -C $(BUILD_DIR)

# Generate CMake build files
$(BUILD_DIR)/Makefile:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && $(CMAKE) ..

clean:
	@$(MAKE) -C $(BUILD_DIR) clean
	@rm -rf $(BUILD_DIR)

fclean: clean
	@rm -rf $(BUILD_DIR) $(BIN_DIR) $(LIB_DIR)

re: fclean all