//
// Created by Sakri Koskimies on 4/3/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_CORE_UTIL_PRIMITIVE_HPP_
#define JUST_SOME_GRAPHICS_SRC_CORE_UTIL_PRIMITIVE_HPP_

#include <vector>

#include "mappings.hpp"

struct Primitive {
 public:
  std::vector<Vertex> vertices;
  std::vector<Index> indices;
  std::vector<Vector2> tex_coords;

  /**
   * Create a new primitive cube
   * @return
   */
  static Primitive Cube() {
    Primitive primitive;

    primitive.indices = std::vector<Index>{
        2, 1, 0, 3, 2, 1,
        8, 9, 2, 4, 2, 9,
        2, 4, 3, 5, 3, 4,
        3, 5, 10, 11, 10, 5,
        4, 6, 5, 7, 5, 6,
        0, 7, 6, 1, 7, 0
    };

    /*auto vertices = std::vector<Vector3>{
        Vector3(1.0, 1.0, 1.0),
        Vector3(0.0f, 1.0, 1.0),
        Vector3(1.0, 1.0, 0.0f),
        Vector3(0.0f, 1.0, 0.0f),
        Vector3(1.0, 0.0f, 1.0),
        Vector3(0.0f, 0.0f, 1.0),
        Vector3(0.0f, 0.0f, 0.0f),
        Vector3(1.0, 0.0f, 0.0f)
    };*/

    primitive.vertices = std::vector<Vertex>{
        {Vector3(-1, 1, 1), Vector3(0, 0, 0), Vector2(0, 0)},
        {Vector3(1, 1, 1), Vector3(0, 0, 0), Vector2(1, 0)},
        {Vector3(-1, -1, 1), Vector3(0, 0, 0), Vector2(0, 1)},
        {Vector3(1, -1, 1), Vector3(0, 0, 0), Vector2(1, 1)},
        {Vector3(-1, -1, -1), Vector3(0, 0, 0), Vector2(0, 0)},
        {Vector3(1, -1, -1), Vector3(0, 0, 0), Vector2(1, 0)},
        {Vector3(-1, 1, -1), Vector3(0, 0, 0), Vector2(0, 1)},
        {Vector3(1, 1, -1), Vector3(0, 0, 0), Vector2(1, 1)},
        {Vector3(-1, 1, 1), Vector3(0, 0, 0), Vector2(1, 1)},
        {Vector3(-1, 1, -1), Vector3(0, 0, 0), Vector2(1, 0)},
        {Vector3(1, 1, 1), Vector3(0, 0, 0), Vector2(0, 1)},
        {Vector3(1, 1, -1), Vector3(0, 0, 0), Vector2(0, 0)}
    };

    return primitive;
  }
};

#endif //JUST_SOME_GRAPHICS_SRC_CORE_UTIL_PRIMITIVE_HPP_
