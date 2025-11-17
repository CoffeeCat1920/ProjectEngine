#pragma once
#include <ECS/component/component.hpp>

namespace signatureUtils {

inline Signature GetSignature(ComponentId componentId) {
  Signature signature;
  signature.set(componentId, true);
  return signature;
}

inline Signature GetSignature(std::initializer_list<ComponentId> componentIds) {
  Signature signature;
  for (auto id : componentIds) {
    signature.set(id);
  }
  return signature;
}

template <typename... ComponentIds>

inline Signature GetSignature(ComponentIds... componentsIds) {
  Signature signature;
  (signature.set(componentsIds, true), ...);
  return signature;
}

} // namespace signatureUtils
