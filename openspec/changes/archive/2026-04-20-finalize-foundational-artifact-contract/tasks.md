## 1. Device-Scoped Descriptor Completion

- [x] 1.1 Add `generated/devices/<device>/device_descriptor.hpp`
- [x] 1.2 Add `generated/devices/<device>/pins.hpp`
- [x] 1.3 Add `generated/devices/<device>/peripheral_instances.hpp`
- [x] 1.4 Add `generated/devices/<device>/capability_overlays.hpp`
- [x] 1.5 Extend emitted device metadata and/or descriptor references so those headers can be
      generated without JSON-side inference
- [x] 1.6 Extend the Alloy smoke consumer to compile against the new device-scoped descriptor
      contract
- [x] 1.7 Add golden tests for all new device-scoped emitted artifacts

### Gate K1: Device-scoped C++ consumption parity
- [x] K1.1 All foundational families emit the four required device-scoped descriptor headers
- [x] K1.2 Smoke-consumer coverage can compile using only the generated C++ contract plus Alloy
      runtime headers

## 2. Publication Consistency Hardening

- [x] 2.1 Make publish fail when `coverage.all_devices_publishable` is false
- [x] 2.2 Make publish fail when any targeted device has `publishable=false`
- [x] 2.3 Ensure publication-record, validation-summary, and coverage all agree on publishability
- [x] 2.4 Add regression tests for families that validate structurally but remain coverage-incomplete
- [x] 2.5 Add CI checks preventing partial-family publication into `alloy-devices`

### Gate K2: Publication consistency
- [x] K2.1 No family can be published while its coverage still says incomplete
- [x] K2.2 Publication outputs remain internally consistent across reports

## 3. Foundational Family Completion

- [x] 3.1 Audit `st/stm32g0` against the hardened contract and close remaining gaps
- [x] 3.2 Audit `st/stm32f4` against the hardened contract and close remaining gaps
- [x] 3.3 Audit `microchip/same70` against the hardened contract and close remaining gaps
- [x] 3.4 Audit `nxp/imxrt1060` against the hardened contract and close remaining gaps, including
      any descriptor domains that still report incomplete in coverage
- [x] 3.5 Add regression fixtures proving the foundational families remain complete under repeat
      publish cycles

### Gate K3: Foundational contract completeness
- [x] K3.1 `st/stm32g0` is contract-complete
- [x] K3.2 `st/stm32f4` is contract-complete
- [x] K3.3 `microchip/same70` is contract-complete
- [x] K3.4 `nxp/imxrt1060` is contract-complete

## 4. Artifact Contract Documentation Sync

- [x] 4.1 Update `docs/codegen-alloy-boundary.md` to the active emitted artifact set
- [x] 4.2 Update `docs/artifact-layout.md` to the active emitted artifact set
- [x] 4.3 Remove references to retired bootstrap-only artifact names from active docs
- [x] 4.4 Add regression checks that fail when active docs drift from the emitted contract

### Gate K4: Contract-document synchronization
- [x] K4.1 Active docs reference only current artifact families
- [x] K4.2 Active docs include all required artifact families

## 5. Vendor Admission Hardening

- [x] 5.1 Update `vendor-admission` so foundational families must be contract-complete on the
      hardened publication rules
- [x] 5.2 Make the admission gate treat partial foundational publication as an open blocker
- [x] 5.3 Update CI checks, if needed, to match the hardened admission semantics

## 6. Validation

- [x] 6.1 Run `openspec validate finalize-foundational-artifact-contract --strict`
- [x] 6.2 Add or update tests covering the new emitted headers and publication consistency rules
- [x] 6.3 Verify a full local publish for all foundational families under the hardened contract
