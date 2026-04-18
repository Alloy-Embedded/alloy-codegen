## Overview

This change is the "semantic and validation moat" phase of the generator.

The goal is not to add more legacy-style generated headers. The goal is to make the existing
runtime-only contract deeper, more explicit, and more trustworthy than vendor tooling.

The change has four pillars:

1. system-control fabric
2. formal capability model
3. provenance and explainability
4. validation moat

## 1. System-Control Fabric

### Canonical IR

Canonical IR gains explicit, typed facts for system-level control domains.

At minimum, the model must represent:

- `clock_roots`
- `clock_domains`
- `clock_dependencies`
- `reset_controls`
- `interrupt_slots`
- `interrupt_bindings`
- `power_domains`
- `system_sequences`

The intent is to stop treating startup/clock/reset/interrupt behavior as scattered side facts.
They become one cohesive device-scoped model.

### Runtime contract

The runtime publication must add device-scoped typed headers under
`generated/runtime/devices/<device>/` for the new system-control surfaces.

The exact file split may evolve, but the supported contract must include typed facts for:

- interrupt identifiers and vector bindings
- reset identifiers and reset sequencing dependencies
- power/enable domains where the vendor architecture exposes them
- clock dependency edges between roots, domains, and peripheral consumers
- reusable typed bring-up sequence metadata for foundational devices

The generated runtime contract must stay device-scoped and zero-reflection. This change does not
reintroduce string-based lookup or generic runtime tables.

## 2. Formal Capability Model

### Problem

Today many driver semantics are strong, but support questions still require reading low-level facts
or inferring behavior from schema ids.

That is not strong enough for a best-in-class multi-vendor generator.

### Capability contract

Each supported peripheral family must gain explicit capability descriptors.

The model must cover:

- peripheral-level capabilities
- channel-level capabilities
- DMA compatibility capabilities
- trigger/clock/reset prerequisites where relevant

Examples include:

- ADC external trigger support
- timer center-aligned support
- PWM complementary output support
- UART DMA RX/TX support
- SPI frame width or FIFO support
- interrupt and wakeup capabilities

Capabilities must be first-class emitted facts, not post-hoc heuristics in Alloy.

### Publication shape

Capabilities may live inside `driver_semantics/*` or in a dedicated runtime capability tree, but
the published C++ contract must make them:

- typed
- device-scoped
- compile-time queryable
- consistent across vendors

## 3. Provenance and Explainability

### Problem

Users and maintainers need to know why the generator emitted a fact, why a capability exists, and
why a route or binding was accepted or rejected.

Without this, scaling to more vendors becomes guesswork.

### Provenance model

Every emitted fact that matters for runtime behavior must be traceable to:

- upstream source
- patch
- inference rule
- merge rule

### Explainability outputs

Publication must emit machine-readable reports that answer:

- what source or patch produced this fact
- whether the fact was direct, patched, or inferred
- why a connector/route/DMA binding was accepted
- why a candidate was rejected or unsupported
- where coverage is partial or heuristic

These outputs are expected to be JSON/report artifacts, not a second public C++ contract.

## 4. Validation Moat

### Determinism

The publish pipeline must prove repeated publication produces the same materialized tree revision
for the same inputs.

### Foundational completeness

Foundational families must fail publication when the following are incomplete:

- system-control fabric coverage
- capability coverage for supported runtime peripherals
- provenance coverage for emitted runtime facts
- consumer verification coverage for new runtime contracts

### Consumer verification

Consumer verification must compile the system-control and capability contracts directly.

It must not rely on legacy reflection artifacts or handwritten assumptions about startup, reset,
clock, or interrupt structure.

## Scope and sequencing

This change is intentionally limited to the core moat.

It does not try to expand every peripheral class or build a user-facing configurator. Those belong
to follow-up work once the semantic foundation and validation moat are in place.

