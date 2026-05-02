"""alloy-codegen package.

Public Python surface:

- :func:`generate` — turn a project config into a per-device
  artifact tree.  Mirrors the ``alloy-codegen <target>`` CLI but
  consumable from alloy-cli + agents.
- :class:`alloy_codegen.errors.ConfigError` — config-side
  preconditions.
- :class:`alloy_codegen.errors.StageExecutionError` — pipeline
  failures inside the loader / synthesiser.
"""

from alloy_codegen.entrypoint import generate
from alloy_codegen.errors import ConfigError, StageExecutionError
from alloy_codegen.version import __version__

__all__ = [
    "ConfigError",
    "StageExecutionError",
    "__version__",
    "generate",
]
