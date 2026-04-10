# Project Context

## Purpose
`alloy-codegen` is the source-of-truth toolchain for transforming messy vendor hardware
descriptions into a clean, validated, reproducible device model and then emitting versioned
artifacts for the Alloy ecosystem.

Its job is not only to generate C++ headers. It must own the full pipeline:
- acquiring raw source data
- applying reproducible corrections
- normalizing vendors into a canonical intermediate representation
- validating semantic consistency
- emitting machine-consumable metadata and generated code
- publishing artifacts to `alloy-devices`

The long-term goal is to make Alloy device support deterministic, auditable, and scalable
without embedding vendor quirks directly into handwritten HAL code or final codegen
templates.

## Tech Stack
- Python 3.12+ for CLI, pipeline orchestration, validation, and emitters
- Structured schemas for canonical data and manifests (JSON and/or YAML)
- Template-based code emission for generated C++ output
- GitHub Actions for CI validation and artifact publication

## Project Conventions

### Code Style
- Prefer explicit, typed Python over dynamic convenience code
- Keep vendor-specific logic isolated in adapters and normalizers
- Treat reproducibility as a product feature: same inputs plus same patches must produce
  byte-for-byte stable normalized data and artifacts unless versioned schema changes
- Avoid “magic fixups” inside emitters; corrections must live in patch or normalization
  layers with provenance

### Architecture Patterns
- Stage-separated pipeline: `fetch -> patch -> normalize -> validate -> emit -> publish`
- Canonical intermediate representation (IR) is the heart of the system
- Emitters are downstream consumers of IR; they do not own business rules
- Validation is multi-layered: schema validation, semantic validation, and artifact
  validation
- Vendor support grows by implementing adapters into the same IR, not by branching the
  whole architecture per vendor

### Testing Strategy
- Each pipeline stage must be testable in isolation
- Synthetic fixtures are preferred for deterministic unit tests
- Golden tests are required for normalized IR and emitted artifacts
- CI must block progression when a maturity gate fails
- New vendor/family support must ship with regression fixtures before expanding coverage

### Git Workflow
- Architectural or contract changes require OpenSpec proposals first
- Breaking changes to schemas, manifests, artifact layout, or publication flow require a
  change proposal
- Implementation follows approved phase gates; do not skip gates to add breadth prematurely

## Domain Context
The raw hardware ecosystem is inconsistent. SVDs are incomplete or wrong, vendor tool
exports encode valuable data in incompatible formats, and device support usually depends on
more than register blocks alone. The codegen system therefore must model:
- IP blocks and their versions
- devices and packages
- pins and alternate-function connectivity
- interrupts
- DMA request routing
- clock/reset enable data
- provenance for every normalized field

The system is inspired by ideas seen in projects like `modm-data`, `modm-devices`,
`stm32-data`, `chiptool`, and `svdtools`, but it must remain Alloy-owned in architecture,
schemas, and tooling.

## Important Constraints
- Do not depend on third-party generated outputs as the foundation of the product
- Keep licensing and provenance explicit for upstream data sources and derived artifacts
- Avoid baking vendor quirks into final emitted C++ templates
- A phase may only advance after its quality gate passes
- Multi-vendor expansion is forbidden until the single-family path is reproducible and
  semantically validated

## External Dependencies
- Upstream vendor/device descriptions such as SVD and other vendor-provided metadata
- Git for fetching sources and publishing artifacts
- GitHub Actions for CI execution and publication orchestration
