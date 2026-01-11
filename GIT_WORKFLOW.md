# Git Workflow – PlugFrame / OpLink

This document describes the Git branching strategy used for the PlugFrame and
OpLink projects.

The objective is to keep a **simple, readable and disciplined workflow** that
supports parallel feature development and controlled releases, even in a solo
development context.

---

## Main Branches

### `master`
- Always **stable and releasable**
- Contains only released versions
- Version tags (`vX.Y.Z`) are created on this branch
- No direct commits (except exceptional cases)

---

### `develop`
- Integration branch
- Receives completed features
- May contain work not yet released
- Should remain buildable on the host platform

---

## Feature Branches

### `feature/*`
- One branch per feature or technical topic
- Usually created from `develop`
- Short-lived
- Merged back into `develop` using non fast-forward merges

Examples:
- `feature/my-feature`
- `feature/my-feature2`

### Feature merge example
```bash
git checkout develop
git merge --no-ff feature/my-feature
git branch -d feature/my-feature
```
---

## Release Branches

### `release/*`
- Used to prepare a new release
- Created from develop

Represents a stabilization phase

Used mainly for:
- Bug fixes
- Documentation updates
- Version bump
- Build or packaging adjustments

A release branch allows development on develop to continue while the release
is being finalized.

Examples:
- `release/0.3.0`
- `release/1.0.0`

---

## Merge Policy

All merges use non fast-forward (--no-ff) merges to keep the history clear
and readable.

Recommended Git configuration:
```bash
git config --global merge.ff false
```
---

## Versioning

The projects follow Semantic Versioning:

MAJOR.MINOR.PATCH
- PATCH : bug fixes
- MINOR : new features (backward compatible)
- MAJOR : breaking changes

---

This workflow is intentionally lightweight and may evolve as the projects grow.

