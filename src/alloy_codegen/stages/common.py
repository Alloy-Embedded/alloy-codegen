"""Common stage models and helpers."""

from __future__ import annotations

from dataclasses import dataclass
from typing import Any, Literal

from alloy_codegen.scope import PipelineScope
from alloy_codegen.serialization import to_primitive

type StageStatus = Literal["completed", "failed"]


@dataclass(frozen=True, slots=True)
class StageResult:
    """Result from a pipeline stage."""

    stage: str
    scope: PipelineScope
    status: StageStatus
    payload: Any
    warnings: tuple[str, ...] = ()

    @property
    def is_successful(self) -> bool:
        """Return whether the stage completed successfully."""
        return self.status == "completed"

    @property
    def is_failed(self) -> bool:
        """Return whether the stage reported a failure."""
        return self.status == "failed"

    def to_dict(self) -> dict[str, object]:
        payload = (
            self.payload.to_dict()
            if hasattr(self.payload, "to_dict") and callable(self.payload.to_dict)
            else to_primitive(self.payload)
        )
        return {
            "stage": self.stage,
            "scope": self.scope.to_dict(),
            "status": self.status,
            "payload": payload,
            "warnings": list(self.warnings),
        }
