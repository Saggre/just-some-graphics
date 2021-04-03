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
#include <cmath>

/**
 * A class that contains movement-related stuff
 */
class Transform : public Component {
  using Vector2 = mathfu::vec2;
  using Vector3 = mathfu::vec3;
  using Quaternion = mathfu::quat;

 public:
  float speed = 0.02f;
  // temp
  bool use_mouse = false;

  Transform() {
    position = Vector3(0, 0, 0);
    rotation = Quaternion::identity;
    local_scale = Vector3(1, 1, 1);
    mouse_rot_ = Vector2(0, 0);
  };

  void Start() override {

  }

  void Update() override {
    // TODO input axes

    float speed = 0.33f;

    if (InputManager::IsKeyPressed(InputManager::D)) {
      position += Right() * speed;
    }

    if (InputManager::IsKeyPressed(InputManager::A)) {
      position -= Right() * speed;
    }

    if (InputManager::IsKeyPressed(InputManager::W)) {
      auto dir = Forward();
      dir.y = 0;
      position += dir.Normalized() * speed;
    }

    if (InputManager::IsKeyPressed(InputManager::S)) {
      auto dir = Forward();
      dir.y = 0;
      position -= dir.Normalized() * speed;
    }

    if (InputManager::IsKeyPressed(InputManager::Space)) {
      position += mathfu::vec3(0, 1, 0) * speed;
    }

    if (InputManager::IsKeyPressed(InputManager::LCtrl)) {
      position -= mathfu::vec3(0, 1, 0) * speed;
    }

    auto mouse = InputManager::GetMouseDelta();

    float sens = 0.003;

    const float MIN_Y = -M_PI * 0.5 + 0.01;
    const float MAX_Y = M_PI * 0.5 - 0.01;

    mouse_rot_[0] += mouse.y * sens;

    if (mouse_rot_[0] < MIN_Y) {
      mouse_rot_[0] = MIN_Y;
    } else if (mouse_rot_[0] > MAX_Y) {
      mouse_rot_[0] = MAX_Y;
    }

    mouse_rot_[1] += mouse.x * sens;

    if (mouse_rot_[1] > M_PI * 2) {
      mouse_rot_[1] -= M_PI * 2;
    } else if (mouse_rot_[1] < -M_PI * 2) {
      mouse_rot_[1] += M_PI * 2;
    }

    //std::cout << std::to_string(mouse.y) << "\n";
    //std::cout << std::to_string(mouse.x) << "\n";

    rotation = Quaternion::FromEulerAngles(mouse_rot_[0], mouse_rot_[1], 0);
  }

  void End() override {

  }

  Vector3 Forward() {
    return rotation * Vector3(0, 0, 1);
  }

  Vector3 Up() {
    return rotation * Vector3(0, 1, 0);
  }

  Vector3 Right() {
    return rotation * Vector3(1, 0, 0);
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
  // temp
  Vector2 mouse_rot_;
};

#endif //JUST_SOME_GRAPHICS_SRC_TRANSFORM_HPP_
