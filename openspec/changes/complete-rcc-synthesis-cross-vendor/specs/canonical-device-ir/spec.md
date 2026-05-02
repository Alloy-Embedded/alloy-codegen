## ADDED Requirements

### Requirement: Canonical IR SHALL carry a per-peripheral `GateModel` enum

Every peripheral instance in ``alloy_codegen.ir.synthesised.SynthesisedDevice.per_rcc_map`` SHALL carry a typed ``GateModel`` enumerator describing how the silicon gates its clock / reset, drawn from a closed set of five values:

* ``always_on`` — the silicon has no per-peripheral clock gate
  (Microchip AVR-Dx, Nordic NRF52); the peripheral is clocked
  whenever the bus is alive.
* ``per_peri_en`` — the gate is a single bit in a centralised
  clock-enable register; the same bit also serves as the reset
  release (RP2040, Microchip SAM ``mclk``/``pm``, Microchip SAM
  ``pmc`` PID-indexed).
* ``per_peri_en_rst`` — separate enable and reset bits in
  centralised registers (every STM32 family, Microchip SAM
  with explicit ``rstc`` path).
* ``index_based`` — the gate bit is identified by a numeric
  index (PID, CCGR.CGm, etc.) rather than a peripheral-named
  field; HAL drivers MUST consult the codegen-emitted
  ``kRccEnable`` / ``kRccReset`` paths verbatim and not parse
  peripheral names from them (NXP iMXRT CCGR).
* ``per_peri_pcr`` — the gate lives inside the peripheral's own
  register block (a per-peripheral configuration register), not
  a centralised clock-enable register (ESP32-C3/S3 PCR fast-path
  peripherals).

The gate model is determined by the synthesiser
(``alloy_codegen.ir.synthesised.builder._build_rcc_lookup``) at
build time and SHALL NOT be set in the YAML directly — it is a
derived fact, not source data.

#### Scenario: AVR-Dx peripheral gets `always_on`

- **WHEN** the synthesiser builds an
  ``avr64da32`` device's ``per_rcc_map``
- **THEN** every peripheral instance entry SHALL carry
  ``extra["gate_model"] == "always_on"``
- **AND** ``en`` and ``rst`` SHALL both be ``None``
- **AND** the alloy HAL's ``RccTraits<P>`` specialisation SHALL
  emit a no-op for ``EnableClock(P)`` / ``ReleaseReset(P)``

#### Scenario: iMXRT peripheral gets `index_based`

- **WHEN** the synthesiser builds a ``mimxrt1062`` device's
  ``per_rcc_map`` and ``lpuart1`` resolves via the iMXRT CCGR
  table (``ccm.ccgr5.cg12``)
- **THEN** ``per_rcc_map["lpuart1"].extra["gate_model"]`` SHALL
  be ``"index_based"``
- **AND** ``per_rcc_map["lpuart1"].en`` SHALL be
  ``"ccm.ccgr5.cg12"``

### Requirement: Canonical IR SHALL synthesise RCC for every admitted vendor

Every ``(vendor, family, device)`` triple in ``alloy_codegen.bootstrap.DEVICE_REGISTRY`` SHALL produce a ``SynthesisedDevice`` whose ``per_rcc_map`` covers AT LEAST one of the following coverage targets:

* ``per_rcc_map[per_id].en`` is set for every peripheral in
  ``device.peripherals``, OR
* ``per_rcc_map[per_id].extra["gate_model"]`` is set for every
  peripheral in ``device.peripherals``.

Falling below either target SHALL trip the new
``test_rcc_synthesis_per_vendor.py`` gate at PR time.  The
specific synth strategy per family is delegated to
``_build_rcc_lookup``'s vendor branches:

| Vendor / family | Source |
|---|---|
| ST stm32f0/f1/f3/f4/g0/g4/h7 | ``rcc`` template (existing) |
| RaspberryPi rp2040 | ``resets`` + ``clocks`` templates (existing) |
| Microchip samd21 | ``pm`` template + samd21 GCLK PCHCTRL table |
| Microchip samd51 / saml21 / saml22 | ``mclk`` template + GCLK PCHCTRL table |
| Microchip same70 / samv71 | ``pmc`` template (PID via IRQ map) |
| Microchip avr-da | hard-coded ``always_on`` marker |
| NXP imxrt1060 | inline ``rcc:`` blocks + CCGR PID table + named CCM muxes |
| Espressif esp32 / esp32c3 / esp32s3 | inline ``rcc:`` blocks + DPORT/SYSTEM/PCR template synth |
| Nordic nrf52 | hard-coded ``always_on`` marker |

#### Scenario: ESP32-C3 peripheral coverage

- **WHEN** the synthesiser builds a ``esp32c3`` device
- **THEN** ``len(syn.per_rcc_map)`` SHALL be at least 30
  (previously 4 from inline-only)
- **AND** at least one peripheral SHALL come from each of the
  three sources: ``system.perip_clk_en0.<peri>_clk_en``,
  ``system.cpu_peri_clk_en.clk_en_<peri>``, and
  ``pcr.<peri>_conf_reg.<peri>_clk_en``

#### Scenario: iMXRT 1062 CCGR table coverage

- **WHEN** the synthesiser builds a ``mimxrt1062`` device
- **THEN** ``len(syn.per_rcc_map)`` SHALL be at least 80
  (previously 23 from inline-only)
- **AND** ``per_rcc_map["pwm1"].en`` SHALL be ``"ccm.ccgr4.cg8"``
  (CCGR-only peripheral; the synthesised entry is the source)
- **AND** ``per_rcc_map["lpuart1"].en`` SHALL match its inline
  ``rcc:`` block verbatim (``"CCM_CCGR5.CG12"``) — the inline
  block is preserved by the merge step; the CCGR-derived
  ``bus = "CCGR"`` and (Phase 4) ``gate_model = "index_based"``
  are layered on top
