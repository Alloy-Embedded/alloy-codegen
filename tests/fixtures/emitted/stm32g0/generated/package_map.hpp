#pragma once

namespace st {
namespace stm32g0 {
namespace generated {
struct PackageDescriptor {
  const char* device;
  const char* package_name;
  int pin_count;
};
inline constexpr PackageDescriptor kPackageMap[] = {
  {"stm32g071rb", "lqfp64", 64},
};

struct PackagePadDescriptor {
  const char* device;
  const char* package_name;
  const char* pad_id;
  const char* position_label;
  int physical_index;
  const char* pad_kind;
  const char* bonded_pin;
  const char* bonding_state;
};
inline constexpr PackagePadDescriptor kPackagePads[] = {
  {"stm32g071rb", "lqfp64", "17", "17", 17, "io", "PA0", "bonded"},
  {"stm32g071rb", "lqfp64", "18", "18", 18, "io", "PA1", "bonded"},
  {"stm32g071rb", "lqfp64", "19", "19", 19, "io", "PA2", "bonded"},
  {"stm32g071rb", "lqfp64", "20", "20", 20, "io", "PA3", "bonded"},
  {"stm32g071rb", "lqfp64", "29", "29", 29, "io", "PB6", "bonded"},
  {"stm32g071rb", "lqfp64", "30", "30", 30, "io", "PB7", "bonded"},
};

struct PinConstraintDescriptor {
  const char* device;
  const char* pin_name;
  const char* kind;
  const char* value;
};
inline constexpr PinConstraintDescriptor kPinConstraints[] = {
};
}
}
}
