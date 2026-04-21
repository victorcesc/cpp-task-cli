---
name: cpp-task-cli-senior
description: >-
  Senior modern C++ engineering and agent workflow for the cpp-task-cli repo:
  C++20, RAII/ownership, cognitive-complexity-friendly structure, clang-tidy
  alignment, and scoped AI-assisted changes. Use when editing this project,
  implementing or reviewing its C++/CMake, or when the user asks for senior-level
  C++ practice or how the agent should manage work in this repository.
---

# cpp-task-cli — senior C++ and AI workflow

## Load and obey first

1. Read **`.cursor/rules.md`** for this repo (learning tone vs. implementation scope).
2. For build, test, and troubleshooting commands, follow **`docs/agent-build.md`** (out-of-source CMake).

## Engineering bar (code)

- **Language:** C++20, idiomatic STL; prefer clarity over cleverness.
- **Ownership:** Make lifetimes obvious; prefer RAII; avoid manual resource pairing unless teaching that topic explicitly.
- **Structure:** Keep functions shallow. When dispatch/parsing/REPL logic nests (`if`/`else`/`for` chains), **extract named helpers** so the top level reads as a short pipeline (parse → dispatch → per-command handlers). Use **early returns** where they reduce nesting.
- **Lint:** Respect **`.clang-tidy`** (`readability-*`, etc.). Treat **`readability-function-cognitive-complexity`** (default **25**) as the default budget for new or touched functions unless the user documents an exception.
- **Diff discipline:** Change only what the task needs; match local naming and comment density; no unrelated refactors.

## AI management (how to work in this repo)

- **Infer intent:** Prefer the user’s end goal (learn vs. ship a fix) from the thread; when unclear, ask one focused question instead of guessing a large redesign.
- **Teaching vs. implementing:** If **`.cursor/rules.md`** says not to give full solutions for conceptual questions, guide step-by-step with minimal excerpts. When the user **asks for code, a fix, or a refactor**, apply the senior engineering bar above and deliver a complete, buildable change for that request.
- **Verify:** After substantive C++ edits, run the build (and tests if any) using the paths/commands in **`docs/agent-build.md`**; report what was run and the outcome.
- **Honesty:** If the environment cannot compile, say so and still leave the repo internally consistent (includes, CMake lists, obvious errors fixed).
- **Artifacts:** Do not add docs or files the user did not request; keep new markdown out of the tree unless asked (project rules).

## Quick review checklist (optional pass before finishing)

- [ ] Behavior and public CLI/REPL contract unchanged unless the task asked otherwise
- [ ] No new cognitive-complexity hotspots in large functions without justification
- [ ] Includes and CMake updated when files are added or renamed
- [ ] Build instructions in `docs/agent-build.md` still accurate if workflow changed

## Related material

- Repo rules: `.cursor/rules.md`
- Build agent guide: `docs/agent-build.md`
