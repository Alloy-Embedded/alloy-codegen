"""Domain error types for alloy-codegen."""


class AlloyCodegenError(Exception):
    """Base exception for the codegen pipeline."""


class UnsupportedScopeError(AlloyCodegenError):
    """Raised when a requested vendor/family/device scope is unsupported."""


class StageExecutionError(AlloyCodegenError):
    """Raised when a pipeline stage cannot complete successfully."""

