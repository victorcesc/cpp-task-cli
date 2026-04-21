---
name: experimental
description: >-
  Experimental placeholder skill for learning Cursor Agent Skills structure
  (YAML frontmatter, body, discovery). Not wired into project rules; load
  manually when exploring how skills work in this repository.
---

# Experimental — learning skills

## Purpose

This skill exists so you can inspect a **minimal real `SKILL.md`** under `.cursor/skills/` without affecting `.cursor/rules.md` or other skills.

## How skills are discovered

- Cursor uses the **`name`** and **`description`** in the YAML frontmatter to identify and suggest the skill.
- The **`description`** should say **what** the skill does and **when** to use it (third person, concrete triggers).

## How to use this one

Nothing in the repo points here on purpose. To try it:

- Open this folder in the editor and read **`SKILL.md`**, or
- Attach or reference this skill from the Cursor UI when your client supports selecting a skill for a chat.

## Safe edits to try

- Change **`description`** and notice how wording affects when the agent might pick it up.
- Add a short **## Checklist** section with bullet steps.
- Optionally add sibling files later (for example `reference.md`) and link them from the body; keep **`SKILL.md`** as the entry point.

## Related reading

- Official “create skill” guidance lives in Cursor’s create-skill documentation (personal or global skills under `~/.cursor/skills/`, project skills under `.cursor/skills/<name>/`).
