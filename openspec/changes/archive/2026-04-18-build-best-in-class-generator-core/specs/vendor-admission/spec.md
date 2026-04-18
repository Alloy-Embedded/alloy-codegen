## ADDED Requirements

### Requirement: New vendor admission requires semantic and provenance readiness

Vendor/family admission MUST not be judged only by parser success or low-level artifact emission.

#### Scenario: Admission checks semantic readiness
- **WHEN** a new vendor or family is considered publishable
- **THEN** admission evaluates system-control coverage, capability coverage, and provenance quality
- **AND** the family is not considered foundational-ready if those remain heuristic or opaque

