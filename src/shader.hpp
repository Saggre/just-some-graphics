#ifndef JUST_SOME_GRAPHICS_SRC_SHADER_HPP
#define JUST_SOME_GRAPHICS_SRC_SHADER_HPP

#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <initializer_list>
#include <map>
#include <string>

class Shader;
class ShaderProgram;

class Shader {
 public:
  /**
   * Loads shader from a file
   * @param filename
   * @param type
   */
  Shader(const std::string &filename, GLenum type);

  GLuint GetHandle() const;

  ~Shader();

 private:
  GLuint handle;

  friend class ShaderProgram;
};

/**
 * A shader program is a set of shader (for instance vertex shader + pixel
 * shader) defining the rendering pipeline. This class provide an interface to
 * define the OpenGL uniforms and attributes using GLM objects.
 */
class ShaderProgram {
 public:
  ShaderProgram(std::initializer_list<Shader> shaderList);

  /**
   * Bind the program
   */
  void Use() const;

  /**
   * Unbind the program
   */
  static void Unuse();

  /**
   * Get handle
   * @return
   */
  GLuint GetHandle() const;

  // Provide attribute information
  GLint Attribute(const std::string &name) const;
  void SetAttribute(const std::string &name, GLint size, GLsizei stride,
                    GLuint offset, GLboolean normalize, GLenum type) const;
  void SetAttribute(const std::string &name, GLint size, GLsizei stride,
                    GLuint offset, GLboolean normalize) const;
  void SetAttribute(const std::string &name, GLint size, GLsizei stride,
                    GLuint offset, GLenum type) const;
  void SetAttribute(const std::string &name, GLint size, GLsizei stride,
                    GLuint offset) const;

  // Provide uniform location
  GLint Uniform(const std::string &name);
  GLint operator[](const std::string &name);

  // Affect uniform
  void SetUniform(const std::string &name, float x, float y, float z);
  void SetUniform(const std::string &name, const glm::vec3 &v);
  void SetUniform(const std::string &name, const glm::dvec3 &v);
  void SetUniform(const std::string &name, const glm::vec4 &v);
  void SetUniform(const std::string &name, const glm::dvec4 &v);
  void SetUniform(const std::string &name, const glm::dmat4 &m);
  void SetUniform(const std::string &name, const glm::mat4 &m);
  void SetUniform(const std::string &name, const glm::mat3 &m);
  void SetUniform(const std::string &name, float val);
  void SetUniform(const std::string &name, int val);

  ~ShaderProgram();

 private:
  ShaderProgram();

  std::map<std::string, GLint> uniforms;
  std::map<std::string, GLint> attributes;

  /**
   * Opengl id
   */
  GLuint handle;

  void GetFileContents() const;
};

#endif
