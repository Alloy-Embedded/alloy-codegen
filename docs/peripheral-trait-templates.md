# Peripheral Trait Template Library

Added by the OpenSpec change `peripheral-trait-template-library`.

## What it is

A library of Tier 2/3/4 trait defaults keyed by
`(peripheral_class, ip_name, ip_version)`.  When an emitter
needs the parity-mode set or FIFO-trigger options for an STM32
USART_v2 instance, it looks them up once in the template — not
copied N times across N device patches.

```
schemas/peripheral_traits/<class>.json   # JSON Schemas
data/peripheral_traits/<class>/<file>.toml  # per-IP-version templates
src/alloy_codegen/peripheral_traits.py    # loader + merge helpers
scripts/extract_peripheral_template.py    # seed templates from existing patches
```

## How the merge order works

```
baseline ← template ← family-patch ← device-patch
```

* **baseline**: defaults that are universal (empty lists / None).
* **template**: the canonical IP-version-specific values.
* **family-patch**: family-wide overrides (rare).
* **device-patch**: per-instance quirks.

`peripheral_traits.merge_chain(*layers)` implements this.  Empty
lists / `None` leaves at any layer act as "no override" so callers
can omit a key without nulling earlier values.

## Template file shape

Every template is a TOML file with three required keys:

```toml
template_revision = 1
ip_name = "usart"
ip_version = "v2"

# … class-specific Tier 2/3/4 fields below …
parity_options = ["none", "even", "odd"]
data_bits_options = [7, 8, 9]
```

The `template_revision` integer **MUST bump** when any default
below it changes.  Per-peripheral provenance records the value as
`peripheral_traits/<class>/<ip_name>__<ip_version>@rev<N>` so a
reviewer can tell at a glance which template revision a device
pinned against.

## Seeding new templates

Run the extractor against the admitted patches tree:

```bash
python -m scripts.extract_peripheral_template \
    --class uart --ip-version v2 \
    --out data/peripheral_traits/uart/usart_v2.toml
```

Output is **most-common, not correct** — the extractor reports the
modal value across every admitted device's existing Tier 2/3/4
arrays.  A reviewer cross-checks against datasheets and fixes
outliers before committing.

The extractor is deterministic: re-running on an unchanged patch
tree produces byte-identical output.

## What this DOES NOT do (yet)

This change ships the **library + merge plumbing** but does **not**
flip every existing emitter to template-first reads.  The migration
is per peripheral class and lands in follow-up changes:

1. `migrate-uart-to-template-library` — flip UART emitters.
2. `migrate-spi-to-template-library` — flip SPI emitters.
3. … one per class.

Each migration:
1. Loads the template via `resolve_template(...)`.
2. Calls `template.merged_into(device_overrides)` to compute the
   effective trait values.
3. Drops the now-redundant fields from device patches (gated by
   the redundancy check from `invert-patch-as-diff`).

Because the merge order treats device-patch values as overrides on
top of template defaults, **every existing emitted artifact stays
byte-identical until a migration explicitly drops the redundant
fields**.

## Why this matters at scale

Every new peripheral instance + family combination is an O(N×M)
hand-write today (recent archived OpenSpec changes:
`add-i2c-tier-2-3-4-data` × 5 patches,
`add-uart-spi-tier-2-3-4-data` × 15 patches).  With this library,
N changes to **one** template file instead of M edits to M device
patches.  Cuts the per-peripheral Tier 2/3/4 work from O(N×M) to
O(N + the genuinely-different overrides).
