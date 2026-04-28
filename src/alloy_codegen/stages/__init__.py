"""Stage entrypoints."""

from alloy_codegen.stages.emit import run as run_emit
from alloy_codegen.stages.fetch import run as run_fetch
from alloy_codegen.stages.normalize import run as run_normalize
from alloy_codegen.stages.pipeline import run as run_pipeline
from alloy_codegen.stages.publish import run as run_publish
from alloy_codegen.stages.validate import run as run_validate

STAGE_RUNNERS = {
    "fetch": run_fetch,
    "normalize": run_normalize,
    "validate": run_validate,
    "emit": run_emit,
    "publish": run_publish,
    "pipeline": run_pipeline,
}

__all__ = ["STAGE_RUNNERS"]
