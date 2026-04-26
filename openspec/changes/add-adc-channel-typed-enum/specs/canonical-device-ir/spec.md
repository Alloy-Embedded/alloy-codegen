## ADDED Requirements

### Requirement: ADC Semantic Row SHALL Surface A Typed Channel Manifest

`AdcSemanticRow` MUST expose a derived channel manifest fusing the
ordinal channel range (`0..kChannelCount-1`) with the named internal
channels published in `internal_channels`. The manifest MUST be a
deterministic derivation — same input row produces the same
manifest — and MUST NOT introduce a new source-of-truth field. The
existing `internal_channels` tuple stays the authoritative input;
the manifest is the format the emitter consumes.

#### Scenario: Manifest fuses ordinal and named channels

- **WHEN** the IR builder constructs an `AdcSemanticRow` for STM32G0
  ADC1 with `channel_count = 19` and three internal channels
  (temperature_sensor at index 12, vrefint at 13, vbat at 14)
- **THEN** the row's channel manifest contains 19 ordinal entries
  (`CH0`..`CH18`) plus three named aliases (`TempSensor` at 12,
  `Vrefint` at 13, `VBat` at 14)
- **AND** the alias `TempSensor` carries the same channel index
  (12) as the ordinal `CH12`

#### Scenario: Manifest is deterministic and re-derivable

- **WHEN** the IR builder runs twice over the same descriptor
- **THEN** the produced manifests are byte-identical
- **AND** no manifest entry is silently reordered, even if the IR
  builder iterates the underlying maps in different orders
  internally

### Requirement: Internal-Channel Kind Names SHALL Be A Closed Set

The IR-to-emitter contract for ADC internal channels SHALL recognise
exactly the `kind` values
`temperature_sensor`, `vrefint`, `vbat`, `opamp_output`, and
`dac_output`. Any kind outside this set is preserved verbatim in
the IR (so future families can land their data without an emitter
change) but MUST NOT be treated as a known name during channel
enumeration.

#### Scenario: Future kind in the IR is preserved without breaking emit

- **WHEN** a future family's patch declares
  `AdcInternalChannel(kind="some_new_kind", channel_index=15)`
- **THEN** the IR carries the entry verbatim
- **AND** the channel manifest treats index 15 as ordinal `CH15`
  only — no named alias is invented from `some_new_kind`
- **AND** the IR validator surfaces a warning that the new kind
  needs an emitter table update before the named alias can be
  produced
