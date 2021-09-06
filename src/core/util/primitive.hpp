//
// Created by Sakri Koskimies on 4/3/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_CORE_UTIL_PRIMITIVE_HPP_
#define JUST_SOME_GRAPHICS_SRC_CORE_UTIL_PRIMITIVE_HPP_

#include <vector>

#include "mappings.hpp"

struct Primitive {
 public:
  const std::vector<Vertex> &GetVertices() const {
    return vertices;
  }

  const std::vector<Index> &GetIndices() const {
    return indices;
  }

  const std::vector<Vector2> &GetTexCoords() const {
    return tex_coords;
  }

 protected:
  std::vector<Vertex> vertices;
  std::vector<Index> indices;
  std::vector<Vector2> tex_coords;
};

#endif //JUST_SOME_GRAPHICS_SRC_CORE_UTIL_PRIMITIVE_HPP_
