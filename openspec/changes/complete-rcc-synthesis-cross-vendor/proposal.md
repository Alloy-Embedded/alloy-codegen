# Complete RCC Synthesis Across Every Admitted Vendor

## Why

Tranches 1 + 2 of the v2.1 RCC synthesis (commits `9aef08f` …
`7a392cd`) wired ``_build_rcc_lookup`` into the synthesiser so the
emitted ``peripheral_traits.h`` carries ``kBus`` / ``kRccEnable`` /
``kRccReset`` / ``kKernelClockMux`` for every peripheral on:

* every STM32 family (F0/F1/F3/F4/G0/G4/H7) — including grouped
  H7 muxes (``d2ccip1r.spi123src`` → spi1/spi2/spi3) and the F4
  ``dckcfgr.sai*src`` muxes,
* RaspberryPi RP2040 (``resets`` + ``clocks`` templates),
* Microchip SAMD21 (``pm``) / SAMD51 / SAML21 / SAML22 (``mclk``)
  and SAME70 / SAMV71 (``pmc`` PID-indexed via IRQ map),
* NXP iMXRT 1060 — *named* CCM kernel-clock muxes only.

That leaves three known gaps the alloy HAL still trips on, plus
two vendors whose silicon has no per-peripheral clock gating at
all and need an explicit "this is by design" marker so HAL
drivers can dispatch correctly:

1. **Espressif ESP32 / C3 / S3** — partial inline ``rcc:`` blocks
   cover only 4–6 of ~37–46 peripherals; the rest live in the
   ``dport`` / ``system`` / ``pcr`` templates with three different
   field-naming conventions per chip and no synthesiser branch
   matches them today.

2. **NXP iMXRT CCGR table** — 88 of 111 peripherals on
   mimxrt1062 have no inline rcc and no synthesised gate because
   the CCGR clock-gates are *index*-based (``ccgr0.cg5`` means
   "the peripheral the reference manual table maps to that bit").
   ``_build_rcc_lookup`` has no PID→peripheral table for this
   family.

3. **Microchip SAMD21 / SAML21 GCLK kernel-clock muxes** — the SAM
   peripheral kernel clock comes from ``gclk.pchctrl<n>.gen``
   where ``<n>`` is a per-chip index from the ATDF (similar to
   the SAME70 PID story, but the index lives on PCHCTRL not
   IRQ).  Today ``kKernelClockMux`` is empty for every
   peripheral on these families.

4. **Microchip AVR-Dx** — peripherals on this family have no
   per-peripheral clock gate (``CLKCTRL`` is global, not
   peripheral-scoped).  Today ``rcc_map`` is empty, which is
   correct, but the alloy HAL has no way to tell "this vendor
   doesn't gate per-peripheral" from "this vendor's gate
   synthesis is incomplete".

5. **Nordic NRF52** — same situation as AVR-Dx (NRF52 peripherals
   are always-clocked when accessed via APB).  Needs the same
   marker.

Without these, alloy's HAL drivers either fall back to manual
register pokes (defeating the codegen contract) or refuse to
compile because the ``RccTraits<P>`` specialisation is missing on
half the admitted devices.

## What Changes

Five vendor-specific synthesiser branches added to
``alloy_codegen/ir/synthesised/builder.py``:

* ``_synthesise_esp32_rcc`` — three sub-handlers, one per Espressif
  generation:
  * **ESP32 (original)**: ``dport.perip_clk_en.<peri>_clk_en`` /
    ``dport.perip_rst_en.<peri>_rst_en``.
  * **ESP32-C3 / S3**: ``system.perip_clk_en{0,1}.<peri>_clk_en``
    / ``system.perip_rst_en{0,1}.<peri>_rst_en``, plus the
    ``cpu_peri_clk_en.clk_en_<peri>`` / ``cpu_peri_rst_en.rst_en_<peri>``
    suffix-prefix-flipped variant for the CPU-side peripherals.
  * **ESP32-C3 / S3 (PCR-self-contained)**: ``pcr.<peri>_conf_reg.<peri>_clk_en``
    / ``pcr.<peri>_conf_reg.<peri>_rst_en`` for the small set of
    peripherals that own their gate in their own register block.

  Each handler emits ``kBus = "DPORT"`` / ``"SYSTEM"`` / ``"PCR"``
  so the alloy HAL can dispatch on bus tag.  Field-name
  normalisation is per-chip (e.g. ``i2c0_ext0_clk_en`` →
  peripheral ``i2c0``, dropping the ``_ext0`` legacy suffix).

* ``_synthesise_imxrt_ccgr`` — hand-curated PID→peripheral table
  for iMXRT 1060 family, sourced from RM table 14-5 ("Clock Gating
  Register Bits Mapping").  Lives in
  ``alloy_codegen/ir/vendor_tables/nxp_imxrt_ccgr.py`` so future
  iMXRT families (1170, 1180) can extend without touching the
  synthesiser.  Cross-link writes ``en = "ccm.ccgr<N>.cg<M>"`` and
  leaves rst empty (CCGR has no separate reset bit; iMXRT
  peripherals reset via SOFT_RESET sequences in their own register
  blocks).

* ``_synthesise_sam_gclk_pchctrl`` — extracts the GCLK kernel-clock
  index from ``gclk.pchctrl<N>.gen``.  Because ``<N>`` is
  chip-specific and the ATDF doesn't carry the peri→pchctrl-index
  map directly, populate from a hand-curated table per family
  (``alloy_codegen/ir/vendor_tables/microchip_samd21_gclk.py``,
  ``microchip_samd51_gclk.py``, ``microchip_saml21_gclk.py``).
  Cross-link writes ``extra["clock_sel"] = "gclk.pchctrl<N>.gen"``.

* ``_no_per_peripheral_gate_marker`` — new ``PeripheralRcc.extra``
  field ``"gate_model"`` (string enum:
  ``"always-on"``, ``"per-peri-en"``, ``"per-peri-en-rst"``,
  ``"index-based"``, ``"per-peri-pcr"``).  AVR-Dx and NRF52 set
  ``"always-on"`` on every peripheral so the HAL can short-circuit.

* The trait emitter (``emit_v2_1/peripheral_traits.py``) gains one
  new constexpr line ``static constexpr GateModel kGateModel = …;``
  derived from ``extra["gate_model"]``, defaulting to
  ``"per-peri-en-rst"`` (the existing common case).  Adds a typed
  ``enum class GateModel`` to the alloy boundary so HAL drivers
  can ``constexpr if`` on it.

Also adds three new regression tests under
``tests/test_rcc_synthesis_per_vendor.py`` exercising one chip per
admitted vendor and asserting the per-peripheral coverage matrix
matches the documented expectation.

## Impact

**Affected capabilities**:

* `canonical-device-ir` — adds ``GateModel`` enum + per-instance
  ``extra["gate_model"]`` semantics requirement.
* `codegen-alloy-boundary` — adds the ``kGateModel`` constexpr
  emission requirement; bumps the alloy boundary to the new
  schema cleanly (no breaking change because consumers without
  ``constexpr if`` on the enum keep working with the default).

**Affected admitted devices**: every admitted ESP32 chip
(esp32 / esp32c3 / esp32s3), every iMXRT chip (mimxrt1062 /
mimxrt1064), every SAMD21 / SAML21 chip in the catalogue,
every AVR-Dx chip (avr32/64/128da*), and the lone nrf52840 entry.

**Goldens**: 100% of the admitted-device golden tree gets
regenerated under the new ``kGateModel`` line.  Goldens that
already populate ``kRccEnable``/``kRccReset``/``kKernelClockMux``
remain byte-stable; only ESP32, iMXRT (the 88 missing peripherals),
and SAMD21/SAML21 see a kRccEnable/kRccReset/kKernelClockMux
populate-from-empty change.

**Out of scope**: The existing STM32 / RP2040 / SAMD51 / SAML21 mclk
/ SAME70 / SAMV71 / iMXRT-named-CCM synthesis branches stay as-is.
The compile-gate-per-device work that proves the alloy HAL
*actually consumes* this trait surface lives in a sibling proposal
(``add-alloy-hal-compile-gate-per-device``).
