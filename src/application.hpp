#ifndef JUST_SOME_GRAPHICS_SRC_APPLICATION_HPP
#define JUST_SOME_GRAPHICS_SRC_APPLICATION_HPP

#include "application_core.hpp"
#include "shader.hpp"

class Application : public ApplicationCore {
 public:
  Application();

 protected:
  void Loop() override;

 private:
  float time = 0.f;
  const int size = 100;

  Shader vertex_shader;
  Shader fragment_shader;
  ShaderProgram shader_program;

  glm::mat4 projection = glm::mat4(1.0);
  glm::mat4 view = glm::mat4(1.0);

  GLuint vao, vbo, ibo;
};

#endif
