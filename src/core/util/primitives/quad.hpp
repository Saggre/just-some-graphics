//
// Created by Sakri Koskimies on 31/8/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_CORE_UTIL_PRIMITIVE_QUAD_HPP_
#define JUST_SOME_GRAPHICS_SRC_CORE_UTIL_PRIMITIVE_QUAD_HPP_

#include <vector>

#include "../primitive.hpp"

struct Quad : Primitive {
 public:
  Quad() {
    vertices = {
        {Vector3(-0.5, -0.5, -3.061617E-17), Vector3(0, 0, -1), Vector2(0, 0)},
        {Vector3(0.5, -0.5, -3.061617E-17), Vector3(0, 0, -1), Vector2(1, 0)},
        {Vector3(-0.5, 0.5, 3.061617E-17), Vector3(0, 0, -1), Vector2(0, 1)},
        {Vector3(0.5, 0.5, 3.061617E-17), Vector3(0, 0, -1), Vector2(1, 1)},

    };

    indices = {
        0, 3, 1, 3, 0, 2,
    };
  }
};

#endif //JUST_SOME_GRAPHICS_SRC_CORE_UTIL_PRIMITIVE_QUAD_HPP_
