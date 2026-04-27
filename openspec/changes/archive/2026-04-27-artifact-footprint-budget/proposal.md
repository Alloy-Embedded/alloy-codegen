# Per-Artifact Footprint Budget Gate

## Why

As the pipeline scales to 1000+ MCUs, some emitted runtime
artifacts will explode in size — iMXRT and ESP32-P4 already carry
hundreds of connection candidates each, and a future device with
thousands of pinmux entries could produce a multi-megabyte
`pin_validation.hpp` that bloats consumer firmware footprint or
DOSes the compiler.

A per-artifact-class byte budget caught at emission time keeps
output bounded.  When an artifact would breach its budget, the
build fails with a clear diagnostic so the team can either bump
the budget intentionally or split the artifact (per-peripheral
sub-headers, on-demand inclusion).

## What Changes

- New file `data/artifact_footprint_budget.toml` declares a
  byte budget per `(artifact_name_pattern, severity)` triple,
  e.g.:
    `pin_validation.hpp` → 64 KiB warn, 128 KiB fail
    `routes.hpp` → 96 KiB warn, 192 KiB fail
    `connectors.hpp` → 96 KiB warn, 192 KiB fail
- The publish stage measures every emitted artifact's UTF-8 byte
  size and compares it to the budget.
- `warn` exceedances surface in the validation report; `fail`
  exceedances abort the build.
- Per-device exemptions live in
  `data/artifact_footprint_overrides.toml` keyed by
  `(vendor, family, device, artifact_name)` — so a known-large
  device (e.g. an iMXRT with 800 candidates) can opt into a
  larger budget without relaxing the global default.
- The default budgets are set from the **largest currently
  admitted device's actual output**, plus a 50% headroom — i.e.
  no admitted device fails on day one, but anything more than 50%
  larger than today's worst case requires explicit review.

## Impact

Caps runtime-image and compile-time blast radius as device
catalog grows.  Pairs with the smoke-compile gate (catches
type-system regressions) and the existing no-string-literals
publication gate (caps per-symbol overhead) to make footprint
bounded by policy, not by hope.

## What this DOES NOT do

- Does not measure consumer-side firmware image size — that's
  the runtime-lite consumer-verification harness's domain.  This
  gate is on emitted source bytes only.
- Does not auto-split artifacts.  An exceedance triggers a build
  failure that requires human action (raise the budget, refactor
  the emitter, exempt the device).
