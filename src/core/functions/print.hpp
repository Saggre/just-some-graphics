//
// Created by Sakri Koskimies on 6/11/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_CORE_FUNCTIONS_PRINT_HPP_
#define JUST_SOME_GRAPHICS_SRC_CORE_FUNCTIONS_PRINT_HPP_

#include <iostream>
#include <iomanip>

#include "src/core/util/mappings.hpp"

static void Print(const float &val) {
  std::cout << std::fixed << std::setprecision(3) << val << "\n";
}

static void Print(const Vector4 &val) {
  std::cout << val.x << " | " << val.y << " | " << val.z << val.w << "\n";
}

static void Print(const Vector3 &val) {
  std::cout << val.x << " | " << val.y << " | " << val.z << "\n";
}

static void Print(const Vector2 &val) {
  std::cout << val.x << " | " << val.y << "\n";
}

#endif //JUST_SOME_GRAPHICS_SRC_CORE_FUNCTIONS_PRINT_HPP_
