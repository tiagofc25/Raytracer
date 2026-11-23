# 4. Makefile shortcuts for the CMake commands

## Context

The CMake and CTest commands are long and hard to remember when we build or run by hand. In JavaScript, `npm run build` or `npm run start` play this role; C++ has no standard equivalent.

Alternatives: type the CMake commands each time, CMake presets, or shell scripts.

## Decision

A small `Makefile` at the root wraps the CMake commands: `make build`, `make run`, `make test` and `make clean` (`make start` is an alias of `make run`). CMake still describes the build (see ADR 2); the Makefile only calls it.

Reason: commands that are easy to remember.

## Status

Proposed

## Consequences

- Four short commands, the same for everyone, in the README and AGENTS.md.
- Make is one more tool. It is in the dev container, but not installed by default on Windows outside it.
- The Makefile must be kept in sync with how we call CMake.
