"""Execution context and repository path handling."""

from __future__ import annotations

import os
import re
from dataclasses import dataclass
from pathlib import Path

LEGACY_SOURCE_ENV_VARS = {
    "cmsis-svd-data": "ALLOY_CODEGEN_CMSIS_SVD_ROOT",
    "stm32-open-pin-data": "ALLOY_CODEGEN_STM32_OPEN_PIN_DATA_ROOT",
}
SOURCE_ENV_PREFIX = "ALLOY_CODEGEN_SOURCE_"
SOURCE_ENV_SUFFIX = "_ROOT"


def source_id_to_env_var(source_id: str) -> str:
    """Translate a logical source identifier into an environment variable name."""
    sanitized = re.sub(r"[^A-Z0-9]+", "_", source_id.upper()).strip("_")
    return f"{SOURCE_ENV_PREFIX}{sanitized}{SOURCE_ENV_SUFFIX}"


def discover_source_overrides() -> dict[str, Path]:
    """Collect named source overrides from current environment variables."""
    overrides: dict[str, Path] = {}

    for source_id, env_var in LEGACY_SOURCE_ENV_VARS.items():
        raw_value = os.getenv(env_var)
        if raw_value:
            overrides[source_id] = Path(raw_value).resolve()

    for env_var, raw_value in os.environ.items():
        if not env_var.startswith(SOURCE_ENV_PREFIX) or not env_var.endswith(SOURCE_ENV_SUFFIX):
            continue
        source_key = env_var.removeprefix(SOURCE_ENV_PREFIX).removesuffix(SOURCE_ENV_SUFFIX)
        source_id = source_key.lower().replace("_", "-")
        if raw_value:
            overrides[source_id] = Path(raw_value).resolve()

    return overrides


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
    source_roots: dict[str, Path]
    patch_root: Path
    source_cache_dir: Path
    artifact_root: Path
    publication_root: Path
    alloy_root: Path | None

    @classmethod
    def default(cls) -> ExecutionContext:
        repo_root = discover_repo_root()
        cache_dir = os.getenv("ALLOY_CODEGEN_SOURCE_CACHE_DIR")
        patch_root = os.getenv("ALLOY_CODEGEN_PATCH_ROOT")
        artifact_root = os.getenv("ALLOY_CODEGEN_ARTIFACT_ROOT")
        publication_root = os.getenv("ALLOY_CODEGEN_PUBLICATION_ROOT")
        alloy_root = os.getenv("ALLOY_CODEGEN_ALLOY_ROOT")
        return cls(
            repo_root=repo_root,
            source_roots=discover_source_overrides(),
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
        source_overrides: dict[str, str] | None = None,
        source_root: str | None = None,
        pin_source_root: str | None = None,
        patch_root: str | None = None,
        cache_dir: str | None = None,
        artifact_root: str | None = None,
        publication_root: str | None = None,
        alloy_root: str | None = None,
    ) -> ExecutionContext:
        updated_sources = dict(self.source_roots)
        if source_overrides:
            updated_sources.update(
                {
                    source_id: Path(source_path).resolve()
                    for source_id, source_path in source_overrides.items()
                }
            )
        if source_root:
            updated_sources["cmsis-svd-data"] = Path(source_root).resolve()
        if pin_source_root:
            updated_sources["stm32-open-pin-data"] = Path(pin_source_root).resolve()
        return ExecutionContext(
            repo_root=self.repo_root,
            source_roots=updated_sources,
            patch_root=Path(patch_root).resolve() if patch_root else self.patch_root,
            source_cache_dir=Path(cache_dir).resolve() if cache_dir else self.source_cache_dir,
            artifact_root=Path(artifact_root).resolve() if artifact_root else self.artifact_root,
            publication_root=Path(publication_root).resolve()
            if publication_root
            else self.publication_root,
            alloy_root=Path(alloy_root).resolve() if alloy_root else self.alloy_root,
        )

    def source_root_for(self, source_id: str) -> Path | None:
        """Return the configured override path for a logical source identifier."""
        return self.source_roots.get(source_id)
