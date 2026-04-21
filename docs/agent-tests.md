# Agent guide: testing `learn-modern-cpp`

Use this document when verifying behavior after changes (CI, sandbox, or local agent runs).

## Prerequisites

Same as **`docs/agent-build.md`**: CMake 3.16+, C++20 toolchain, and a configured out-of-source build under `build/` from the repository root.

## Current automated test status

The top-level **`CMakeLists.txt`** enables **`include(CTest)`** and, when **`BUILD_TESTING`** is enabled (CTest default), uses **FetchContent** to pull **Catch2** and builds the **`unit-tests`** target (`tests/test_task.cpp`, `tests/test_repl.cpp`, linked with `src/Task.cpp` and `src/ReplLogic.cpp`). Tests are registered with **`add_test(NAME unit-tests ...)`**.

**Canonical command** after a successful build:

```bash
ctest --test-dir build --output-on-failure
```

First configure needs network access so CMake can clone Catch2.

## Always run first: build

From the repository root (see **`docs/agent-build.md`** for options and troubleshooting):

```bash
cmake -S . -B build
cmake --build build
```

## Unit tests

```bash
ctest --test-dir build --output-on-failure
```

Or run the test binary directly:

```bash
./build/unit-tests
```

## Smoke checks (non-interactive)

Requires a successful build. Executable path is **`build/learn-modern-cpp`** (on Windows, `build/learn-modern-cpp.exe`).

**List command** (adjust if CLI subcommands change in `src/main.cpp`):

```bash
./build/learn-modern-cpp list
```

**REPL without a TTY** (pipes `help` then `quit`):

```bash
printf 'help\nquit\n' | ./build/learn-modern-cpp
```

## Optional static checks

If **`clang-tidy`** is installed and you want extra signal beyond the compiler:

```bash
clang-tidy src/main.cpp src/Task.cpp src/ReplLogic.cpp -p build
```

**`tests/.clang-tidy`** relaxes the same few Catch2-related checks when you run **`clang-tidy tests/... -p build`**. The repo **`.clangd`** applies equivalent **`ClangTidy: Remove`** entries for the language server (so the IDE matches) and adds **`-Wno-c2y-extensions`** only for **`tests/*.cpp`** for the `__COUNTER__` diagnostic. Production sources under **`src/`** still follow the stricter root **`.clang-tidy`** when linting those paths from the CLI.

Paths and `compile_commands.json` location are described in **`docs/agent-build.md`**.

## What not to do

- Do not commit **`build/`** or generated test artifacts.
