# Papercuts

Small, actionable friction found during agent work. Agents append entries when
they hit a solvable hurdle; they do not stop the current task to fix one.

## Open

<!-- Keep entries short. Append newest entries at the top. Do not include secrets. -->

### check-links strips underscores from heading anchors

- Friction: `effigy skill run northstar-lean/cut -- check-links` slugs a
  heading by deleting `_`, so `### \`vst2_paths\`` becomes `vst2paths` and
  `config-reference.md#vst2_paths` is reported missing. GitHub keeps the
  underscore.
- Impact: one correct anchor in `docs/setup/troubleshooting.md` is a permanent
  false positive, and cannot be fixed without writing the link in a form GitHub
  will not resolve.
- Plausible fix: keep `_` in `scripts/cut.py`'s `slug()` and match GitHub's
  slugger, or compare against GitHub's rendering.
- Surface: `northstar-lean` skill, `scripts/cut.py` `check-links`.
