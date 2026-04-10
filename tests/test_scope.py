from alloy_codegen.errors import UnsupportedScopeError
from alloy_codegen.scope import PipelineScope


def test_scope_defaults_to_bootstrap_family() -> None:
    scope = PipelineScope().validate_supported()
    assert scope.resolved_vendor() == "st"
    assert scope.resolved_family() == "stm32g0"


def test_scope_rejects_unknown_family() -> None:
    try:
        PipelineScope(vendor="st", family="stm32z99").validate_supported()
    except UnsupportedScopeError as exc:
        assert "stm32z99" in str(exc)
    else:
        raise AssertionError("Expected UnsupportedScopeError for unknown family.")


def test_scope_accepts_stm32f4_family() -> None:
    scope = PipelineScope(vendor="st", family="stm32f4").validate_supported()
    assert scope.resolved_vendor() == "st"
    assert scope.resolved_family() == "stm32f4"


def test_scope_auto_resolves_family_from_device() -> None:
    scope = PipelineScope(device="stm32f401re").validate_supported()
    assert scope.resolved_vendor() == "st"
    assert scope.resolved_family() == "stm32f4"

