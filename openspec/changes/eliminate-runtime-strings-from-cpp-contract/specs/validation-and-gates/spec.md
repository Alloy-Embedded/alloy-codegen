## ADDED Requirements

### Requirement: Validation SHALL Ban Semantic Strings In Runtime C++ Headers

Validation SHALL fail when a runtime-consumed generated C++ header exposes a semantic string
field.

#### Scenario: Runtime header still exposes textual schema or signal information
- **WHEN** validation detects fields such as `const char* schema_id`, `const char* signal`,
  `const char* kind`, `const char* package_name`, or similar semantic labels in a runtime
  header
- **THEN** validation fails
- **AND** publication is blocked

### Requirement: Foundational Publication SHALL Require Zero-String Runtime Headers

Foundational families SHALL not publish unless every runtime-consumed generated C++ artifact
obeys the zero-string rule.

#### Scenario: Foundational family still leaks semantic labels into C++
- **WHEN** a foundational family emits a runtime-facing C++ artifact with semantic strings
- **THEN** publish fails for that family
- **AND** no artifact publication record is materialized
