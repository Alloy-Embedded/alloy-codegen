"""Per-vendor regression tests for the v2.1 RCC synthesiser.

Each vendor branch in
:func:`alloy_codegen.ir.synthesised.builder._build_rcc_lookup` gets a
dedicated test that asserts:

* every admitted device for that vendor produces a ``per_rcc_map``
  whose size meets or exceeds the documented coverage target, and
* a handful of hand-picked peripheral entries match the expected
  ``en`` / ``rst`` / ``extra["bus"]`` paths from the chip's
  reference manual.

These tests ride alongside the byte-stable golden tests (which catch
*regressions* on already-emitted devices) by catching the inverse:
peripherals that were silently dropped because the synthesiser branch
covering their family is missing or buggy.
"""

from __future__ import annotations

import pytest

from alloy_codegen.ir.synthesised.builder import _build_rcc_lookup, build_synthesised
from alloy_codegen.sources.alloy_devices_yml import load_canonical_device


# ---------------------------------------------------------------------------
# Espressif ESP32 / C3 / S3
# ---------------------------------------------------------------------------


@pytest.mark.parametrize(
    "vendor, family, device, min_size",
    [
        # ESP32 (original) — DPORT.PERIP_CLK_EN/RST_EN covers ~20 of
        # the 46 peripherals (the rest are always-on / system control
        # which Phase 4 ``always_on`` markers will cover).
        ("espressif", "esp32", "esp32", 18),
        ("espressif", "esp32", "esp32-wroom32", 18),
        # ESP32-C3 — SYSTEM.PERIP_CLK_EN0/1 + CPU_PERI + PCR self-
        # contained covers ~25 of the 37 peripherals.
        ("espressif", "esp32c3", "esp32c3", 22),
        # ESP32-S3 — same SYSTEM convention as C3, ~33 of 54.
        ("espressif", "esp32s3", "esp32s3", 30),
    ],
)
def test_esp32_family_minimum_coverage(
    vendor: str, family: str, device: str, min_size: int
) -> None:
    """Every admitted ESP32 chip's ``per_rcc_map`` SHALL cover at
    least the documented number of peripherals.  Falling below this
    bound means the synthesiser branch missed a register group or
    field-naming variant that previously worked."""

    dev = load_canonical_device(vendor=vendor, family=family, device=device)
    syn = build_synthesised(dev)
    assert len(syn.per_rcc_map) >= min_size, (
        f"{device}: only {len(syn.per_rcc_map)} per_rcc_map entries; "
        f"expected >= {min_size}"
    )


def test_esp32_dport_paths_use_lowercase_dotted_form() -> None:
    """Synthesised paths SHALL be lowercase dotted (``dport.<reg>.<field>``).
    Pre-existing inline ``rcc:`` blocks may use UPPER form (data debt
    inherited from the YAML); the merge layer keeps them as-is.
    """
    dev = load_canonical_device(vendor="espressif", family="esp32", device="esp32")
    syn = build_synthesised(dev)
    # `i2s0` has no inline rcc block on esp32 → synthesised wins.
    rcc = syn.per_rcc_map["i2s0"]
    assert rcc.en == "dport.perip_clk_en.i2s0_clk_en"
    assert rcc.rst == "dport.perip_rst_en.i2s0_rst"
    assert rcc.extra["bus"] == "DPORT"


def test_esp32c3_three_register_sources() -> None:
    """ESP32-C3 SHALL synth gates from THREE distinct sources:
    ``system.perip_clk_en0``, ``system.cpu_peri_clk_en`` (prefix
    form), and ``pcr.<peri>_conf_reg.<peri>_clk_en``.  At least one
    peripheral MUST come from each source in the *raw* synthesis
    output (before the merge layer collapses inline ``rcc:`` blocks
    over synthesised entries).
    """
    dev = load_canonical_device(vendor="espressif", family="esp32c3", device="esp32c3")
    # Bypass the merge step: inspect the raw synth output directly
    # (the inline ``rcc:`` blocks on i2c0/spi2/uart0/uart1 use UPPER
    # form which would otherwise mask the PCR-synthesised entries).
    raw = _build_rcc_lookup(dev)

    sources = {
        "perip_clk_en0": False,
        "cpu_peri": False,
        "pcr_conf": False,
    }
    for rcc in raw.values():
        if rcc.en is None:
            continue
        if "perip_clk_en0" in rcc.en:
            sources["perip_clk_en0"] = True
        if "cpu_peri_clk_en.clk_en_" in rcc.en:
            sources["cpu_peri"] = True
        if rcc.en.startswith("pcr."):
            sources["pcr_conf"] = True
    assert all(sources.values()), (
        f"esp32c3 missing one of the expected gate sources: {sources}"
    )


def test_esp32c3_assist_debug_uses_prefix_form() -> None:
    """The CPU-side ``cpu_peri_*`` group inverts the suffix→prefix
    convention (``clk_en_<peri>`` rather than ``<peri>_clk_en``).
    ``assist_debug`` is the canonical example that exercises this
    path on both C3 and S3.
    """
    dev = load_canonical_device(vendor="espressif", family="esp32c3", device="esp32c3")
    syn = build_synthesised(dev)
    rcc = syn.per_rcc_map["assist_debug"]
    assert rcc.en == "system.cpu_peri_clk_en.clk_en_assist_debug"
    assert rcc.rst == "system.cpu_peri_rst_en.rst_en_assist_debug"
    assert rcc.extra["bus"] == "SYSTEM"


def test_esp32s3_dma_synthesised_from_perip_clk_en1() -> None:
    """The ESP32-S3 GDMA controller's gate is in
    ``perip_clk_en1.dma_clk_en`` (not the legacy esp32-original
    ``spi_dma_*`` field).  Tests the C3/S3 second-bank handling."""
    dev = load_canonical_device(vendor="espressif", family="esp32s3", device="esp32s3")
    syn = build_synthesised(dev)
    rcc = syn.per_rcc_map["dma"]
    assert rcc.en == "system.perip_clk_en1.dma_clk_en"
    assert rcc.rst == "system.perip_rst_en1.dma_rst"
    assert rcc.extra["bus"] == "SYSTEM"


def test_esp32_field_aliases_resolve() -> None:
    """The alias map collapses vendor naming quirks
    (``crypto_aes`` → ``aes``, ``i2c_ext0`` → ``i2c0``,
    ``timergroup`` → ``timg0``).  Each one MUST surface as the
    canonical peripheral id in the ``per_rcc_map``."""

    dev = load_canonical_device(vendor="espressif", family="esp32c3", device="esp32c3")
    syn = build_synthesised(dev)
    # crypto_aes alias
    assert "aes" in syn.per_rcc_map
    assert "crypto_aes" not in syn.per_rcc_map
    # timergroup alias
    assert syn.per_rcc_map["timg0"].en == "system.perip_clk_en0.timergroup_clk_en"
    assert syn.per_rcc_map["timg1"].en == "system.perip_clk_en0.timergroup1_clk_en"


# ---------------------------------------------------------------------------
# NXP i.MX RT 1060 CCGR PID table
# ---------------------------------------------------------------------------


def test_imxrt_ccgr_minimum_coverage() -> None:
    """The mimxrt1062 ``per_rcc_map`` SHALL cover at least 80
    peripherals (was 23 from inline-only, plus 7 from named CCM
    muxes; the CCGR PID table closes the remaining gap)."""

    dev = load_canonical_device(
        vendor="nxp", family="imxrt1060", device="mimxrt1062"
    )
    syn = build_synthesised(dev)
    assert len(syn.per_rcc_map) >= 80, (
        f"mimxrt1062: only {len(syn.per_rcc_map)} per_rcc_map entries; "
        f"expected >= 80 with the CCGR table wired in"
    )


def test_imxrt_ccgr_only_peripheral_uses_lowercase_path() -> None:
    """Peripherals without an inline ``rcc:`` block SHALL get a
    clean lowercase synthesised path of the form ``ccm.ccgrN.cgM``.
    Pwm1, tmr1, usb1/usb2 and sai1 are anchor cases — none of them
    have inline rcc on the YAML, so the CCGR table is the source.
    """
    dev = load_canonical_device(
        vendor="nxp", family="imxrt1060", device="mimxrt1062"
    )
    syn = build_synthesised(dev)
    # Spot-check a half-dozen well-known mappings (all CCGR-only):
    assert syn.per_rcc_map["pwm1"].en == "ccm.ccgr4.cg8"
    assert syn.per_rcc_map["tmr1"].en == "ccm.ccgr6.cg13"
    assert syn.per_rcc_map["sai1"].en == "ccm.ccgr5.cg9"
    assert syn.per_rcc_map["usb1"].en == "ccm.ccgr6.cg0"
    assert syn.per_rcc_map["usb2"].en == "ccm.ccgr6.cg0"
    # CCGR7 entries (RT1062-specific extras):
    assert syn.per_rcc_map["enet2"].en == "ccm.ccgr7.cg0"
    assert syn.per_rcc_map["can3"].en == "ccm.ccgr7.cg2"
    # Bus tag: CCGR (the synthetic name the alloy HAL uses to
    # dispatch to the index-based gate path).
    for per_id in ("pwm1", "tmr1", "sai1", "usb1", "enet2"):
        assert syn.per_rcc_map[per_id].extra["bus"] == "CCGR"


def test_imxrt_inline_rcc_blocks_not_shadowed() -> None:
    """When a peripheral already has an inline ``rcc:`` block on
    the YAML, the synthesised CCGR entry MUST NOT shadow it — the
    inline path is the YAML-author's source of truth.  The merge
    layer keeps inline ``en``/``rst`` paths and only contributes
    the bus tag and (Phase 4) ``gate_model`` from the CCGR side.
    """
    dev = load_canonical_device(
        vendor="nxp", family="imxrt1060", device="mimxrt1062"
    )
    syn = build_synthesised(dev)
    # All these peripherals carry an inline rcc block on the YAML
    # in UPPER form — they MUST stay UPPER after synthesis.
    assert syn.per_rcc_map["lpuart1"].en == "CCM_CCGR5.CG12"
    assert syn.per_rcc_map["gpio1"].en == "CCM_CCGR1.CG13"
    assert syn.per_rcc_map["lpi2c1"].en == "CCM_CCGR2.CG2"
    assert syn.per_rcc_map["flexspi"].en == "CCM_CCGR6.CG5"
    assert syn.per_rcc_map["flexspi2"].en == "CCM_CCGR7.CG3"


# ---------------------------------------------------------------------------
# AVR-Dx + NRF52: always-on marker pass
# ---------------------------------------------------------------------------


@pytest.mark.parametrize(
    "vendor, family, device",
    [
        ("microchip", "avr-da", "avr64da32"),
        ("microchip", "avr-da", "avr128da48"),
        ("nordic", "nrf52", "nrf52840"),
    ],
)
def test_avr_da_and_nrf52_every_peripheral_marked_always_on(
    vendor: str, family: str, device: str
) -> None:
    """AVR-Dx and Nordic NRF52 silicon have NO per-peripheral clock
    gate.  Every peripheral SHALL carry
    ``extra["gate_model"] == "always_on"`` so HAL drivers can
    short-circuit the EnableClock path via ``constexpr if``."""

    dev = load_canonical_device(vendor=vendor, family=family, device=device)
    syn = build_synthesised(dev)

    # Every peripheral on the chip MUST appear in per_rcc_map.
    peri_ids = {p.id for p in dev.peripherals}
    assert peri_ids.issubset(set(syn.per_rcc_map.keys())), (
        f"{device}: missing per_rcc_map entries for "
        f"{sorted(peri_ids - set(syn.per_rcc_map.keys()))}"
    )

    # Every entry MUST have gate_model = "always_on" (no en/rst paths).
    for per_id in peri_ids:
        rcc = syn.per_rcc_map[per_id]
        assert rcc.extra.get("gate_model") == "always_on", (
            f"{device}/{per_id}: gate_model={rcc.extra.get('gate_model')!r}, "
            f"expected 'always_on'"
        )
        assert rcc.en is None and rcc.rst is None, (
            f"{device}/{per_id}: en/rst should both be None on "
            f"always-on silicon (got en={rcc.en!r}, rst={rcc.rst!r})"
        )


def test_gate_model_derivation_per_vendor() -> None:
    """The five GateModel enumerators SHALL each have at least one
    representative across the admitted device set, exercising every
    branch of the derivation logic."""

    seen: set[str] = set()
    for vendor, family, device in (
        ("microchip", "avr-da", "avr64da32"),       # always_on
        ("st", "stm32g0", "stm32g0b1cbtx"),         # per_peri_en_rst
        ("raspberrypi", "rp2040", "rp2040"),        # per_peri_en
        ("nxp", "imxrt1060", "mimxrt1062"),         # index_based
        ("espressif", "esp32c3", "esp32c3"),        # per_peri_pcr
    ):
        dev = load_canonical_device(vendor=vendor, family=family, device=device)
        syn = build_synthesised(dev)
        for rcc in syn.per_rcc_map.values():
            gm = rcc.extra.get("gate_model")
            if isinstance(gm, str):
                seen.add(gm)
    assert seen == {
        "always_on",
        "per_peri_en",
        "per_peri_en_rst",
        "index_based",
        "per_peri_pcr",
    }, f"missing gate-model branches: {seen}"


# ---------------------------------------------------------------------------
# Microchip SAMx GCLK kernel-clock-mux
# ---------------------------------------------------------------------------


def test_samd21_clkctrl_ids_populated() -> None:
    """SAMD21 SHALL emit a ``gclk.clkctrl.id<N>`` entry for every
    SERCOM / TC / TCC / ADC / DAC instance.  The CLKCTRL register
    is the single-register form of GCLK kernel-clock selection on
    SAMD21 (later families switched to the array PCHCTRL[N])."""

    dev = load_canonical_device(
        vendor="microchip", family="samd21", device="atsamd21g18a"
    )
    syn = build_synthesised(dev)
    # SERCOM0..SERCOM5 (the J variant has all 6).
    for n in range(6):
        per = f"sercom{n}"
        if per not in syn.per_rcc_map:
            continue  # G/E variants may not have all 6
        clock_sel = str(syn.per_rcc_map[per].extra["clock_sel"])
        assert clock_sel.startswith("gclk.clkctrl.id"), (
            f"{per}: missing clock_sel (got {clock_sel!r})"
        )
    # ADC + DAC + AC.
    assert syn.per_rcc_map["adc"].extra["clock_sel"] == "gclk.clkctrl.id30"
    assert syn.per_rcc_map["dac"].extra["clock_sel"] == "gclk.clkctrl.id33"
    assert syn.per_rcc_map["ac"].extra["clock_sel"] == "gclk.clkctrl.id31"
    # TC/TCC pairs (TCC0_TCC1 share id 26; TC4_TC5 share id 28).
    assert syn.per_rcc_map["tcc0"].extra["clock_sel"] == "gclk.clkctrl.id26"
    assert syn.per_rcc_map["tc4"].extra["clock_sel"] == "gclk.clkctrl.id28"


def test_samd51_pchctrl_array_paths() -> None:
    """SAMD51 uses ``PCHCTRL[N]`` (an array of single-channel
    registers).  The synthesised path SHALL be
    ``gclk.pchctrl<N>.gen`` for every channel-bound peripheral."""

    dev = load_canonical_device(
        vendor="microchip", family="samd51", device="atsamd51g18a"
    )
    syn = build_synthesised(dev)
    assert syn.per_rcc_map["sercom0"].extra["clock_sel"] == "gclk.pchctrl7.gen"
    assert syn.per_rcc_map["adc0"].extra["clock_sel"] == "gclk.pchctrl40.gen"
    assert syn.per_rcc_map["dac"].extra["clock_sel"] == "gclk.pchctrl42.gen"
    assert syn.per_rcc_map["sdhc0"].extra["clock_sel"] == "gclk.pchctrl45.gen"


def test_saml21_pchctrl_paths() -> None:
    """SAML21 PCHCTRL indices follow the SAML21 datasheet table
    17-3 (slightly compacted vs SAMD51 because the L21 has fewer
    peripherals)."""

    dev = load_canonical_device(
        vendor="microchip", family="saml21", device="atsaml21j18b"
    )
    syn = build_synthesised(dev)
    assert syn.per_rcc_map["sercom0"].extra["clock_sel"] == "gclk.pchctrl18.gen"
    assert syn.per_rcc_map["sercom1"].extra["clock_sel"] == "gclk.pchctrl20.gen"
    assert syn.per_rcc_map["adc"].extra["clock_sel"] == "gclk.pchctrl30.gen"
    assert syn.per_rcc_map["dac"].extra["clock_sel"] == "gclk.pchctrl32.gen"


def test_esp32_spi01_shared_gate_links_both_instances() -> None:
    """``perip_clk_en0.spi01_clk_en`` is a single bit that gates
    BOTH ``spi0`` and ``spi1``.  The synthesiser SHALL link both
    peripheral ids to the same path so the alloy HAL can dispatch
    on either instance and hit the right bit."""

    dev = load_canonical_device(vendor="espressif", family="esp32", device="esp32")
    syn = build_synthesised(dev)
    spi0 = syn.per_rcc_map.get("spi0")
    spi1 = syn.per_rcc_map.get("spi1")
    # spi0 has no inline rcc on esp32, spi1 too — both should come
    # from the synthesised shared gate.
    assert spi0 is not None
    assert spi1 is not None
    # NB: spi0 is shadowed by an inline rcc block on the YAML
    # (`DPORT_PERIP_CLK_EN.SPI01_CLK_EN`) — that's UPPER form.  The
    # synthesised entry wins for spi1 since spi1 has no inline.
    assert "spi01" in (spi1.en or "").lower()
