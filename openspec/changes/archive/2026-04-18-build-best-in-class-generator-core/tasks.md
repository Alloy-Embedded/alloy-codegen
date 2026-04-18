## 1. Spec and IR

- [x] 1.1 Add the best-in-class core change and spec deltas
- [x] 1.2 Extend canonical IR with typed system-control fabric facts
- [x] 1.3 Extend canonical IR with formal capability descriptors
- [x] 1.4 Extend canonical IR with provenance/explainability metadata

## 2. System-Control Fabric

- [x] 2.1 Publish typed interrupt runtime facts for foundational devices
- [x] 2.2 Publish typed reset-control runtime facts for foundational devices
- [x] 2.3 Publish typed power-domain or enable-domain runtime facts where applicable
- [x] 2.4 Publish typed clock dependency edges beyond simple system clock profiles
- [x] 2.5 Publish typed system sequence metadata for foundational bring-up

## 3. Capability Contract

- [x] 3.1 Define the formal runtime capability taxonomy
- [x] 3.2 Emit foundational capability facts for existing runtime-supported peripherals
- [x] 3.3 Publish DMA compatibility capabilities for runtime-supported peripherals
- [x] 3.4 Fail foundational publication when runtime-supported peripherals lack capability coverage

## 4. Provenance and Explainability

- [x] 4.1 Emit provenance reports for runtime-critical generated facts
- [x] 4.2 Emit explainability reports for route, binding, and capability decisions
- [x] 4.3 Surface unsupported or heuristic coverage explicitly in publication reports

## 5. Validation Moat

- [x] 5.1 Add deterministic double-publish checks for foundational families
- [x] 5.2 Expand consumer verification to compile new system-control runtime contracts
- [x] 5.3 Expand consumer verification to compile capability contracts
- [x] 5.4 Fail publish when foundational provenance/explainability coverage is incomplete
- [x] 5.5 Update CI integration to treat runtime-only semantic completeness as release-blocking

## 6. Docs and Fixtures

- [x] 6.1 Update artifact layout and boundary docs
- [x] 6.2 Regenerate foundational fixtures affected by the new runtime contracts
- [x] 6.3 Validate with `python3 -m ruff check src tests`
- [x] 6.4 Validate with `python3 -m pytest tests -q`
- [x] 6.5 Validate with `openspec validate build-best-in-class-generator-core --strict`
