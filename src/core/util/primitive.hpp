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
   * Create a new plane
   * @return
   */
  static Primitive Plane() {
    Primitive primitive;

    primitive.indices = std::vector<Index>{
        0, 2, 3, 0, 3, 1, 8, 4, 5, 8, 5, 9, 10, 6, 7, 10, 7, 11, 12, 13,
        14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23
    };

    primitive.vertices = std::vector<Vertex>{
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

    return primitive;
  }

  /**
   * Create a new plane
   * @return
   */
  static Primitive Sphere() {
    Primitive primitive;

    primitive.indices = std::vector<Index>{
        0, 2, 3, 0, 3, 1, 8, 4, 5, 8, 5, 9, 10, 6, 7, 10, 7, 11, 12, 13,
        14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23
    };

    primitive.vertices = std::vector<Vertex>{
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

    return primitive;
  }

  /**
   * Create a new cube
   * @return
   */
  static Primitive Cube() {
    Primitive primitive;

    primitive.indices = std::vector<Index>{
        0, 2, 3, 0, 3, 1, 8, 4, 5, 8, 5, 9, 10, 6, 7, 10, 7, 11, 12, 13,
        14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23
    };

    primitive.vertices = std::vector<Vertex>{
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

    return primitive;
  }
};

#endif //JUST_SOME_GRAPHICS_SRC_CORE_UTIL_PRIMITIVE_HPP_
