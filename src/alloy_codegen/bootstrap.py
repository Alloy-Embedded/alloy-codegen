"""Bootstrap family configuration."""

from __future__ import annotations

BOOTSTRAP_VENDOR = "st"
BOOTSTRAP_FAMILY = "stm32g0"
IR_SCHEMA_VERSION = "1.0.0"
PIPELINE_NAME = "alloy-codegen"
PUBLICATION_TARGET_REPOSITORY = "alloy-devices"
ARTIFACT_LAYOUT_VERSION = "alloy-devices-v1"
CPP_CONTRACT_VERSION = "alloy-cpp-bootstrap-v1"
BOOTSTRAP_DEVICE_NAMES = (
    "stm32g030f6",
    "stm32g071rb",
    "stm32g0b1re",
)


def bootstrap_device_names() -> tuple[str, ...]:
    """Return supported bootstrap device names in stable order."""
    return tuple(sorted(BOOTSTRAP_DEVICE_NAMES))
