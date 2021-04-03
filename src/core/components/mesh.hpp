//
// Created by Sakri Koskimies on 4/3/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_CORE_COMPONENTS_MESH_HPP_
#define JUST_SOME_GRAPHICS_SRC_CORE_COMPONENTS_MESH_HPP_

#include <mathfu/vector.h>
#include <mathfu/matrix.h>
#include <mathfu/glsl_mappings.h>
#include <vector>
#include <src/core/util/primitive.hpp>

#include "component.hpp"
#include "../util/mappings.hpp"

class Mesh : public Component {
 public:
  void Start() override {

  }

  void Update() override {

  }

  void End() override {

  }

  /**
   * Create a mesh from a primitive
   * @param primitive
   * @return
   */
  static Mesh FromPrimitive(const Primitive &primitive) {
    Mesh mesh;
    mesh.indices = primitive.indices;
    mesh.vertices = primitive.vertices;
    mesh.tex_coords = primitive.tex_coords;
    mesh.normals = primitive.normals;
    return mesh;
  }

  inline const std::vector<Vertex> &GetVertices() const {
    return vertices;
  }

  inline const std::vector<uint32_t> &GetIndices() const {
    return indices;
  }

  inline const std::vector<Vector3> &GetNormals() const {
    return normals;
  }

  inline const std::vector<Vector2> &GetTexCoords() const {
    return tex_coords;
  }

 private:
  std::vector<Vector3> vertices;
  std::vector<Vector3> normals;
  std::vector<Index> indices;
  std::vector<Vector2> tex_coords;
};

#endif //JUST_SOME_GRAPHICS_SRC_CORE_COMPONENTS_MESH_HPP_
