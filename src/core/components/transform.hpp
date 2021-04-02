//
// Created by Sakri Koskimies on 4/2/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_TRANSFORM_HPP_
#define JUST_SOME_GRAPHICS_SRC_TRANSFORM_HPP_

#include "src/core/multi_frame_data.hpp"
#include "src/core/components/component.hpp"
#include "src/core/input_manager.hpp"

#include <mathfu/vector.h>
#include <mathfu/quaternion.h>
#include <mathfu/glsl_mappings.h>

/**
 * A class that contains movement-related stuff
 */
class Transform : public Component {
  using Vector3 = mathfu::vec3;
  using Quaternion = mathfu::quat;

 public:
  float speed = 0.02f;

  Transform() = default;

  void Start() override {

  }

  void Update() override {
    // TODO input axes

    if (InputManager::IsKeyPressed(InputManager::D)) {
      position.x += speed;
    }

    if (InputManager::IsKeyPressed(InputManager::A)) {
      position.x -= speed;
    }

    if (InputManager::IsKeyPressed(InputManager::W)) {
      position.y += speed;
    }

    if (InputManager::IsKeyPressed(InputManager::S)) {
      position.y -= speed;
    }

  }

  void End() override {

  }

  Vector3 GetPosition() const {
    return position;
  }

  Quaternion GetRotation() const {
    return rotation;
  }

  Vector3 GetLocalScale() const {
    return local_scale;
  }

  void SetPosition(const Vector3 &new_position) {
    position = new_position;
  }

  // TODO implement the rest

 private:
  Vector3 position;
  Quaternion rotation;
  Vector3 local_scale;
};

#endif //JUST_SOME_GRAPHICS_SRC_TRANSFORM_HPP_
