# Peripheral Trait Template Library

## Why

Every new peripheral type (UART, SPI, I2C, TIMER, PWM, …) requires
hand-writing Tier 2/3/4 data into every device patch, every time.
Recent OpenSpec archives show the cost: `add-i2c-tier-2-3-4-data`
edited 5 device patches, `add-uart-spi-tier-2-3-4-data` edited
~15.  N peripherals × M devices = O(N×M) hand-typing.

Most of that data is **identical across instances of the same IP
version**.  Every STM32 USART_v2 has the same parity-mode set,
the same baud divider semantics, the same FIFO depths.  The
patches duplicate this because the IR has no inheritance model:
each device repeats the trait values from scratch.

A small template library keyed by `(peripheral_class, ip_version)`
holds the Tier 2/3/4 defaults once.  Devices inherit them
automatically; patches only override when a specific instance
diverges.

## What Changes

- New directory `data/peripheral_traits/<peripheral_class>/<ip_version>.toml`
  carrying the canonical Tier 2/3/4 trait values for one IP
  version (e.g. `uart/usart_v2.toml`, `i2c/i2c_v2.toml`,
  `spi/spi_v3.toml`).
- Schema lives in `schemas/peripheral_traits/<class>.json` —
  one schema per peripheral class describing every Tier 2/3/4
  field.
- The normalize stage joins each peripheral instance to its
  matching template using `(peripheral.ip_name,
  peripheral.ip_version)` and applies template defaults *before*
  device-patch overrides.
- Device patches drop any Tier 2/3/4 field that matches the
  template (validated by the `invert-patch-as-diff` gate).
- A `scripts/extract_peripheral_template.py` tool seeds the
  initial templates by extracting the most common values across
  every admitted device for each `(class, ip_version)` — so the
  initial library reflects what's already shipped.
- Templates are versioned: `usart_v2.toml` carries a
  `template_revision` field that bumps when defaults change, so
  device patches can pin against a specific revision.

## Impact

Adding peripheral N+1 to family M+1 stops being O(N×M) work.  The
template carries the bulk of each `(class, ip_version)`'s Tier
2/3/4 surface; device patches only encode the genuinely
device-specific overrides (instance count, IRQ vectors, DMA
channels).  Pairs naturally with `invert-patch-as-diff` — both
exist to take redundancy out of patches.

## What this DOES NOT do

- Does not change the peripheral trait emitter contracts (they
  still emit one trait header per peripheral class).  The change
  is upstream of emission, in how the IR is populated.
- Does not eliminate ip-version-specific patches — when a chip
  has a quirk that doesn't fit the template, the device patch
  still carries the override.
