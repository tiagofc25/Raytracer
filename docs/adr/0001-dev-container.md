# 1. Build in a dev container

## Context

Every contributor needs the same compiler, CMake and Git to build and test the project. Without a shared setup, each laptop (Windows, macOS, Linux) has different versions, and a build that works on one machine can fail on another.

Alternatives: let everyone install the tools on their own machine, or use a virtual machine.

## Decision

We build and test inside a dev container (`.devcontainer/`): a Docker image based on Ubuntu 24.04 with `build-essential`, CMake, GDB and Git. It opens in VS Code or Zed.

Reason: the same tools on every laptop and for every contributor.

## Status

Proposed

## Consequences

- Everyone builds with the same tools, so "it works on my machine" problems go away.
- Everyone needs Docker.
- The container runs Linux: it does not test native macOS or Windows builds, and render times may differ from a native build.
