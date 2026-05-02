"""Unit tests for the ST :class:`ClockBackend` lowering layer.

Covers the foundational pass landed under
``complete-clock-tree-runtime-init``:

* Registry exposes the ST backend keyed by vendor.
* Post-reset profiles lower to a no-op barrier.
* PLL profiles emit the canonical FLASH → PLL → SYSCLK → barrier
  sequence in the right order.
* Profiles missing ``hclk_hz`` lower to a stub with a documented
  comment instead of crashing synthesis (incremental rollout).
* Synthesised :class:`SynthesisedDevice` carries the lowered
  program for every profile when the device's vendor has a
  registered backend.
"""

from __future__ import annotations

from alloy_codegen.emit_v2_1.clock_backends import backend_for, registry
from alloy_codegen.ir.synthesised import ClockProgramStep
from alloy_codegen.sources.alloy_devices_yml import load_with_synthesis


def test_registry_exposes_st_backend() -> None:
    backends = registry()
    assert "st" in backends
    assert backend_for("st") is backends["st"]
    assert backend_for("ST") is backends["st"]   # case-insensitive


def test_unknown_vendor_returns_none() -> None:
    assert backend_for("acme-corp") is None


def test_post_reset_profile_lowers_to_no_op_barrier() -> None:
    canonical, _ = load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )
    backend = backend_for("st")
    assert backend is not None
    post_reset = next(
        p for p in canonical.clock.profiles if p.kind == "post-reset"
    )
    steps = backend.emit_profile(post_reset, canonical)
    # One barrier_dsb step with a "no-op" comment — chip is
    # already at this state at reset.
    assert len(steps) == 1
    assert steps[0].kind == "barrier_dsb"
    assert "no-op" in steps[0].comment


def test_pll_profile_lowers_in_canonical_order() -> None:
    canonical, _ = load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )
    backend = backend_for("st")
    assert backend is not None
    pll_profile = next(
        p for p in canonical.clock.profiles if p.kind == "recommended"
    )
    steps = backend.emit_profile(pll_profile, canonical)

    kinds = [s.kind for s in steps]
    # FLASH latency MUST come before any RCC write that raises HCLK.
    assert kinds[0] == "flash_latency"
    # The bring-up envelope ends with __DSB(); __ISB();.
    assert kinds[-2:] == ["barrier_dsb", "barrier_isb"]
    # PLL coefficient writes happen before PLLON.
    assert kinds.index("set_bits") > kinds.index("write_field")
    # SYSCLK source switch (write_field on RCC.CFGR.SW) and its
    # readback (spin on RCC.CFGR.SWS) appear after PLL lock.
    set_pll_idx = next(i for i, s in enumerate(steps)
                       if s.kind == "set_bits" and "pll" in (s.field_id or ""))
    sw_idx = next(i for i, s in enumerate(steps)
                  if s.kind == "write_field" and (s.field_id or "").endswith(":sw"))
    assert sw_idx > set_pll_idx


def test_pll_profile_carries_pllm_pln_pllr() -> None:
    canonical, _ = load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )
    backend = backend_for("st")
    assert backend is not None
    pll_profile = next(
        p for p in canonical.clock.profiles if p.id == "pll-hsi16-64mhz"
    )
    steps = backend.emit_profile(pll_profile, canonical)

    coefs: dict[str, int] = {}
    for s in steps:
        if s.kind != "write_field":
            continue
        for coef in ("pllm", "plln", "pllr", "pllp", "pllq"):
            if (s.field_id or "").endswith(f":{coef}"):
                coefs[coef] = s.value
    assert coefs["pllm"] == 1
    assert coefs["plln"] == 8
    assert coefs["pllr"] == 2


def test_synthesised_device_carries_clock_program() -> None:
    canonical, syn = load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )
    # Every profile gets a lowered program (the dict is keyed by
    # profile.id; values are deterministic ClockProgramStep tuples).
    assert set(syn.clock_program_steps.keys()) == {p.id for p in canonical.clock.profiles}
    # And each entry is non-empty (post-reset is a single barrier;
    # PLL profile is the full 11-step program).
    for prog in syn.clock_program_steps.values():
        assert all(isinstance(s, ClockProgramStep) for s in prog)
        assert len(prog) >= 1


def test_missing_hclk_lowers_to_documented_stub() -> None:
    """Soft fallback when a profile YAML lacks hclk_hz.

    The first-cut data-quality contract is incremental: missing
    fields surface as a comment in the generated source (so the
    diff is visible) rather than a synthesis-time crash.
    """
    from dataclasses import replace

    canonical, _ = load_with_synthesis(
        vendor="st", family="stm32g0", device="stm32g071rb",
    )
    backend = backend_for("st")
    assert backend is not None
    # Take an existing PLL profile and strip hclk_hz to simulate
    # a YAML row that hasn't been enriched yet.
    pll = next(p for p in canonical.clock.profiles if p.kind == "recommended")
    bare = replace(pll, hclk_hz=None)
    steps = backend.emit_profile(bare, canonical)
    assert len(steps) == 1
    assert steps[0].kind == "barrier_dsb"
    assert "skipped" in steps[0].comment.lower()
