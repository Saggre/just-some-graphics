#include "application.hpp"

#include <GLFW/glfw3.h>
#include <mathfu/vector.h>
#include <mathfu/matrix.h>
#include <mathfu/glsl_mappings.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <future>
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
  entity.transform_.SetPosition(mathfu::vec3(0, 0, -15));
  entity.AddComponent(&mesh);
  entity.AddComponent(&creative_camera);
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

void Application::Start() {
  ApplicationCore::Start();
}

void Application::Loop() {
  ApplicationCore::Loop();

  // TODO move
  entity.Update();

  auto d = entity.transform_.GetPosition();
  //std::cout << std::to_string(d.x) << ", " << std::to_string(d.y) << ", " << std::to_string(d.z) << "\n";

  // exit on window close button pressed
  if (glfwWindowShouldClose(GetWindow())) {
    Exit();
  }

  projection = mathfu::mat4::Perspective(
      M_PI * 0.25,
      GetWindowRatio(), 0.1f, 1000.f,
      1
  );

  // Dirty hack
  projection = projection * mathfu::mat4::FromScaleVector(mathfu::vec3(-1, 1, 1));

  /*float sz = 10;

  projection = mathfu::mat4::Ortho(
      sz, -sz, -sz, sz, 0.1f, 1000.f,
      1
  );*/

  view = mathfu::mat4::LookAt(
      entity.transform_.GetPosition() + entity.transform_.Forward(),
      entity.transform_.GetPosition(),
      mathfu::vec3(0, 1, 0),
      1
  );

  model = mathfu::mat4::Identity();

  // clear
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  shader_program.Use();

  // send uniforms
  shader_program.SetUniform("projection", projection);
  shader_program.SetUniform("view", view);
  shader_program.SetUniform("model", model);

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

