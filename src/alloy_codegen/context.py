"""Execution context and repository path handling."""

from __future__ import annotations

import os
from dataclasses import dataclass
from pathlib import Path


def discover_repo_root() -> Path:
    """Locate the repository root by walking upward from this file."""
    current = Path(__file__).resolve()
    for parent in current.parents:
        if (parent / "pyproject.toml").exists():
            return parent
    raise RuntimeError("Could not locate alloy-codegen repository root.")


def discover_alloy_root(repo_root: Path) -> Path | None:
    """Locate a sibling Alloy repository when available."""
    candidate = repo_root.parent / "alloy"
    if (candidate / "CMakeLists.txt").exists() and (candidate / "src").exists():
        return candidate.resolve()
    return None


def discover_publication_root(repo_root: Path) -> Path | None:
    """Locate a sibling alloy-devices repository when available."""
    candidate = repo_root.parent / "alloy-devices"
    if (candidate / ".git").exists():
        return candidate.resolve()
    return None


@dataclass(frozen=True, slots=True)
class ExecutionContext:
    """Filesystem and source resolution context for the pipeline."""

    repo_root: Path
    source_root: Path | None
    pin_source_root: Path | None
    patch_root: Path
    source_cache_dir: Path
    artifact_root: Path
    publication_root: Path
    alloy_root: Path | None

    @classmethod
    def default(cls) -> ExecutionContext:
        repo_root = discover_repo_root()
        source_root = os.getenv("ALLOY_CODEGEN_CMSIS_SVD_ROOT")
        pin_source_root = os.getenv("ALLOY_CODEGEN_STM32_OPEN_PIN_DATA_ROOT")
        cache_dir = os.getenv("ALLOY_CODEGEN_SOURCE_CACHE_DIR")
        patch_root = os.getenv("ALLOY_CODEGEN_PATCH_ROOT")
        artifact_root = os.getenv("ALLOY_CODEGEN_ARTIFACT_ROOT")
        publication_root = os.getenv("ALLOY_CODEGEN_PUBLICATION_ROOT")
        alloy_root = os.getenv("ALLOY_CODEGEN_ALLOY_ROOT")
        return cls(
            repo_root=repo_root,
            source_root=Path(source_root).resolve() if source_root else None,
            pin_source_root=Path(pin_source_root).resolve() if pin_source_root else None,
            patch_root=Path(patch_root).resolve() if patch_root else (repo_root / "patches"),
            source_cache_dir=Path(cache_dir).resolve()
            if cache_dir
            else (repo_root / ".cache" / "sources"),
            artifact_root=Path(artifact_root).resolve()
            if artifact_root
            else (repo_root / ".artifacts"),
            publication_root=Path(publication_root).resolve()
            if publication_root
            else (
                discover_publication_root(repo_root) or (repo_root / ".published" / "alloy-devices")
            ),
            alloy_root=Path(alloy_root).resolve() if alloy_root else discover_alloy_root(repo_root),
        )

    def with_overrides(
        self,
        *,
        source_root: str | None = None,
        pin_source_root: str | None = None,
        patch_root: str | None = None,
        cache_dir: str | None = None,
        artifact_root: str | None = None,
        publication_root: str | None = None,
        alloy_root: str | None = None,
    ) -> ExecutionContext:
        return ExecutionContext(
            repo_root=self.repo_root,
            source_root=Path(source_root).resolve() if source_root else self.source_root,
            pin_source_root=(
                Path(pin_source_root).resolve() if pin_source_root else self.pin_source_root
            ),
            patch_root=Path(patch_root).resolve() if patch_root else self.patch_root,
            source_cache_dir=Path(cache_dir).resolve() if cache_dir else self.source_cache_dir,
            artifact_root=Path(artifact_root).resolve() if artifact_root else self.artifact_root,
            publication_root=Path(publication_root).resolve()
            if publication_root
            else self.publication_root,
            alloy_root=Path(alloy_root).resolve() if alloy_root else self.alloy_root,
        )
