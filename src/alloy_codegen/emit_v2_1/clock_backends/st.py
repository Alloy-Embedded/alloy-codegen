"""STM32 :class:`ClockBackend` — covers F0/F1/F3/F4/G0/G4/H7
(and any future ST family that uses the standard RCC + FLASH
shape).

The lowering follows the canonical bring-up recipe documented
across every STM32 reference manual:

  1. (Optional) increase FLASH wait-states *before* raising HCLK.
  2. Power up HSE / HSI48 if the profile requests it.
  3. Configure the PLL (M, N, R, P, Q as carried by the profile).
  4. Power up the PLL and spin on ``RCC.CR.PLLRDY``.
  5. Switch ``RCC.CFGR.SW`` to the target source and spin on
     ``RCC.CFGR.SWS`` confirming the switch landed.
  6. Program HCLK / PCLK1 / PCLK2 prescalers.
  7. (Optional) lower FLASH wait-states *after* lowering HCLK.

The backend is intentionally small — every register and field
named here is documented in every STM32 reference manual under
the same names.  The IR's ``clock.domains`` graph is consulted
for the prescaler-encoding tables (those *do* differ per family)
but not for the order or barrier discipline (those are family-
invariant).

Where the IR doesn't yet carry the data we need (FLASH WS
threshold table per family, PLL coefficient ranges), this
backend uses a small hard-coded fallback table keyed by family
name and **emits a comment** in the program so the generated
source is auditable.  Promoting those tables out of the
fallback into ``family.yml`` is tracked under the
``complete-clock-tree-runtime-init`` proposal's tasks 1.1 / 1.2.
"""

from __future__ import annotations

from collections.abc import Mapping

from alloy_codegen.errors import StageExecutionError
from alloy_codegen.ir.synthesised.clock_program import ClockProgramStep
from alloy_codegen.ir.v2_1 import CanonicalDevice, ClockProfile

# ---------------------------------------------------------------------------
# Family fallbacks for data not yet promoted into the YAML.
#
# Each tuple row is ``(min_hz, max_hz_inclusive, ws, encoding)``.
# encoding is the value to write into ``FLASH.ACR.LATENCY``.
# Sources: STM32 G0 RM0444 §3.3.4, F4 RM0090 §3.4, H7 RM0433 §4.9.1.
# ---------------------------------------------------------------------------
_FLASH_WS_FALLBACK: dict[str, tuple[tuple[int, int, int, int], ...]] = {
    "stm32g0": (
        (0,        24_000_000, 0, 0),
        (24_000_001, 48_000_000, 1, 1),
        (48_000_001, 64_000_000, 2, 2),
    ),
    "stm32f0": (
        (0,        24_000_000, 0, 0),
        (24_000_001, 48_000_000, 1, 1),
    ),
    "stm32f1": (
        (0,        24_000_000, 0, 0),
        (24_000_001, 48_000_000, 1, 1),
        (48_000_001, 72_000_000, 2, 2),
    ),
    "stm32f3": (
        (0,        24_000_000, 0, 0),
        (24_000_001, 48_000_000, 1, 1),
        (48_000_001, 72_000_000, 2, 2),
    ),
    "stm32f4": (
        (0,        30_000_000, 0, 0),
        (30_000_001, 60_000_000, 1, 1),
        (60_000_001, 90_000_000, 2, 2),
        (90_000_001, 120_000_000, 3, 3),
        (120_000_001, 150_000_000, 4, 4),
        (150_000_001, 168_000_000, 5, 5),
        (168_000_001, 180_000_000, 6, 6),
    ),
    "stm32g4": (
        (0,        34_000_000, 0, 0),
        (34_000_001, 68_000_000, 1, 1),
        (68_000_001, 102_000_000, 2, 2),
        (102_000_001, 136_000_000, 3, 3),
        (136_000_001, 170_000_000, 4, 4),
    ),
    "stm32h7": (
        (0,        70_000_000, 0, 0),
        (70_000_001, 140_000_000, 1, 1),
        (140_000_001, 210_000_000, 2, 2),
        (210_000_001, 280_000_000, 3, 3),
        (280_000_001, 480_000_000, 4, 4),
    ),
}

# Sentinel timeout for spin-loops.  The runtime-lite contract
# documents this constant; consumers may override at compile time.
_PLL_LOCK_TIMEOUT_US = 10_000  # 10 ms


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------


def _flash_ws_for(family: str, hclk_hz: int) -> tuple[int, int]:
    """Return ``(ws, encoding)`` for the given HCLK on ``family``.

    Raises :class:`StageExecutionError` when no row matches —
    the YAML asks for a frequency the family can't reach.
    """
    rows = _FLASH_WS_FALLBACK.get(family.lower())
    if rows is None:
        raise StageExecutionError(
            f"st clock backend: no FLASH wait-state table for family {family!r}; "
            f"add an entry to _FLASH_WS_FALLBACK or populate "
            f"identity.flash_wait_states in family.yml"
        )
    for min_hz, max_hz, ws, enc in rows:
        if min_hz <= hclk_hz <= max_hz:
            return ws, enc
    raise StageExecutionError(
        f"st clock backend: HCLK {hclk_hz} Hz is outside the supported "
        f"range for family {family!r} (max in fallback table: {rows[-1][1]} Hz)"
    )


def _is_pll_source(sysclk_source: str) -> bool:
    """ST profiles that use the PLL name it like ``pll_hsi16`` or
    ``pll_hse``; reset profiles name a bare oscillator."""
    return sysclk_source.startswith("pll")


def _pll_input_oscillator(sysclk_source: str, oscillators: Mapping[str, object]) -> str:
    """Resolve ``pll_hsi16`` → ``hsi`` (the oscillator key actually
    declared in ``clock.oscillators``).

    ST profiles encode the PLL input by a *naming-convention suffix*
    (``pll_hsi16``, ``pll_hse``, ``pll_msi``); the actual oscillator
    key may be a prefix of that suffix (G0's HSI16 oscillator lives
    under key ``hsi`` because the YAML drops the frequency tag).
    Prefix-match against the declared oscillator keys.
    """
    if not _is_pll_source(sysclk_source):
        raise StageExecutionError(
            f"st clock backend: not a PLL source: {sysclk_source!r}"
        )
    suffix = sysclk_source[len("pll_"):]
    # Direct match wins.
    if suffix in oscillators:
        return suffix
    # Prefix match: pick the longest oscillator key whose name is a
    # prefix of the suffix (so ``hsi16`` first tries ``hsi16`` then
    # ``hsi``, never accidentally matching ``h``).
    candidates = sorted(
        (k for k in oscillators if suffix.startswith(k)),
        key=len,
        reverse=True,
    )
    if candidates:
        return candidates[0]
    raise StageExecutionError(
        f"st clock backend: profile sysclk_source {sysclk_source!r} "
        f"does not match any declared oscillator (have: "
        f"{', '.join(sorted(oscillators))})"
    )


# ---------------------------------------------------------------------------
# The backend
# ---------------------------------------------------------------------------


class _StClockBackend:
    """Stateless lowering layer; instantiated once at import time."""

    def emit_profile(
        self,
        profile: ClockProfile,
        device: CanonicalDevice,
    ) -> tuple[ClockProgramStep, ...]:
        family = device.identity.family
        steps: list[ClockProgramStep] = []

        # Post-reset profiles are no-ops (the part already lands
        # there at reset).  We still emit the function body so
        # consumers can call it defensively, but it's empty.
        if profile.kind == "post-reset":
            steps.append(
                ClockProgramStep(
                    kind="barrier_dsb",
                    comment=f"post-reset profile {profile.id!r} is a no-op (chip already at this state)",
                )
            )
            return tuple(steps)

        # Soft fallback when the profile lacks hclk_hz.  The body
        # compiles (a barrier-only no-op) and the comment surfaces
        # the gap; promoting the YAML row to carry hclk_hz lights
        # up full lowering on the next regen.
        if profile.hclk_hz is None:
            return (
                ClockProgramStep(
                    kind="barrier_dsb",
                    comment=(
                        f"profile {profile.id!r} skipped — YAML missing hclk_hz; "
                        "see complete-clock-tree-runtime-init proposal §1.1"
                    ),
                ),
            )

        # 1. FLASH latency BEFORE raising HCLK.
        ws, enc = _flash_ws_for(family, profile.hclk_hz)
        steps.append(
            ClockProgramStep(
                kind="flash_latency",
                register_id="register:flash:acr",
                field_id="field:flash:acr:latency",
                value=enc,
                comment=f"FLASH wait states = {ws} for HCLK = {profile.hclk_hz} Hz",
            )
        )

        # 2. Power up the source oscillator if it's not the
        # post-reset HSI.  We model this as "set the corresponding
        # ON bit in RCC.CR" — the actual bit shift is family-specific
        # and lives in clock.oscillators[k].extra in the YAML; for
        # now we emit a comment-only marker and leave the bit
        # programming to a follow-up YAML enrichment.
        if _is_pll_source(profile.sysclk_source):
            src_osc = _pll_input_oscillator(profile.sysclk_source, device.clock.oscillators)
        else:
            # Direct sysclk source — use the same prefix-match logic
            # so naming variants like ``hsi16`` resolve to ``hsi``.
            if profile.sysclk_source in device.clock.oscillators:
                src_osc = profile.sysclk_source
            else:
                candidates = sorted(
                    (k for k in device.clock.oscillators if profile.sysclk_source.startswith(k)),
                    key=len, reverse=True,
                )
                if not candidates:
                    raise StageExecutionError(
                        f"st clock backend: profile {profile.id!r} sysclk_source "
                        f"{profile.sysclk_source!r} does not match any declared "
                        f"oscillator (have: {', '.join(sorted(device.clock.oscillators))})"
                    )
                src_osc = candidates[0]
        if device.clock.oscillators[src_osc].kind == "crystal-external":
            steps.append(
                ClockProgramStep(
                    kind="set_bits",
                    register_id="register:rcc:cr",
                    field_id=f"field:rcc:cr:{src_osc}on",
                    comment=f"power up external oscillator {src_osc!r}",
                )
            )
            steps.append(
                ClockProgramStep(
                    kind="spin_until",
                    register_id="register:rcc:cr",
                    field_id=f"field:rcc:cr:{src_osc}rdy",
                    expected=1,
                    comment=f"spin on {src_osc.upper()}RDY",
                )
            )

        # 3. PLL programming (only if the profile uses one).
        if _is_pll_source(profile.sysclk_source):
            if profile.pll_n is None:
                raise StageExecutionError(
                    f"st clock backend: PLL profile {profile.id!r} missing pll_n"
                )
            # PLLM / PLLN / PLLR live under RCC.PLLCFGR on G0/G4/F4/H7
            # (the offsets and exact field shifts differ — the IR
            # carries the encoding map under clock.domains[id=='pll_*'].select_register
            # for the input mux; the M/N/R coefficients are in their
            # own field on the same register and we lower them as
            # ``write_field`` ops keyed by the symbolic field-id.
            # The emitter resolves the symbolic id to a (mask, shift)
            # at write time via the device's templates).
            for coef in ("m", "n", "r", "p", "q"):
                value = getattr(profile, f"pll_{coef}")
                if value is None:
                    continue
                steps.append(
                    ClockProgramStep(
                        kind="write_field",
                        register_id="register:rcc:pllcfgr",
                        field_id=f"field:rcc:pllcfgr:pll{coef}",
                        value=value,
                        comment=f"PLL{coef.upper()} = {value}",
                    )
                )
            # PLL input source select.
            steps.append(
                ClockProgramStep(
                    kind="write_field",
                    register_id="register:rcc:pllcfgr",
                    field_id="field:rcc:pllcfgr:pllsrc",
                    value=_pllsrc_encoding(device, src_osc),
                    comment=f"PLL input = {src_osc!r}",
                )
            )
            # Power up + spin.
            steps.append(
                ClockProgramStep(
                    kind="set_bits",
                    register_id="register:rcc:cr",
                    field_id="field:rcc:cr:pllon",
                    comment="power up PLL",
                )
            )
            steps.append(
                ClockProgramStep(
                    kind="spin_until",
                    register_id="register:rcc:cr",
                    field_id="field:rcc:cr:pllrdy",
                    expected=1,
                    comment=f"spin on PLLRDY (timeout {_PLL_LOCK_TIMEOUT_US} us)",
                )
            )

        # 4. Switch SYSCLK source.
        steps.append(
            ClockProgramStep(
                kind="write_field",
                register_id="register:rcc:cfgr",
                field_id="field:rcc:cfgr:sw",
                value=_sw_encoding(device, profile.sysclk_source),
                comment=f"SYSCLK source = {profile.sysclk_source!r}",
            )
        )
        steps.append(
            ClockProgramStep(
                kind="spin_until",
                register_id="register:rcc:cfgr",
                field_id="field:rcc:cfgr:sws",
                expected=_sw_encoding(device, profile.sysclk_source),
                comment="spin until SWS confirms the SYSCLK switch",
            )
        )

        # 5. AHB / APB prescalers.  We only emit a write when the
        # profile narrows the prescaler from 1 to something else;
        # most ST profiles run AHB = SYSCLK = HCLK, APB1 = HCLK,
        # APB2 = HCLK, so this is rarely populated.  Future
        # enrichment of the IR's ``hpre`` / ``ppre1`` / ``ppre2``
        # fields lights up the rest.
        # (Intentional no-op for now — see proposal §4.4.)

        steps.append(
            ClockProgramStep(
                kind="barrier_dsb",
                comment=f"profile {profile.id!r} complete",
            )
        )
        steps.append(ClockProgramStep(kind="barrier_isb"))

        return tuple(steps)


def _sw_encoding(device: CanonicalDevice, sysclk_source: str) -> int:
    """Look up ``RCC.CFGR.SW`` encoding for the source.

    Reads ``device.clock.domains[id == 'sysclk_source'].select_register.encoding``
    when populated; otherwise falls back to the canonical
    STM32-wide map.
    """
    for d in device.clock.domains:
        if d.id == "sysclk_source" and d.select_register is not None:
            enc = d.select_register.encoding
            if sysclk_source in enc:
                return enc[sysclk_source]
    fallback = {"hsi16": 0, "hsisys": 0, "hsi": 0, "hse": 1, "pll_r_clk": 2,
                "pll_hsi16": 2, "pll_hse": 2, "pllclk": 2, "lse": 3, "lsi": 4}
    if sysclk_source in fallback:
        return fallback[sysclk_source]
    raise StageExecutionError(
        f"st clock backend: cannot encode SYSCLK source {sysclk_source!r}; "
        "neither clock.domains[sysclk_source].select_register nor the "
        "internal fallback map covers it"
    )


def _pllsrc_encoding(device: CanonicalDevice, source: str) -> int:
    """Look up ``RCC.PLLCFGR.PLLSRC`` encoding."""
    for d in device.clock.domains:
        if d.id == "pll_source" and d.select_register is not None:
            enc = d.select_register.encoding
            if source in enc:
                return enc[source]
    raise StageExecutionError(
        f"st clock backend: clock.domains[pll_source].select_register.encoding "
        f"missing entry for {source!r} (required for PLL profiles)"
    )


ST_CLOCK_BACKEND = _StClockBackend()
"""Singleton — the registry holds this exact instance."""

__all__ = ["ST_CLOCK_BACKEND"]
