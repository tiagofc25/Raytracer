# Shortcuts for the CMake commands, like "npm run ..." scripts.
BUILD_DIR := build

.PHONY: build run start test clean

build:
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

run: build
	./$(BUILD_DIR)/raytracer

# Same as run, for people used to "npm run start".
start: run

test: build
	ctest --test-dir $(BUILD_DIR) --output-on-failure

clean:
	rm -rf $(BUILD_DIR)
