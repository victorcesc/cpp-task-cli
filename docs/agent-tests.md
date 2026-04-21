# Agent guide: testing `learn-modern-cpp`

Use this document when verifying behavior after changes (CI, sandbox, or local agent runs).

## Prerequisites

Same as **`docs/agent-build.md`**: CMake 3.16+, C++20 toolchain, and a configured out-of-source build under `build/` from the repository root.

## Current automated test status

The top-level **`CMakeLists.txt`** does **not** yet define `enable_testing()`, CTest labels, or a linked unit-test executable (for example GoogleTest). There is **no** `ctest` suite to run today.

Until that exists, treat **build + smoke commands** below as the default verification path.

## Always run first: build

From the repository root (see **`docs/agent-build.md`** for options and troubleshooting):

```bash
cmake -S . -B build
cmake --build build
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
clang-tidy src/main.cpp src/Task.cpp -p build
```

Paths and `compile_commands.json` location are described in **`docs/agent-build.md`**.

## When a real test target is added

Update this guide in the **same change** that introduces tests. Typical CMake additions:

1. `enable_testing()` in **`CMakeLists.txt`**
2. A test executable target (or several) and `add_test(NAME ... COMMAND ...)`
3. Agents then run **`ctest --test-dir build`** (or the project’s chosen output directory) after `cmake --build build`

Document the **canonical** command here once it exists; avoid duplicating long CMake snippets if **`CMakeLists.txt`** is the source of truth.

## What not to do

- Do not assume **`ctest`** passes until **`CMakeLists.txt`** actually registers tests.
- Do not commit **`build/`** or generated test artifacts.
