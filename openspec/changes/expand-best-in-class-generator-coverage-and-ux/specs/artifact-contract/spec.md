## ADDED Requirements

### Requirement: Runtime contract expands to the remaining high-value peripheral classes

The supported runtime contract MUST eventually cover the major peripheral classes required by
modern embedded products.

#### Scenario: New peripheral classes follow the runtime-only contract
- **WHEN** CAN, RTC, watchdog, USB, ETH, QSPI/OSPI, SDMMC, or advanced timer features are added
- **THEN** they are published through the typed runtime contract
- **AND** they do not rely on legacy reflection-oriented C++ artifacts

