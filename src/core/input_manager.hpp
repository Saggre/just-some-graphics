//
// Created by Sakri Koskimies on 4/2/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_CORE_INPUT_MANAGER_HPP_
#define JUST_SOME_GRAPHICS_SRC_CORE_INPUT_MANAGER_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <bitset>
#include <map>
#include <mathfu/vector.h>
#include <mathfu/glsl_mappings.h>

#include "abstract_updatable.hpp"
#include "multi_frame_data.hpp"

using PressedKeyMap = std::bitset<512>;

class InputManager {
 public:
  enum Key {
    None = 0,
    Left = GLFW_KEY_LEFT,
    Right = GLFW_KEY_RIGHT,
    Up = GLFW_KEY_UP,
    Down = GLFW_KEY_DOWN,
    W = GLFW_KEY_W,
    A = GLFW_KEY_A,
    S = GLFW_KEY_S,
    D = GLFW_KEY_D,
    Space = GLFW_KEY_SPACE,
    LCtrl = GLFW_KEY_LEFT_CONTROL,
    LShift = GLFW_KEY_LEFT_SHIFT,
    Esc = GLFW_KEY_ESCAPE,
    KeyEnd
  };

  inline static const Key all_keys[] = {Left, Right, Up, Down, W, A, S, D, Esc, Space, LCtrl, LShift};

  InputManager() {
    window_ = nullptr;
  }

  /**
   * Mouse position delta since last frame
   * @return
   */
  static mathfu::vec2 GetMouseDelta() {
    if (!mouse_enabled_) {
      return mathfu::vec2(0, 0);
    }

    return mathfu::vec2(mouse_pos_[0] - mouse_pos_last_frame_[0], mouse_pos_[1] - mouse_pos_last_frame_[1]);
  }

  /**
   * Returns true if the key is pressed
   * @param keycode
   * @return
   */
  static bool IsKeyPressed(Key keycode) {
    return keys_.test(keycode);
  }

  /**
   * Returns true if the key was just pressed
   * @param keycode
   * @return
   */
  static bool IsKeyDown(Key keycode) {
    return keys_.test(keycode) && !keys_last_frame_.test(keycode);
  }

  /**
   * Returns true if the key was just released
   * @param keycode
   * @return
   */
  static bool IsKeyUp(Key keycode) {
    return !keys_.test(keycode) && keys_last_frame_.test(keycode);
  }

  void Init(GLFWwindow *window) {
    window_ = window;
    UpdateMouse();
    UpdateMouse();
  }

  void Update() {
    UpdateMouse();

    // Update keyboard bitset
    keys_last_frame_ = keys_;

    for (int key : all_keys) {
      int state = glfwGetKey(window_, key);
      if (state == GLFW_PRESS) {
        keys_.set(key, true);
      } else {
        keys_.set(key, false);
      }
    }
  }

  static bool IsMouseEnabled() {
    return mouse_enabled_;
  }

  static void SetMouseEnabled(bool mouse_enabled) {
    mouse_enabled_ = mouse_enabled;
  }

 private:
  inline static bool mouse_enabled_ = false;
  inline static float mouse_pos_[2];
  inline static float mouse_pos_last_frame_[2];
  inline static PressedKeyMap keys_;
  inline static PressedKeyMap keys_last_frame_;
  GLFWwindow *window_;

  /**
   * Calculate mouse delta
   */
  void UpdateMouse() {
    double x, y;
    glfwGetCursorPos(window_, &x, &y);

    mouse_pos_last_frame_[0] = mouse_pos_[0];
    mouse_pos_last_frame_[1] = mouse_pos_[1];

    mouse_pos_[0] = (float) x;
    mouse_pos_[1] = (float) y;
  }
};

#endif //JUST_SOME_GRAPHICS_SRC_CORE_INPUT_MANAGER_HPP_
