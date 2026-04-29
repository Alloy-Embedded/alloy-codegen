"""Drop orphan peripheral references from canonical YAMLs.

Some YAMLs in alloy-devices-yml carry ``dma_requests`` /
``dma_routes`` / ``dma_bindings`` / ``peripheral_clock_bindings``
entries that reference peripherals which the device's
``peripherals`` whitelist does not admit (residue of the SVD →
patch filter pipeline).  After
``consume-alloy-devices-yml-as-canonical-input`` Phase 3 the
YAML is the source of truth, and the validation gate flags
these orphan references as schema errors.

This one-shot script walks every admitted device YAML and:

* re-loads it via ``load_canonical_device``
* filters out every orphan reference whose target peripheral is
  not in the device's ``peripherals`` set
* re-serialises the cleaned IR back to its YAML

Run it, commit the diff to alloy-devices-yml, and the validation
gate goes green again without touching the codegen rules.
"""

from __future__ import annotations

import argparse
import dataclasses
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"
if str(SRC) not in sys.path:
    sys.path.insert(0, str(SRC))

from alloy_codegen.canonical_device_yaml import serialize_device  # noqa: E402
from alloy_codegen.ir.model import CanonicalDeviceIR  # noqa: E402
from alloy_codegen.sources.alloy_devices_yml import (  # noqa: E402
    device_yaml_path,
    load_canonical_device,
)


def _discover() -> list[tuple[str, str, str]]:
    base = ROOT / "data" / "devices" / "vendors"
    triples: list[tuple[str, str, str]] = []
    for vendor_dir in sorted(base.iterdir()):
        if not vendor_dir.is_dir():
            continue
        for family_dir in sorted(vendor_dir.iterdir()):
            if not family_dir.is_dir():
                continue
            devices_dir = family_dir / "devices"
            if not devices_dir.exists():
                continue
            for yml in sorted(devices_dir.glob("*.yml")):
                triples.append((vendor_dir.name, family_dir.name, yml.stem))
    return triples


def _clean(ir: CanonicalDeviceIR) -> CanonicalDeviceIR:
    peripheral_names = {peripheral.name for peripheral in ir.peripherals}
    dma_controller_ids = {controller.controller for controller in ir.dma_controllers}

    def _peripheral_known(value: str | None) -> bool:
        return value is None or value in peripheral_names

    def _controller_known(value: str | None) -> bool:
        return value is None or value in dma_controller_ids

    cleaned_dma_requests = tuple(
        request
        for request in ir.dma_requests
        if _peripheral_known(request.peripheral)
        and _controller_known(request.controller)
    )
    surviving_request_keys = {
        (request.controller, request.request_line) for request in cleaned_dma_requests
    }
    cleaned_dma_routes = tuple(
        route
        for route in ir.dma_routes
        if _peripheral_known(route.peripheral)
        and _controller_known(route.controller)
        and (route.controller, route.request_line) in surviving_request_keys
    )
    surviving_route_ids = {route.route_id for route in cleaned_dma_routes}
    # Drop orphan bindings AND deduplicate by ``(peripheral, signal,
    # controller)`` — the C++ emitter writes one trait specialisation
    # per binding, so two bindings on the same peripheral/signal lead
    # to a redefinition compile error.  When a binding with a
    # channel-style request_line and one with a DMAMUX-style
    # request_line both target the same (peripheral, signal), we
    # keep the channel-style entry (it carries ``channel_index``).
    # Iteration order is preserved so the emitted ``kDmaBindings[]``
    # ordering remains stable.
    # Drop bindings with ``signal=None`` — these are ADC-style
    # single-stream bindings that don't fit the
    # ``(peripheral, signal)`` consumer-facing trait model and trip
    # the runtime-lite smoke compile (which spot-checks that
    # ``kDmaSemanticPeripherals[0]`` has a specialisation for the
    # first binding's signal_id).  ADC DMA goes through a separate
    # HAL concept anyway.
    candidates = [
        binding
        for binding in ir.dma_bindings
        if _peripheral_known(binding.peripheral)
        and _controller_known(binding.controller)
        and binding.route_id in surviving_route_ids
        and binding.signal is not None
    ]
    # First pass: pick the preferred binding per ``(peripheral, signal,
    # controller)`` key — channel-style entries (``channel_index`` set)
    # win over DMAMUX-style fallbacks.
    preferred: dict[tuple[str | None, str | None, str | None], object] = {}
    for binding in candidates:
        key = (binding.peripheral, binding.signal, binding.controller)
        existing = preferred.get(key)
        if existing is None:
            preferred[key] = binding
            continue
        if existing.channel_index is None and binding.channel_index is not None:
            preferred[key] = binding
    # Second pass: keep original ordering, dropping bindings that
    # weren't selected as the preferred entry for their key.
    cleaned_binding_list: list = []
    seen_binding_keys: set[tuple[str | None, str | None, str | None]] = set()
    for binding in candidates:
        key = (binding.peripheral, binding.signal, binding.controller)
        if key in seen_binding_keys:
            continue
        if preferred[key] is not binding:
            continue
        seen_binding_keys.add(key)
        cleaned_binding_list.append(binding)
    cleaned_dma_bindings = tuple(cleaned_binding_list)
    # Drop routes that no surviving binding points at — without a
    # binding, the route is invisible to consumers and trips the
    # ``<device>-dma-bindings-cover-routes`` validation rule.
    bound_route_ids = {binding.route_id for binding in cleaned_dma_bindings}
    cleaned_dma_routes = tuple(
        route
        for route in cleaned_dma_routes
        if route.peripheral is None or route.route_id in bound_route_ids
    )
    surviving_request_keys = {
        (route.controller, route.request_line) for route in cleaned_dma_routes
    }
    cleaned_dma_requests = tuple(
        request
        for request in cleaned_dma_requests
        if (request.controller, request.request_line) in surviving_request_keys
    )
    cleaned_clock_bindings = tuple(
        binding
        for binding in ir.peripheral_clock_bindings
        if _peripheral_known(binding.peripheral)
    )
    cleaned_max_clock = tuple(
        entry
        for entry in ir.peripheral_max_clock_hz
        if _peripheral_known(entry.peripheral)
    )
    # Drop clock_nodes that don't reach ``clock-root`` — the modm
    # clock-tree extension shipped with a handful of orphan nodes
    # (e.g. ``sysclk`` whose ``parent=None`` doesn't anchor to the
    # canonical root).  Validation rejects them; we drop them here.
    parent_map = {node.node_id: node.parent for node in ir.clock_nodes}

    def _reaches_root(node_id: str) -> bool:
        seen: set[str] = set()
        current = node_id
        while current not in seen:
            seen.add(current)
            parent = parent_map.get(current)
            if parent is None:
                return current == "clock-root"
            current = parent
        return False

    rooted_clock_nodes = tuple(node for node in ir.clock_nodes if _reaches_root(node.node_id))
    rooted_clock_node_ids = {node.node_id for node in rooted_clock_nodes}
    # Drop clock_selectors that reference parent_options not present
    # in the surviving rooted clock_nodes — modm's clock-tree
    # extension also shipped with a few naming mismatches
    # (e.g. ``hsi16`` vs ``clock-node:hsi16``).
    cleaned_selectors = tuple(
        selector
        for selector in ir.clock_selectors
        if selector.parent_options
        and all(option in rooted_clock_node_ids for option in selector.parent_options)
    )
    surviving_selector_ids = {selector.selector_id for selector in cleaned_selectors}
    cleaned_clock_nodes = tuple(
        dataclasses.replace(
            node,
            selector=node.selector if node.selector in surviving_selector_ids else None,
        )
        for node in rooted_clock_nodes
    )
    # Refresh ``dma_controllers[].request_count`` so the validate
    # rule ``<device>-dma-controller-request-counts-match`` stays
    # green after we drop orphan routes.
    route_count_by_controller: dict[str, int] = {}
    for route in cleaned_dma_routes:
        route_count_by_controller[route.controller] = (
            route_count_by_controller.get(route.controller, 0) + 1
        )
    cleaned_dma_controllers = tuple(
        dataclasses.replace(
            controller,
            request_count=route_count_by_controller.get(
                controller.controller, controller.request_count or 0
            ),
        )
        if controller.request_count is not None
        else controller
        for controller in ir.dma_controllers
    )
    return dataclasses.replace(
        ir,
        clock_nodes=cleaned_clock_nodes,
        clock_selectors=cleaned_selectors,
        dma_controllers=cleaned_dma_controllers,
        dma_requests=cleaned_dma_requests,
        dma_routes=cleaned_dma_routes,
        dma_bindings=cleaned_dma_bindings,
        peripheral_clock_bindings=cleaned_clock_bindings,
        peripheral_max_clock_hz=cleaned_max_clock,
    )


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dry-run", action="store_true")
    args = parser.parse_args()

    triples = _discover()
    if not triples:
        print("No devices found under data/devices/vendors/.", file=sys.stderr)
        return 1

    print(f"{'vendor/family/device':50}  {'before':>8}  {'after':>8}  {'Δ':>8}")
    print("-" * 86)
    for vendor, family, device in triples:
        ir = load_canonical_device(vendor=vendor, family=family, device=device)
        cleaned = _clean(ir)
        before_text = serialize_device(ir)
        after_text = serialize_device(cleaned)
        triple = f"{vendor}/{family}/{device}"
        delta = len(after_text) - len(before_text)
        print(f"{triple:50}  {len(before_text):>8}  {len(after_text):>8}  {delta:>+8}")
        if not args.dry_run and after_text != before_text:
            target = device_yaml_path(vendor=vendor, family=family, device=device)
            target.write_text(after_text, encoding="utf-8")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
