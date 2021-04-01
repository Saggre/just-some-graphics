//
// Created by Sakri Koskimies on 4/2/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_TRANSFORM_HPP_
#define JUST_SOME_GRAPHICS_SRC_TRANSFORM_HPP_

#include "entity.hpp"

#include <mathfu/vector.h>
#include <mathfu/quaternion.h>
#include <mathfu/glsl_mappings.h>

/**
 * A class that contains movement-related stuff
 */
class Transform {
  using Vector3 = mathfu::vec3;
  using Quaternion = mathfu::quat;

 public:
  Entity parent;
  Vector3 position;
  Quaternion rotation;
  Vector3 scale;

 private:
  Vector3 lastPosition;
  Quaternion lastRotation;
  Vector3 lastScale;

  Vector3 deltaPosition;
  Quaternion deltaRotation;
  Vector3 deltaScale;
};

#endif //JUST_SOME_GRAPHICS_SRC_TRANSFORM_HPP_
