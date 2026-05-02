"""Domain error types for alloy-codegen."""


class AlloyCodegenError(Exception):
    """Base exception for the codegen pipeline."""


class UnsupportedScopeError(AlloyCodegenError):
    """Raised when a requested vendor/family/device scope is unsupported."""


class StageExecutionError(AlloyCodegenError):
    """Raised when a pipeline stage cannot complete successfully."""


class ReleaseMetadataError(AlloyCodegenError):
    """Raised when release metadata cannot be derived from a publish report."""


class ConfigError(AlloyCodegenError):
    """Raised when ``generate(config, out_dir)`` cannot resolve a target.

    Distinct from :class:`StageExecutionError`: ConfigError fires
    *before* we touch the YAML loader, signalling that the caller
    needs to fix their config (missing chip, board not resolved,
    unknown vendor / family) — not a bug in alloy-codegen itself.
    """
