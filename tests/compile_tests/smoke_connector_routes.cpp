// smoke_connector_routes.cpp
//
// Minimal compile smoke for the connector + route artifacts emitted by
// alloy-codegen for a single representative device (stm32g071rb).
//
// The pytest harness (test_compile_smoke.py) generates the artifact tree
// under a tmp directory and compiles this TU with:
//
//   clang++ -std=c++20 -ffreestanding -nostdlib -c -I <tmpdir> ...
//
// Note: peripheral_id.hpp is NOT included in the same TU because it
// defines its own ``PeripheralId`` (kUsart1-style, for the RCC/traits
// subsystem) which conflicts with the connector-system ``PeripheralId``
// (USART1-style) in connectors.hpp.  These are intentionally different
// types for different subsystems — include them in separate TUs.

#include "connectors.hpp"
#include "routes.hpp"

// Alias the device namespace to keep assertions concise.
namespace dev = alloy::st::stm32g0::stm32g071rb;

// ---------------------------------------------------------------------------
// PinId / PeripheralId / SignalId enums exist and carry the expected values.
// ---------------------------------------------------------------------------

static_assert(dev::PinId::PB6    != dev::PinId::none);
static_assert(dev::PinId::PA9    != dev::PinId::none);
static_assert(dev::PeripheralId::USART1 != dev::PeripheralId::none);
static_assert(dev::SignalId::signal_tx  != dev::SignalId::none);
static_assert(dev::RouteKindId::route_kind_alternate_function
              != dev::RouteKindId::none);
static_assert(dev::ConnectionGroupId::none == dev::ConnectionGroupId::none);

// ---------------------------------------------------------------------------
// ConnectorTraits — valid combo (PB6 / USART1 / signal_tx)
// ---------------------------------------------------------------------------

using ValidTrait = dev::ConnectorTraits<
    dev::PinId::PB6,
    dev::PeripheralId::USART1,
    dev::SignalId::signal_tx>;

static_assert(ValidTrait::kPresent);
static_assert(ValidTrait::kPinId       == dev::PinId::PB6);
static_assert(ValidTrait::kPeripheralId == dev::PeripheralId::USART1);
static_assert(ValidTrait::kSignalId    == dev::SignalId::signal_tx);
static_assert(ValidTrait::kRouteKindId
              == dev::RouteKindId::route_kind_alternate_function);
static_assert(ValidTrait::kGroupId     == dev::ConnectionGroupId::none);

// ---------------------------------------------------------------------------
// ConnectorTraits — base template (completely unknown triple → not present)
// ---------------------------------------------------------------------------

using BaseTrait = dev::ConnectorTraits<
    dev::PinId::none,
    dev::PeripheralId::none,
    dev::SignalId::none>;

static_assert(!BaseTrait::kPresent);
static_assert(BaseTrait::kConnectorId  == dev::ConnectorId::none);
static_assert(BaseTrait::kRouteId      == dev::RouteId::none);

// ---------------------------------------------------------------------------
// kConnectors descriptor table — non-empty, fields accessible
// ---------------------------------------------------------------------------

static_assert(dev::kConnectors.size() > 0u);

// First entry must have a non-none ConnectorId.
static_assert(dev::kConnectors[0].connector_id != dev::ConnectorId::none);
static_assert(dev::kConnectors[0].pin_id        != dev::PinId::none);
static_assert(dev::kConnectors[0].peripheral_id != dev::PeripheralId::none);
static_assert(dev::kConnectors[0].signal_id     != dev::SignalId::none);

// ---------------------------------------------------------------------------
// kRoutes table — same count as kConnectors, fields accessible
// ---------------------------------------------------------------------------

static_assert(dev::kRoutes.size() > 0u);
static_assert(dev::kRoutes.size() == dev::kConnectors.size());
static_assert(dev::kRoutes[0].route_id != dev::RouteId::none);
