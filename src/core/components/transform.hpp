//
// Created by Sakri Koskimies on 4/2/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_TRANSFORM_HPP_
#define JUST_SOME_GRAPHICS_SRC_TRANSFORM_HPP_

#include <mathfu/vector.h>
#include <mathfu/quaternion.h>
#include <mathfu/glsl_mappings.h>
#include <cmath>

#include "src/core/components/component.hpp"
#include "src/core/input_manager.hpp"

/**
 * A class that contains movement-related stuff
 */
class Transform : public Component {
  using Vector2 = mathfu::vec2;
  using Vector3 = mathfu::vec3;
  using Quaternion = mathfu::quat;

 public:
  float speed = 0.02f;

  Transform() {
    position = Vector3(0, 0, 0);
    rotation = Quaternion::identity;
    local_scale = Vector3(1, 1, 1);
  };

  void Start() override {

  }

  void Update() override {

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

  void SetRotation(const Quaternion &new_rotation) {
    Transform::rotation = new_rotation;
  }

  void SetLocalScale(const Vector3 &new_local_scale) {
    Transform::local_scale = new_local_scale;
  }

  void Move(const Vector3 &delta) {
    position += delta;
  }

  void Rotate(const Quaternion &delta) {
    rotation = rotation * delta;
  }

  // TODO implement the rest

 private:
  Vector3 position;
  Quaternion rotation;
  Vector3 local_scale;
};

#endif //JUST_SOME_GRAPHICS_SRC_TRANSFORM_HPP_
