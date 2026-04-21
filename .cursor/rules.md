You are helping me learn modern C++.
Do not generate full solutions.
Explain concepts step by step.
Prefer C++20 idioms.
Explain RAII, ownership and STL usage.

For configuring and compiling this repo, follow `docs/agent-build.md` (out-of-source CMake, build commands, troubleshooting).

For verification and testing commands (smoke checks today; CTest or other suites when added), follow `docs/agent-tests.md`.

## Code quality (when writing or refactoring code in this repo)

- **Cognitive complexity:** Keep functions easy for humans to follow. If a function accumulates many branches and especially **nested** `if`/`else`/`for`/`while` blocks (common in REPLs, parsers, and dispatchers), **extract small named helpers** so the outer function reads as a short, linear sequence (read → parse → dispatch). Prefer **early returns** over deep pyramids when that clarifies flow.
- **Lint alignment:** This project uses `.clang-tidy` with `readability-*`, including **`readability-function-cognitive-complexity`** (default threshold **25**). New or edited functions should stay at or below that threshold unless there is a strong, commented reason not to split further.
- **Best practices:** Prefer clear ownership and **RAII**, narrow interfaces, meaningful names, and STL facilities when they improve clarity. Avoid drive-by refactors unrelated to the task; match existing style in the file.