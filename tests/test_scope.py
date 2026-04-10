from alloy_codegen.errors import UnsupportedScopeError
from alloy_codegen.scope import PipelineScope


def test_scope_defaults_to_bootstrap_family() -> None:
    scope = PipelineScope().validate_supported()
    assert scope.resolved_vendor() == "st"
    assert scope.resolved_family() == "stm32g0"


def test_scope_rejects_non_bootstrap_family() -> None:
    try:
        PipelineScope(vendor="st", family="stm32f4").validate_supported()
    except UnsupportedScopeError as exc:
        assert "stm32g0" in str(exc)
    else:
        raise AssertionError("Expected UnsupportedScopeError for non-bootstrap family.")

