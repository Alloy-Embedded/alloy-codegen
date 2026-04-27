#!/usr/bin/env bash
# Wrapper for the ``auto-update-goldens`` workflow.
#
# Runs pytest with ``--update-goldens``, then prints
# ``git diff --stat tests/fixtures/`` so reviewers can see the
# generated fixture changes before committing.  Refuses to run if
# non-fixture files are dirty (the conftest fixture aborts in that
# case).
#
# Usage:
#   scripts/update_goldens_pytest.sh [extra pytest args...]
#
# The legacy ``scripts/update_goldens.py`` still exists for the
# emit-pipeline-driven fixture refresh that predates the flag
# (covers fixtures the pytest-driven path does not yet touch).

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$REPO_ROOT"

echo "==> pytest --update-goldens $*"
pytest --update-goldens "$@"

echo
echo "==> git diff --stat tests/fixtures/"
git diff --stat -- tests/fixtures/ || true
