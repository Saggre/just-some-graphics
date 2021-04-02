//
// Created by Sakri Koskimies on 4/3/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_CORE_COMPONENTS_MESH_HPP_
#define JUST_SOME_GRAPHICS_SRC_CORE_COMPONENTS_MESH_HPP_

#include <mathfu/vector.h>
#include <mathfu/matrix.h>
#include <mathfu/glsl_mappings.h>
#include <vector>

#include "component.hpp"

class Mesh : public Component {
 public:
  struct Vertex {
    mathfu::vec3 position;
    mathfu::vec3 normal;
    mathfu::vec4 color;
  };

  const int size = 100;
  void Start() override {
    for (int y = 0; y <= size; ++y)
      for (int x = 0; x <= size; ++x) {
        float xx = (x - size / 2) * 0.1f;
        float yy = (y - size / 2) * 0.1f;
        vertices_.push_back(GetHeightMap({xx, yy}));
      }

    for (int y = 0; y < size; ++y)
      for (int x = 0; x < size; ++x) {
        indices_.push_back((x + 0) + (size + 1) * (y + 0));
        indices_.push_back((x + 1) + (size + 1) * (y + 0));
        indices_.push_back((x + 1) + (size + 1) * (y + 1));

        indices_.push_back((x + 1) + (size + 1) * (y + 1));
        indices_.push_back((x + 0) + (size + 1) * (y + 1));
        indices_.push_back((x + 0) + (size + 1) * (y + 0));
      }
  }

  void Update() override {

  }

  void End() override {

  }

  const std::vector<Vertex> &GetVertices() const {
    return vertices_;
  }

  const std::vector<uint32_t> &GetIndices() const {
    return indices_;
  }
 private:
  std::vector<Vertex> vertices_;
  std::vector<uint32_t> indices_; // TODO make sure it's always this type

  static float HeightMap(const mathfu::vec2 &position) {
    return 2.0 * sin(position.x) * sin(position.y);
  }

  static Vertex GetHeightMap(const mathfu::vec2 &position) {
    const mathfu::vec2 dx(1.0, 0.0);
    const mathfu::vec2 dy(0.0, 1.0);

    Vertex v;
    float h = HeightMap(position);
    float hx = 100.f * (HeightMap(position + 0.01f * dx) - h);
    float hy = 100.f * (HeightMap(position + 0.01f * dy) - h);

    v.position = mathfu::vec3(position, h);
    v.normal = mathfu::normalize(mathfu::vec3(-hx, -hy, 1.0));

    float c = sin(h * 5.f) * 0.5 + 0.5;
    v.color = mathfu::vec4(c, 1.0 - c, 1.0, 1.0);
    return v;
  }
};

#endif //JUST_SOME_GRAPHICS_SRC_CORE_COMPONENTS_MESH_HPP_
