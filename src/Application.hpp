#ifndef OPENGL_CMAKE_SKELETON_MYAPPLICATION
#define OPENGL_CMAKE_SKELETON_MYAPPLICATION

#include "ApplicationCore.hpp"
#include "Shader.hpp"

class Application : public ApplicationCore {
 public:
  Application();

 protected:
  void loop() override;

 private:
  float time = 0.f;
  const int size = 100;

  Shader vertexShader;
  Shader fragmentShader;
  ShaderProgram shaderProgram;

  glm::mat4 projection = glm::mat4(1.0);
  glm::mat4 view = glm::mat4(1.0);

  GLuint vao, vbo, ibo;
};

#endif
