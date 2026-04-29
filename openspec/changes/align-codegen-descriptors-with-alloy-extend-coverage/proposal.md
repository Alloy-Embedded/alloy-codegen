# Align Codegen Descriptors with alloy `extend-*-coverage` Series

## Why

The sibling `alloy` HAL repo has six in-flight OpenSpec changes
extending its descriptor-driven peripheral handles to consume
the FULL surface that alloy-codegen publishes:
`extend-uart-coverage`, `extend-adc-coverage`,
`extend-eth-coverage`, `extend-usb-coverage`,
`extend-qspi-coverage`, `extend-sdmmc-coverage` (plus the
umbrella `extend-device-contract-qspi-sdmmc-eth`).

Each expects rich `<Class>SemanticTraits<P>` headers already
published by alloy-codegen.  The audit shows that for some
classes the descriptor surface IS already rich (UART has 60+
register/field refs, USB device has the full DPRAM topology,
ADC has tier 2/3/4 metadata).  For others the codegen still
ships **stub specialisations** that block alloy's HAL series
from compiling on every admitted device — most notably **CAN**
(no `CanSemanticTraits<P>` populated for any device with a CAN
controller) and the **USB Host** path (distinct from USB
Device which IS populated on STM32F4 as OTG_FS_GLOBAL).

This change is the codegen-side counterpart to alloy's HAL
extension series: promote every stub semantic-trait class to
full for every admitted device whose silicon owns one, so
alloy's HAL drivers compile on every admitted target without
fallback paths.

## What Changes

The classes that need the codegen-side promotion are
identified by inspecting the alloy/ extend-* proposals
against the published alloy-devices artifact set.  The matrix
covers seven classes: CAN (every admitted device with a
controller), USB Host (distinct from USB Device which is
already full), Ethernet MAC, QSPI / OctoSPI, SDMMC, RTC, and
Watchdog.

For each class a new IR descriptor dataclass is added to
`ir/model.py` carrying the vendor-agnostic feature surface,
and the corresponding `_build_<class>_rows()` builder is
promoted from stub to full.  Per-device YAML migrations carry
the new descriptor data on stm32f405rg, stm32g0b1re,
atsame70q21b, mimxrt1062, and any other admitted device that
owns a peripheral in the affected class.

For each promotion, a regression test asserts the published
trait specialisation contains the fields alloy's
`extend-<class>-coverage` HAL driver expects.  The
`artifact-contract` capability spec is amended to require the
seven previously-stub classes to ship full specialisations on
every admitted device that owns the peripheral.

## Impact

Affected specs: MODIFIED `artifact-contract` requiring full
trait specialisations for the seven classes named above on
every admitted device that owns the peripheral.  Affected
code: 7 new descriptor dataclasses in `ir/model.py`; 7
builder promotions in the driver-semantics emitters; per-class
regression tests; per-device YAML migrations carrying the new
descriptor data.  Dependencies: ideally lands AFTER
`refactor-runtime-driver-semantics-per-class` (the per-class
module split makes the promotions safer); pairs 1:1 with
alloy's `extend-*-coverage` in-flight series.  Out of scope:
PIO (RP2040-only, already full); GPIO / UART / SPI / I2C / DMA
/ Timer / PWM / ADC / DAC (already full or full with minor
gaps the alloy/ extend-* series will surface if needed);
driver-class admission for chips not yet in DEVICE_REGISTRY
(separate alloy/ `expand-chip-coverage` work).
