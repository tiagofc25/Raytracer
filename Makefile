# Shortcuts for the CMake commands, like "npm run ..." scripts.
BUILD_DIR := build

.PHONY: build start test clean

build:
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

start: build
	./$(BUILD_DIR)/raytracer

test: build
	ctest --test-dir $(BUILD_DIR) --output-on-failure

clean:
	rm -rf $(BUILD_DIR)
