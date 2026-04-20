# Configuration Layer

The runtime contract is typed, but users still need a concrete way to ask for a board or
peripheral setup.

`alloy-codegen` exposes that layer through a declarative JSON request plus three CLI entrypoints:

- `alloy-codegen config-schema`
- `alloy-codegen config-template --device <device>`
- `alloy-codegen config-diagnose --file <request.json>`
- `alloy-codegen config-recipe --file <request.json>`
- `alloy-codegen config-example --file <request.json>`

## Recommended Flow

1. Inspect the schema:

```sh
alloy-codegen config-schema --json
```

2. Generate a device-scoped template:

```sh
alloy-codegen config-template --device stm32g071rb --json
```

3. Fill the template with:

- `clock_profile`
- requested peripheral instances or classes
- requested signal-to-pin mappings
- requested DMA use
- requested recipe/example outputs

4. Diagnose the request before generating downstream recipes:

```sh
alloy-codegen config-diagnose --file request.json --json
```

5. Render the resolved recipe once diagnostics are clean:

```sh
alloy-codegen config-recipe --file request.json --json
```

6. Render example-ready outputs from the same request:

```sh
alloy-codegen config-example --file request.json --json
```

## Request Shape

The current request schema is `runtime-config-request-v1`.

Minimal example:

```json
{
  "schema_version": "runtime-config-request-v1",
  "device": "stm32g071rb",
  "clock_profile": "default-pll-64mhz",
  "requests": [
    {
      "kind": "peripheral",
      "peripheral_class": "uart",
      "peripheral": "USART1",
      "pins": {
        "tx": "PB6",
        "rx": "PB7"
      },
      "dma": {
        "rx": true,
        "tx": true
      }
    }
  ],
  "outputs": {
    "recipes": [],
    "examples": []
  }
}
```

## Diagnostic Guarantees

`config-diagnose` is expected to answer:

- whether the requested `clock_profile` exists
- whether the requested `peripheral_class` is runtime-supported
- whether the requested peripheral exists inside that class
- whether the requested pins realize valid route candidates
- whether multi-signal requests form a valid route group
- whether requested DMA directions are available on the resolved peripheral

When a request is invalid, diagnostics return concrete alternatives such as:

- valid peripheral instances for the class
- valid pins for a signal
- valid route groups and pin maps
- valid DMA-capable directions
- valid clock profiles

## Recipe Output

`config-recipe` returns the normalized, resolved recipe on top of the typed runtime contract.

The current recipe schema is `runtime-config-recipe-v1`.

That recipe is expected to carry:

- resolved peripheral instance names
- resolved route groups when multi-signal routes are involved
- resolved signal-to-pin maps
- resolved DMA directions
- the selected clock profile

This is the stable generator-side handoff for higher-level board recipes and example generation.

## Example Output

`config-example` emits user-facing example bundles from the resolved recipe.

The current example output is expected to carry:

- `runtime_headers` needed by the request
- a stable `example_id`
- resolved pins, route groups, DMA directions, and clock profile
- a compact snippet block that can seed board/example source files

## Scope Rules

- This layer is device-scoped. A request must target one device.
- The configuration layer sits on top of the same typed runtime contract published to `alloy`.
- Diagnostics must remain explainable; they should reuse emitted runtime facts instead of
  rebuilding a second handwritten model.
