@AGENTS.md

# Claude Code

- The rules above are the single source of truth for every agent. Do not duplicate them here.
- Project skills live in `.agents/skills/*/SKILL.md` (also exposed to Claude Code through
  `.claude/skills`). Read the matching skill before a translation-unit review, a build/regression
  verification or a portability review.
- Run `python3 .agents/scripts/agent_doctor.py` at the start of a session.
- Local notes in `notes/` (gitignored, may not exist in a fresh clone) are optional background,
  never a source of truth for the repository.
