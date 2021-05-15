//
// Created by Sakri Koskimies on 5/15/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_CORE_UTIL_PRINT_HPP_
#define JUST_SOME_GRAPHICS_SRC_CORE_UTIL_PRINT_HPP_

#include "src/core/util/mappings.hpp"

class Print {
 public:
  static void pos(const Vector4 &pos) {
    std::cout << pos.x << " | " << pos.y << " | " << pos.z << pos.w << "\n";
  }

  static void pos(const Vector3 &pos) {
    std::cout << pos.x << " | " << pos.y << " | " << pos.z << "\n";
  }

  static void pos(const Vector2 &pos) {
    std::cout << pos.x << " | " << pos.y << "\n";
  }
};

#endif //JUST_SOME_GRAPHICS_SRC_CORE_UTIL_PRINT_HPP_
