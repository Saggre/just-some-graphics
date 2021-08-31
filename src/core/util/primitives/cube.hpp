//
// Created by Sakri Koskimies on 31/8/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_CORE_UTIL_PRIMITIVE_CUBE_HPP_
#define JUST_SOME_GRAPHICS_SRC_CORE_UTIL_PRIMITIVE_CUBE_HPP_

#include <vector>

#include "../primitive.hpp"

struct Cube : Primitive {
 public:
  std::vector<Vertex> vertices = {
      {Vector3(0.5, -0.5, 0.5), Vector3(0.0, 0.0, 1.0), Vector2(0.0, 0.0)},
      {Vector3(-0.5, -0.5, 0.5), Vector3(0.0, 0.0, 1.0), Vector2(1.0, 0.0)},
      {Vector3(0.5, 0.5, 0.5), Vector3(0.0, 0.0, 1.0), Vector2(0.0, 1.0)},
      {Vector3(-0.5, 0.5, 0.5), Vector3(0.0, 0.0, 1.0), Vector2(1.0, 1.0)},
      {Vector3(0.5, 0.5, -0.5), Vector3(0.0, 1.0, 0.0), Vector2(0.0, 1.0)},
      {Vector3(-0.5, 0.5, -0.5), Vector3(0.0, 1.0, 0.0), Vector2(1.0, 1.0)},
      {Vector3(0.5, -0.5, -0.5), Vector3(0.0, 0.0, -1.0), Vector2(0.0, 1.0)},
      {Vector3(-0.5, -0.5, -0.5), Vector3(0.0, 0.0, -1.0), Vector2(1.0, 1.0)},
      {Vector3(0.5, 0.5, 0.5), Vector3(0.0, 1.0, 0.0), Vector2(0.0, 0.0)},
      {Vector3(-0.5, 0.5, 0.5), Vector3(0.0, 1.0, 0.0), Vector2(1.0, 0.0)},
      {Vector3(0.5, 0.5, -0.5), Vector3(0.0, 0.0, -1.0), Vector2(0.0, 0.0)},
      {Vector3(-0.5, 0.5, -0.5), Vector3(0.0, 0.0, -1.0), Vector2(1.0, 0.0)},
      {Vector3(0.5, -0.5, -0.5), Vector3(0.0, -1.0, 0.0), Vector2(0.0, 0.0)},
      {Vector3(0.5, -0.5, 0.5), Vector3(0.0, -1.0, 0.0), Vector2(0.0, 1.0)},
      {Vector3(-0.5, -0.5, 0.5), Vector3(0.0, -1.0, 0.0), Vector2(1.0, 1.0)},
      {Vector3(-0.5, -0.5, -0.5), Vector3(0.0, -1.0, 0.0), Vector2(1.0, 0.0)},
      {Vector3(-0.5, -0.5, 0.5), Vector3(-1.0, 0.0, 0.0), Vector2(0.0, 0.0)},
      {Vector3(-0.5, 0.5, 0.5), Vector3(-1.0, 0.0, 0.0), Vector2(0.0, 1.0)},
      {Vector3(-0.5, 0.5, -0.5), Vector3(-1.0, 0.0, 0.0), Vector2(1.0, 1.0)},
      {Vector3(-0.5, -0.5, -0.5), Vector3(-1.0, 0.0, 0.0), Vector2(1.0, 0.0)},
      {Vector3(0.5, -0.5, -0.5), Vector3(1.0, 0.0, 0.0), Vector2(0.0, 0.0)},
      {Vector3(0.5, 0.5, -0.5), Vector3(1.0, 0.0, 0.0), Vector2(0.0, 1.0)},
      {Vector3(0.5, 0.5, 0.5), Vector3(1.0, 0.0, 0.0), Vector2(1.0, 1.0)},
      {Vector3(0.5, -0.5, 0.5), Vector3(1.0, 0.0, 0.0), Vector2(1.0, 0.0)}
  };

  std::vector<Index> indices = {
      0, 2, 3, 0, 3, 1, 8, 4, 5, 8, 5, 9, 10, 6, 7, 10, 7, 11, 12, 13,
      14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23
  };

  std::vector<Vector2> tex_coords;
};

#endif //JUST_SOME_GRAPHICS_SRC_CORE_UTIL_PRIMITIVE_CUBE_HPP_
