## ADDED Requirements

### Requirement: Test goldens MUST be regeneratable through an opt-in flag

The test harness SHALL support an opt-in mode that rewrites
golden fixtures from the current pipeline output instead of
asserting equality.  The mode SHALL be activated either by
setting the `ALLOY_UPDATE_GOLDENS=1` environment variable or by
passing the `--update-goldens` flag to pytest.  When the flag is
**not** set (the default, including CI), every golden assertion
SHALL still fail the build on mismatch — the flag MUST NOT relax
the default contract.  When the flag IS set, the harness SHALL
refuse to run if `git status` reports dirty non-fixture files,
to prevent accidental source changes from being baked into
goldens.

#### Scenario: Default mode fails on golden mismatch

- **WHEN** `pytest` is run without the update flag
- **AND** an emitted artifact differs from its golden fixture
- **THEN** the test SHALL fail with the existing equality
  assertion message — behaviour unchanged from today

#### Scenario: Update mode rewrites goldens to match pipeline output

- **WHEN** `ALLOY_UPDATE_GOLDENS=1 pytest` is run
- **AND** the working tree has no dirty non-fixture files
- **THEN** every golden-mismatch assertion SHALL instead write
  the new content to the fixture path
- **AND** the resulting `git diff` SHALL be limited to
  `tests/fixtures/` paths so the change is reviewable

#### Scenario: Update mode aborts when source files are dirty

- **WHEN** `ALLOY_UPDATE_GOLDENS=1 pytest` is run
- **AND** `git status --porcelain` reports modified files outside
  `tests/fixtures/`
- **THEN** the harness SHALL abort with an error explaining that
  source changes must be committed first to prevent baking them
  into goldens silently
