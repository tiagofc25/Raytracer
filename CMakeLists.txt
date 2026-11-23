cmake_minimum_required(VERSION 3.20)
project(Raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# LodePNG: PNG encoding. Pinned to a commit because the project has no release tags.
FetchContent_Declare(
  lodepng
  GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
  GIT_TAG 7b2893e35891c0c85bee5595caafaf3c2044b409
)
FetchContent_MakeAvailable(lodepng)

add_library(lodepng STATIC ${lodepng_SOURCE_DIR}/lodepng.cpp)
target_include_directories(lodepng PUBLIC ${lodepng_SOURCE_DIR})

# The ray tracer code, shared by the program and the tests.
add_library(raytracer_core
  src/math/vector.cpp
  src/geometry/ray.cpp
  src/geometry/sphere.cpp
  src/render/camera.cpp
  src/colour/colour.cpp
  src/image/image.cpp
  src/io/png_saver.cpp
  src/material/flat_shader.cpp
  src/material/lambert_shader.cpp
  src/light/light.cpp
)
target_include_directories(raytracer_core PUBLIC src)
target_link_libraries(raytracer_core PRIVATE lodepng)

add_executable(raytracer src/main.cpp)
target_link_libraries(raytracer PRIVATE raytracer_core)

# Tests: Catch2 + CTest.
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.7.1
)
FetchContent_MakeAvailable(Catch2)

enable_testing()

add_executable(tests
  tests/math/vector_test.cpp
  tests/geometry/sphere_test.cpp
  tests/render/camera_test.cpp
  tests/image/image_test.cpp
  tests/material/lambert_shader_test.cpp
)
target_link_libraries(tests PRIVATE raytracer_core Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(tests)
