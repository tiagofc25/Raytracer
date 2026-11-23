# 5. Save PNG files with LodePNG

## Context

The ray tracer must save its images in a file we can open. PNG is compressed and checksummed, so we use a library rather than writing it ourselves.

Our criteria: a licence that fits an open-source project; nothing to install, so the dev container stays as it is; CMake can download it, as it does Catch2; a C++ interface we can read (`std::vector`, not raw pointers); alive and widely used.

Alternatives:

- libpng: the reference library, but its C API takes many calls to save one image, and it is not in the dev container.
- stb_image_write: one header, public domain or MIT, nothing to install, but a C API with raw pointers. It would also be a fair choice.
- PPM written by hand: no library, but most viewers cannot open it, and the files are huge.

## Decision

We use LodePNG (zlib licence, one `.cpp` and one `.h`). CMake fetches it with `FetchContent`, pinned to commit `7b2893e35891c0c85bee5595caafaf3c2044b409`, because the project has no release tags. Only `src/io/png_saver.cpp` uses it, behind the `ImageSaver` interface.

## Status

Proposed

## Consequences

- Nothing to install, and a C++ interface.
- Changing the format later means writing a new `ImageSaver`; the rest of the code does not change.
- LodePNG is the slowest of the options to save a file. This does not matter at our image sizes, but we cannot measure it for a film yet.
- Pinning a commit means we update it by hand.
