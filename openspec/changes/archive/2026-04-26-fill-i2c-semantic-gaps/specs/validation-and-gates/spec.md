## ADDED Requirements

### Requirement: I2C-bearing families MUST pass the I2C semantic coverage gate

I2C-bearing admitted families MUST emit at least one populated `I2cPeripheralTraits` specialization. Every admitted MCU family that ships at least one I2C / TWI controller in its admitted device set is covered by this gate; the gate fails the build when a family has zero `kPresent = true` specializations on its emitted `driver_semantics/i2c.hpp`.

The gate is rolled out per-family alongside the implementation phase
that populates that family.

#### Scenario: I2C coverage gate accepts a populated family

- **WHEN** a family that has been wired through the I2C-semantic
  emitter emits its `i2c.hpp`
- **THEN** the file contains at least one specialization where
  `kPresent = true`
- **AND** the coverage gate passes for that family

#### Scenario: I2C coverage gate ignores devices without I2C hardware

- **WHEN** an admitted family has no I2C / TWI controller on any
  device in its registered device list
- **THEN** the I2C coverage gate is treated as N/A for that family
  (it neither passes nor fails — the assertion does not run)
