//
// Created by Sakri Koskimies on 4/3/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_CORE_UTIL_PRIMITIVE_HPP_
#define JUST_SOME_GRAPHICS_SRC_CORE_UTIL_PRIMITIVE_HPP_

#include <vector>

#include "mappings.hpp"

class Primitive {
 public:
  std::vector<Vector3> vertices;
  std::vector<Vector3> normals;
  std::vector<Index> indices;
  std::vector<Vector2> tex_coords;

  /**
   * Create a new primitive cube
   * @return
   */
  static Primitive Cube() {
    Primitive primitive;
    primitive.vertices = std::vector<Vector3>{
        Vector3(-1, -1, -1),
        Vector3(1, -1, -1),
        Vector3(1, 1, -1),
        Vector3(-1, 1, -1),
        Vector3(-1, -1, 1),
        Vector3(1, -1, 1),
        Vector3(1, 1, 1),
        Vector3(-1, 1, 1)
    };

    primitive.indices = std::vector<Index>{
        0, 1, 3, 3, 1, 2,
        1, 5, 2, 2, 5, 6,
        5, 4, 6, 6, 4, 7,
        4, 0, 7, 7, 0, 3,
        3, 2, 7, 7, 2, 6,
        4, 5, 0, 0, 5, 1
    };

    primitive.normals = std::vector<Vector3>{
        Vector3(0, 0, 1),
        Vector3(1, 0, 0),
        Vector3(0, 0, -1),
        Vector3(-1, 0, 0),
        Vector3(0, 1, 0),
        Vector3(0, -1, 0)
    };

    primitive.tex_coords = std::vector<Vector2>{
        Vector2(0, 0),
        Vector2(1, 0),
        Vector2(1, 1),
        Vector2(0, 1)
    };
  }
};

#endif //JUST_SOME_GRAPHICS_SRC_CORE_UTIL_PRIMITIVE_HPP_
