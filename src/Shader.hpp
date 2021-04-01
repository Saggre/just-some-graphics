#ifndef OPENGL_CMAKE_SKELETON_SHADER_HPP
#define OPENGL_CMAKE_SKELETON_SHADER_HPP

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

  GLuint getHandle() const;

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
  void use() const;

  /**
   * Unbind the program
   */
  static void unuse();

  /**
   * Get handle
   * @return
   */
  GLuint getHandle() const;

  // Provide attribute information
  GLint attribute(const std::string &name) const;
  void setAttribute(const std::string &name, GLint size, GLsizei stride,
                    GLuint offset, GLboolean normalize, GLenum type) const;
  void setAttribute(const std::string &name, GLint size, GLsizei stride,
                    GLuint offset, GLboolean normalize) const;
  void setAttribute(const std::string &name, GLint size, GLsizei stride,
                    GLuint offset, GLenum type) const;
  void setAttribute(const std::string &name, GLint size, GLsizei stride,
                    GLuint offset) const;

  // Provide uniform location
  GLint uniform(const std::string &name);
  GLint operator[](const std::string &name);

  // Affect uniform
  void setUniform(const std::string &name, float x, float y, float z);
  void setUniform(const std::string &name, const glm::vec3 &v);
  void setUniform(const std::string &name, const glm::dvec3 &v);
  void setUniform(const std::string &name, const glm::vec4 &v);
  void setUniform(const std::string &name, const glm::dvec4 &v);
  void setUniform(const std::string &name, const glm::dmat4 &m);
  void setUniform(const std::string &name, const glm::mat4 &m);
  void setUniform(const std::string &name, const glm::mat3 &m);
  void setUniform(const std::string &name, float val);
  void setUniform(const std::string &name, int val);

  ~ShaderProgram();

 private:
  ShaderProgram();

  std::map<std::string, GLint> uniforms;
  std::map<std::string, GLint> attributes;

  /**
   * Opengl id
   */
  GLuint handle;

  void link() const;
};

#endif
