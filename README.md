# Raytracer

A ray tracer written in C++ for an animation studio. It runs on the CPU and is meant to be reliable, easy to maintain and open to contributions.

## Getting started

### 1. Open the dev container

Everyone builds in the same Linux container (compiler, CMake, Git), so the project behaves the same on Windows, macOS and Linux. You need [Docker](https://www.docker.com/) and an editor that supports dev containers.

- **VS Code**: install the *Dev Containers* extension, open this folder, then run **Dev Containers: Reopen in Container**.
- **Zed**: open this folder; Zed offers to open it in the dev container (`.devcontainer/devcontainer.json`).

All the commands below are run in the container's terminal.

### 2. Build and run

```sh
make run
```

This compiles the project and runs it. It prints `Hello, Raytracer!` and renders the m1 scene into `image.png`: a red sphere lit by the sun, on a green ground plane, with its shadow. To choose the file name: `./build/raytracer my_image.png`.

### 3. Run the tests

```sh
make test
```

### All the shortcuts

| Command      | Like…            | What it does                          |
|--------------|------------------|---------------------------------------|
| `make build` | `npm run build`  | Configure and compile into `build/`   |
| `make run`   | `npm run start`  | Build, then render `image.png`       |
| `make test`  | `npm test`       | Build, then run every test with CTest |
| `make clean` | `npm run clean`  | Delete `build/`                       |

The `Makefile` only wraps these CMake commands, which you can also type yourself:

```sh
cmake -S . -B build                          # configure (download Catch2 and LodePNG the first time)
cmake --build build                          # compile
./build/raytracer                            # run
ctest --test-dir build --output-on-failure   # test
```

## Tools

- **CMake** describes how to build the project (which files, which libraries) and generates the real build files for each platform. It also downloads our dependencies at a pinned version.
- **CTest** comes with CMake: it finds the tests and runs them, and reports which ones fail.
- **Catch2** is the C++ library we write the tests with (`TEST_CASE`, `REQUIRE`). `catch_discover_tests` tells CTest about each `TEST_CASE`.
- **LodePNG** encodes our images as PNG files.

## Testing with TDD

We work test first:

1. **Red**: write a small test in `tests/<concept>/<name>_test.cpp` for the behaviour you want. Run `make test` and see it fail.
2. **Green**: write the simplest code in `src/<concept>/` that makes it pass.
3. **Refactor**: clean the code while the tests stay green.

A test looks like this:

```cpp
#include <catch2/catch_test_macros.hpp>
#include "math/vector.h"

TEST_CASE("Adding two vectors adds each component") {
    Vector v3 = Vector(1, 2, 3) + Vector(4, 5, 6);

    REQUIRE(v3.x() == 5);
}
```

A new test file must be added to the `tests` target in `CMakeLists.txt`. For decimal numbers, compare with `Catch::Approx` (from `<catch2/catch_approx.hpp>`).

## Project layout

```
src/
  math/       Vector
  geometry/   Ray, HitInfo, Shape (abstract), Sphere, Plane
  scene/      Scene (objects + light + sky, closest hit, shadows)
  colour/     Colour
  light/      Light (point light)
  material/   Material (strategy), FlatShader, LambertShader
  render/     Camera (pinhole: rayThroughPixel, trace, render)
  image/      Image
  io/         ImageSaver (strategy), PngSaver
  main.cpp
tests/        same folders as src/
```

## Documentation

- [Discovery report](docs/discovery/discovery-report.md): the problem, the client interview, existing solutions, and short explanations of ray tracing and C++.
- [Domain model](docs/domain/domain-model.md): the concepts of the ray tracer and how they relate.
- [Architecture decisions](docs/adr/): why we chose our tools and our design (all Proposed for now).
- [AGENTS.md](AGENTS.md): rules for AI coding agents (and a good summary for humans).

## Milestones

- m0: discovery report
- m1 (done): project setup and a first ray tracer (a sphere lit by the sun on a ground plane)
