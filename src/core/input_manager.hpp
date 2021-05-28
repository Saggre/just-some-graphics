//
// Created by Sakri Koskimies on 4/2/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_CORE_INPUT_MANAGER_HPP_
#define JUST_SOME_GRAPHICS_SRC_CORE_INPUT_MANAGER_HPP_

#include <iostream>
#include <bitset>
#include <map>
#include <mathfu/vector.h>
#include <mathfu/glsl_mappings.h>
#include <SDL2/SDL.h>

#include "abstract_updatable.hpp"
#include "multi_frame_data.hpp"

using PressedKeyMap = std::bitset<SDL_NUM_SCANCODES>;

class InputManager {
 public:
  enum Key {
    Left = SDL_SCANCODE_LEFT,
    Right = SDL_SCANCODE_RIGHT,
    Up = SDL_SCANCODE_UP,
    Down = SDL_SCANCODE_DOWN,
    W = SDL_SCANCODE_W,
    A = SDL_SCANCODE_A,
    S = SDL_SCANCODE_S,
    D = SDL_SCANCODE_D,
    Space = SDL_SCANCODE_SPACE,
    LCtrl = SDL_SCANCODE_LCTRL,
    LShift = SDL_SCANCODE_LSHIFT,
    Esc = SDL_SCANCODE_ESCAPE,
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

    return mathfu::vec2(mouse_delta_[0], mouse_delta_[1]);
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

  void Init(SDL_Window *window) {
    window_ = window;
    UpdateMouse(); // TODO needed?
    UpdateMouse();
  }

  void Update() {
    UpdateMouse();

    // Update keyboard bitset
    keys_last_frame_ = keys_;

    auto *state = SDL_GetKeyboardState(nullptr);
    for (int key : all_keys) {
      if (state[key]) {
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
  inline static int mouse_delta_[2];
  inline static PressedKeyMap keys_;
  inline static PressedKeyMap keys_last_frame_;
  SDL_Window *window_;

  /**
   * Calculate mouse delta
   */
  static void UpdateMouse() {
    int x, y;
    SDL_GetRelativeMouseState(&x, &y);

    mouse_delta_[0] = x;
    mouse_delta_[1] = y;
  }
};

#endif //JUST_SOME_GRAPHICS_SRC_CORE_INPUT_MANAGER_HPP_
