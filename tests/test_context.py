from __future__ import annotations

from pathlib import Path

from alloy_codegen.context import discover_publication_root


def test_discover_publication_root_returns_sibling_repo(tmp_path: Path) -> None:
    repo_root = tmp_path / "alloy-codegen"
    repo_root.mkdir(parents=True, exist_ok=True)
    publication_root = tmp_path / "alloy-devices"
    (publication_root / ".git").mkdir(parents=True, exist_ok=True)

    discovered = discover_publication_root(repo_root)

    assert discovered == publication_root.resolve()


def test_discover_publication_root_returns_none_without_git_repo(tmp_path: Path) -> None:
    repo_root = tmp_path / "alloy-codegen"
    repo_root.mkdir(parents=True, exist_ok=True)
    (tmp_path / "alloy-devices").mkdir(parents=True, exist_ok=True)

    discovered = discover_publication_root(repo_root)

    assert discovered is None
