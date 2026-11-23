# 2. Build with CMake, test with CTest

## Context

A C++ project needs a description of how to compile it: which files, which libraries, which C++ version. This description should work on every platform and be able to download our dependencies.

Alternatives: a hand-written Makefile only, Meson, Bazel.

## Decision

We describe the build in `CMakeLists.txt` (C++17). CMake downloads Catch2 and LodePNG with `FetchContent`, at pinned versions. CTest, which comes with CMake, runs the tests.

Reason: common in C++ projects, and works across platforms.

## Status

Proposed

## Consequences

- One build description for every platform, and new contributors are likely to know it already.
- Dependencies are downloaded at a fixed version, so the build is the same for everyone.
- CMake is one more language to learn.
- The first configure needs a network connection to download the dependencies.
