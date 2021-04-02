#ifndef JUST_SOME_GRAPHICS_SRC_SHADER_HPP
#define JUST_SOME_GRAPHICS_SRC_SHADER_HPP

#include <GL/glew.h>
#include <initializer_list>
#include <map>
#include <string>
#include <mathfu/vector.h>
#include <mathfu/quaternion.h>
#include <mathfu/matrix.h>
#include <mathfu/glsl_mappings.h>

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
 * A shader program is a set of shader (for instance vertex shader + pixel shader)
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
  void SetUniform(const std::string &name, const mathfu::vec3 &v);
  void SetUniform(const std::string &name, const mathfu::vec4 &v);
  void SetUniform(const std::string &name, const mathfu::mat4 &m);
  void SetUniform(const std::string &name, const mathfu::mat3 &m);
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
