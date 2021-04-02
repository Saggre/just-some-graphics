#ifndef JUST_SOME_GRAPHICS_SRC_APPLICATION_HPP
#define JUST_SOME_GRAPHICS_SRC_APPLICATION_HPP

#include "src/core/application_core.hpp"
#include "src/core/shader.hpp"

#include <mathfu/matrix.h>
#include <mathfu/glsl_mappings.h>

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

  mathfu::mat4 projection = mathfu::mat4::Identity();
  mathfu::mat4 view = mathfu::mat4::Identity();

  GLuint vao, vbo, ibo;
};

#endif
