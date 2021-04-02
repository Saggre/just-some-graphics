//
// Created by Sakri Koskimies on 4/2/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_TRANSFORM_HPP_
#define JUST_SOME_GRAPHICS_SRC_TRANSFORM_HPP_

#include "entity.hpp"
#include "multi_frame_data.hpp"

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

  Transform() {
    position = MultiFrameData<Vector3>();
  }

  Vector3 GetPosition() const {
    return position.current_frame();
  }

  Quaternion GetRotation() const {
    return rotation.current_frame();
  }

  Vector3 GetLocalScale() const {
    return local_scale.current_frame();
  }

  void SetPosition(const Vector3 &new_position) const {
    this.position.Update(new_position);
  }

  // TODO implement the rest

 private:
  MultiFrameData<Vector3> position;
  MultiFrameData<Quaternion> rotation;
  MultiFrameData<Vector3> local_scale;
};

#endif //JUST_SOME_GRAPHICS_SRC_TRANSFORM_HPP_
