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
#include <SDL.h>

#include "abstract_updatable.hpp"
#include "multi_frame_data.hpp"

using PressedKeyMap = std::bitset<512>;

class InputManager {
 public:
  enum Key {
    None = 0,
    Left = SDLK_LEFT,
    Right = SDLK_RIGHT,
    Up = SDLK_UP,
    Down = SDLK_DOWN,
    W = SDLK_w,
    A = SDLK_a,
    S = SDLK_s,
    D = SDLK_d,
    Space = SDLK_SPACE,
    LCtrl = SDLK_LCTRL,
    LShift = SDLK_LSHIFT,
    Esc = SDLK_ESCAPE,
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

  void Init(SDL_Window *window) {
    window_ = window;
    UpdateMouse();
    UpdateMouse();
  }

  void Update() {
    UpdateMouse();

    // Update keyboard bitset
    keys_last_frame_ = keys_;

    const uint8_t *state = SDL_GetKeyboardState(nullptr);
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
  inline static int mouse_pos_[2];
  inline static int mouse_pos_last_frame_[2];
  inline static PressedKeyMap keys_;
  inline static PressedKeyMap keys_last_frame_;
  SDL_Window *window_;

  /**
   * Calculate mouse delta
   */
  void UpdateMouse() {
    int *x, *y;
    SDL_GetMouseState(x, y);

    mouse_pos_last_frame_[0] = mouse_pos_[0];
    mouse_pos_last_frame_[1] = mouse_pos_[1];

    mouse_pos_[0] = *x;
    mouse_pos_[1] = *y;
  }
};

#endif //JUST_SOME_GRAPHICS_SRC_CORE_INPUT_MANAGER_HPP_
