//
// Created by Sakri Koskimies on 4/2/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_CREATIVE_CAMERA_HPP_
#define JUST_SOME_GRAPHICS_SRC_CREATIVE_CAMERA_HPP_

#include "component.hpp"
#include "src/core/input_manager.hpp"

#include <mathfu/vector.h>
#include <mathfu/quaternion.h>
#include <mathfu/glsl_mappings.h>
#include <cmath>

/**
 * A "creative mode" camera, that can fly around
 */
class CreativeCamera : public Component {
  void Start() override {
  }

  void Update() override {
    float speed = 0.33f;

    auto move_delta = mathfu::vec3(0, 0, 0);

    if (InputManager::IsKeyPressed(InputManager::D)) {
      move_delta += transform->Right();
    }

    if (InputManager::IsKeyPressed(InputManager::A)) {
      move_delta -= transform->Right();
    }

    if (InputManager::IsKeyPressed(InputManager::W)) {
      auto dir = transform->Forward();
      dir.y = 0;
      move_delta += dir.Normalized();
    }

    if (InputManager::IsKeyPressed(InputManager::S)) {
      auto dir = transform->Forward();
      dir.y = 0;
      move_delta -= dir.Normalized();
    }

    if (InputManager::IsKeyPressed(InputManager::Space)) {
      move_delta += mathfu::vec3(0, 1, 0);
    }

    if (InputManager::IsKeyPressed(InputManager::LCtrl)) {
      move_delta -= mathfu::vec3(0, 1, 0);
    }

    if (move_delta.Length() > 1.0) {
      move_delta = move_delta.Normalized();
    }

    transform->Move(move_delta * speed);

    auto mouse = InputManager::GetMouseDelta();

    float sens = 0.2;

    const float MIN_Y = -M_PI * 0.5 + 0.01;
    const float MAX_Y = M_PI * 0.5 - 0.01;

    mouse_rot_[0] += mouse.y * sens * Time::delta_time_;

    if (mouse_rot_[0] < MIN_Y) {
      mouse_rot_[0] = MIN_Y;
    } else if (mouse_rot_[0] > MAX_Y) {
      mouse_rot_[0] = MAX_Y;
    }

    mouse_rot_[1] += mouse.x * sens * Time::delta_time_;

    if (mouse_rot_[1] > M_PI * 2) {
      mouse_rot_[1] -= M_PI * 2;
    } else if (mouse_rot_[1] < -M_PI * 2) {
      mouse_rot_[1] += M_PI * 2;
    }

    //std::cout << std::to_string(mouse.y) << "\n";
    //std::cout << std::to_string(mouse.x) << "\n";

    transform->SetRotation(mathfu::quat::FromEulerAngles(mouse_rot_[0], mouse_rot_[1], 0));
  }

  void End() override {
  }

 private:
  mathfu::vec2 mouse_rot_;
};

#endif //JUST_SOME_GRAPHICS_SRC_CREATIVE_CAMERA_HPP_