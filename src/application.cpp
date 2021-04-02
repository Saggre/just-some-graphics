#include "application.hpp"

#include <GLFW/glfw3.h>
#include <mathfu/vector.h>
#include <mathfu/matrix.h>
#include <mathfu/glsl_mappings.h>
#include <iostream>
#include <vector>

#include "src/core/gl_error.hpp"
#include "src/core/entity.hpp"
#include "src/core/components/mesh.hpp"

#define SHADER_DIR "../shader/"

Application::Application() :
    ApplicationCore(),
    vertex_shader(SHADER_DIR "/shader.vert", GL_VERTEX_SHADER),
    fragment_shader(SHADER_DIR "/shader.frag", GL_FRAGMENT_SHADER),
    shader_program({vertex_shader, fragment_shader}) {
  GLCheckError(__FILE__, __LINE__);

  // Test
  entity.AddComponent(&mesh);
  entity.Start();

  // creation of the vertex array buffer----------------------------------------

  auto indices = mesh.GetIndices();
  auto vertices = mesh.GetVertices();

  vao = -1;
  vbo = -1;
  ibo = -1;

  // vbo
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Mesh::Vertex),
               vertices.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // ibo
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
               indices.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // vao
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // bind vbo
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  // map vbo to shader attributes
  shader_program.SetAttribute("position", 3, sizeof(Mesh::Vertex),
                              offsetof(Mesh::Vertex, position));
  shader_program.SetAttribute("normal", 3, sizeof(Mesh::Vertex),
                              offsetof(Mesh::Vertex, normal));
  shader_program.SetAttribute("color", 4, sizeof(Mesh::Vertex),
                              offsetof(Mesh::Vertex, color));

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
                 100 * 100 * 2 * 3, // count
                 GL_UNSIGNED_INT,     // type
                 nullptr                 // element array buffer offset
  );

  glBindVertexArray(0);

  ShaderProgram::Unuse();
}

Application::~Application() {

}

