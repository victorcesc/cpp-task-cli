# Agent guide: building `learn-modern-cpp`

Use this document when configuring or compiling the project in a clean environment (CI, sandbox, or new machine).

## Prerequisites

- **CMake** 3.16 or newer (`cmake --version`).
- A **C++20** compiler (GCC 10+, Clang 10+, or MSVC with `/std:c++20`).

## Recommended layout

- **Out-of-source build**: all generated files go under `build/`, never commit them.
- **Project root**: the directory that contains the top-level `CMakeLists.txt`.

Assume the working directory is the repository root unless stated otherwise.

## Configure (first time or after CMake changes)

From the repository root:

```bash
cmake -S . -B build
```

Optional **Debug** build (single-config generators such as Unix Makefiles or Ninja on Linux):

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```

Optional **Ninja** (faster incremental builds if installed):

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
```

## Build (incremental)

```bash
cmake --build build
```

Parallel jobs (portable):

```bash
cmake --build build --parallel
```

## Output

- **Executable**: `build/learn-modern-cpp` (on Windows, `build/learn-modern-cpp.exe`).
- **`compile_commands.json`**: emitted under `build/` because `CMAKE_EXPORT_COMPILE_COMMANDS` is `ON`. Point clangd / static analysis at `build/compile_commands.json`, or symlink it into the repo root if your tooling expects it there:

```bash
ln -sf build/compile_commands.json compile_commands.json
```

The root `.gitignore` may ignore `compile_commands.json`; that is intentional so local symlinks are not committed.

## Clean reconfigure

If CMake cache is wrong or you switched generators:

```bash
rm -rf build
cmake -S . -B build
cmake --build build
```

## Smoke test

Non-interactive (requires a supported argv subcommand in `main.cpp`; adjust if commands differ):

```bash
./build/learn-modern-cpp list
```

Interactive REPL without a TTY (pipes `help` then `quit`):

```bash
printf 'help\nquit\n' | ./build/learn-modern-cpp
```

## Troubleshooting for agents

| Issue | What to do |
|--------|------------|
| `Could not find CMAKE_ROOT` / broken CMake | Prefer the **system** CMake (e.g. `PATH=/usr/bin:/bin` on Linux, or `which cmake` and use a Kitware install). |
| Wrong C++ standard | `CMakeLists.txt` sets `CMAKE_CXX_STANDARD 20` and `CMAKE_CXX_STANDARD_REQUIRED ON`; fix the toolchain, not the standard flag, unless the project is intentionally upgraded. |
| Stale objects after big refactors | `rm -rf build` then configure + build again. |
| Missing sources in `add_executable` | Edit `CMakeLists.txt` so every `.cpp` that must be linked is listed; then re-run `cmake -S . -B build`. |

## What not to do

- Do not run `cmake` **inside** `build/` as the source tree unless you know the project supports in-source builds (this project expects `-S . -B build`).
- Do not commit the `build/` directory.

## Current targets (sanity check)

The executable target is **`learn-modern-cpp`**, built from the sources listed in `CMakeLists.txt` (as of this guide: `src/main.cpp`, `src/Task.cpp`, `src/ReplLogic.cpp`). If linking fails after adding files, update `add_executable(...)` and reconfigure.
