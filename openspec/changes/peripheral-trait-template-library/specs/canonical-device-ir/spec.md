## ADDED Requirements

### Requirement: Tier 2/3/4 peripheral traits SHALL be inherited from a per-IP-version template library

The pipeline SHALL maintain a template library at
`data/peripheral_traits/<peripheral_class>/<ip_version>.toml`
describing the canonical Tier 2/3/4 trait values for each
`(peripheral_class, ip_version)` pair.  During normalization,
every peripheral instance SHALL be joined to its matching
template via `(peripheral.ip_name, peripheral.ip_version)` and
the template values SHALL be applied to the IR before device-patch
overrides — the merge order MUST be
`baseline ← template ← family-patch ← device-patch`.  Device
patches SHALL NOT carry Tier 2/3/4 fields whose values match the
template; redundant fields SHALL fail validation.

#### Scenario: Two STM32 instances on the same USART_v2 IP inherit identical defaults

- **WHEN** STM32G0 USART1 and STM32F4 USART2 are both
  `(ip_name=usart, ip_version=v2)`
- **THEN** both peripheral instances SHALL receive the same
  Tier 2/3/4 defaults from
  `data/peripheral_traits/uart/usart_v2.toml`
- **AND** the device patches SHALL NOT repeat those default
  values

#### Scenario: A device-specific quirk overrides the template

- **WHEN** a single peripheral instance diverges from its
  template (e.g. a stripped-down USART variant lacks parity-mode
  `even`)
- **THEN** the device patch SHALL carry only the divergent field
- **AND** the resolved IR SHALL reflect the device-patch override
  on top of the template's other defaults

#### Scenario: Templates are versioned

- **WHEN** a template file is updated (a Tier 2/3/4 default
  changes)
- **THEN** the file's `template_revision` field SHALL bump
- **AND** the bump SHALL be visible in the resolved IR's
  per-peripheral provenance so reviewers can tell which template
  revision a device pinned against
