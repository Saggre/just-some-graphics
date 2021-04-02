#include "application.hpp"

#include <GLFW/glfw3.h>
#include <mathfu/vector.h>
#include <mathfu/matrix.h>
#include <mathfu/glsl_mappings.h>
#include <iostream>
#include <vector>

#include "src/core/gl_error.hpp"

#define SHADER_DIR "../shader/"

struct VertexType {
  mathfu::vec3 position;
  mathfu::vec3 normal;
  mathfu::vec4 color;
};

float HeightMap(const mathfu::vec2& position) {
  return 2.0 * sin(position.x) * sin(position.y);
}

VertexType GetHeightMap(const mathfu::vec2& position) {
  const mathfu::vec2 dx(1.0, 0.0);
  const mathfu::vec2 dy(0.0, 1.0);

  VertexType v;
  float h = HeightMap(position);
  float hx = 100.f * (HeightMap(position + 0.01f * dx) - h);
  float hy = 100.f * (HeightMap(position + 0.01f * dy) - h);

  v.position = mathfu::vec3(position, h);
  v.normal = mathfu::normalize(mathfu::vec3(-hx, -hy, 1.0));

  float c = sin(h * 5.f) * 0.5 + 0.5;
  v.color = mathfu::vec4(c, 1.0 - c, 1.0, 1.0);
  return v;
}

Application::Application() :
    ApplicationCore(),
    vertex_shader(SHADER_DIR "/shader.vert", GL_VERTEX_SHADER),
    fragment_shader(SHADER_DIR "/shader.frag", GL_FRAGMENT_SHADER),
    shader_program({vertex_shader, fragment_shader}) {
  GLCheckError(__FILE__, __LINE__);

  // creation of the mesh ------------------------------------------------------
  std::vector<VertexType> vertices;
  std::vector<GLuint> index;

  for (int y = 0; y <= size; ++y)
    for (int x = 0; x <= size; ++x) {
      float xx = (x - size / 2) * 0.1f;
      float yy = (y - size / 2) * 0.1f;
      vertices.push_back(GetHeightMap({xx, yy}));
    }

  for (int y = 0; y < size; ++y)
    for (int x = 0; x < size; ++x) {
      index.push_back((x + 0) + (size + 1) * (y + 0));
      index.push_back((x + 1) + (size + 1) * (y + 0));
      index.push_back((x + 1) + (size + 1) * (y + 1));

      index.push_back((x + 1) + (size + 1) * (y + 1));
      index.push_back((x + 0) + (size + 1) * (y + 1));
      index.push_back((x + 0) + (size + 1) * (y + 0));
    }

  std::cout << "vertices=" << vertices.size() << std::endl;
  std::cout << "index=" << index.size() << std::endl;

  // creation of the vertex array buffer----------------------------------------

  vao = -1;
  vbo = -1;
  ibo = -1;

  // vbo
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexType),
               vertices.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // ibo
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(GLuint),
               index.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // vao
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // bind vbo
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  // map vbo to shader attributes
  shader_program.SetAttribute("position", 3, sizeof(VertexType),
                              offsetof(VertexType, position));
  shader_program.SetAttribute("normal", 3, sizeof(VertexType),
                              offsetof(VertexType, normal));
  shader_program.SetAttribute("color", 4, sizeof(VertexType),
                              offsetof(VertexType, color));

  // bind the ibo
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

  // vao end
  glBindVertexArray(0);
}

void Application::Loop() {
  ApplicationCore::Loop();

  // exit on window close button pressed
  if (glfwWindowShouldClose(GetWindow())) {
    Exit();
  }

  float t = GetTime();
  // set matrix : projection + view
  projection = mathfu::mat4::Perspective(
      float(2.0 * atan(getHeight() / 1920.f)),
      GetWindowRatio(), 0.1f, 100.f
  );

  view = mathfu::mat4::LookAt(
      mathfu::vec3(0.0, 0.0, 0.0),
      mathfu::vec3(20.0 * sin(t), 20.0 * cos(t), 20.0),
      mathfu::vec3(0.0, 0.0, 1.0),
      1
  );

  // clear
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  shader_program.Use();

  // send uniforms
  shader_program.SetUniform("projection", projection);
  shader_program.SetUniform("view", view);

  GLCheckError(__FILE__, __LINE__);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

  GLCheckError(__FILE__, __LINE__);
  glDrawElements(GL_TRIANGLES,        // mode
                 size * size * 2 * 3, // count
                 GL_UNSIGNED_INT,     // type
                 nullptr                 // element array buffer offset
  );

  glBindVertexArray(0);

  ShaderProgram::Unuse();
}
