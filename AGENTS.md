# AGENTS.md

C++17 ray tracer, built with CMake, tested with Catch2 + CTest, inside a dev container.

## Commands

Run them inside the dev container, from the project root.

| Command      | What it does                                   |
|--------------|------------------------------------------------|
| `make build` | Configure and compile into `build/`            |
| `make run`   | Build, then render `image.png`                 |
| `make test`  | Build, then run every test with CTest          |
| `make clean` | Delete `build/`                                |

## Architecture decisions

Our architecture decisions are in `docs/adr/`. Read them before changing the build, the tools or the test setup.

- Never go against an accepted ADR. To change a decision, write a new ADR with status Proposed and ask the user.
- Never set an ADR to Accepted.

## Code style

- Private member variables start with `_` (for example `_origin`).
- No `get` prefix on getters: `ray.origin()`, not `ray.getOrigin()`.
- Files are grouped by concept: `src/<concept>/<name>.h` and `.cpp`, with tests in `tests/<concept>/<name>_test.cpp`. Add new `.cpp` files to `CMakeLists.txt`.
- Work with TDD: write the failing test first.
