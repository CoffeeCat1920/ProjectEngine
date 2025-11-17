// To defining components related to Physics-System cycle 

#pragma once

#include <ComponentRegistry/ComponentRegistry.hpp>
#include <json_util.hpp>
#include <raylib.h>

inline void to_json(json &j, const Vector2 &v) {
  j = json{{"x", v.x}, {"y", v.y}};
}

inline void from_json(const json &j, Vector2 &v) {
  v.x = j.at("x").get<float>();
  v.y = j.at("y").get<float>();
}
REFLECTION(Vector2);

struct CGravity {
  Vector2 force{};
  NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CGravity, force)
};
REFLECTION(CGravity);

struct CRigidBody {
  Vector2 velocity{};
  Vector2 acceleration{};
  NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CRigidBody, velocity,
                                              acceleration)
};
REFLECTION(CRigidBody);
