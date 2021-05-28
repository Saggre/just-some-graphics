#ifndef JUST_SOME_GRAPHICS_SRC_SHADER_HPP
#define JUST_SOME_GRAPHICS_SRC_SHADER_HPP

#include <initializer_list>
#include <map>
#include <string>
#include <mathfu/vector.h>
#include <mathfu/quaternion.h>
#include <mathfu/matrix.h>
#include <mathfu/glsl_mappings.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

class Shader;
class ShaderProgram;

class Shader {
 public:
  /**
   * Loads shader from a file
   * @param filename
   * @param type
   */
  Shader(const std::string &filename, GLenum type) {
    // file loading
    std::vector<char> file_content;
    GetFileContents(filename.c_str(), file_content);

    // creation
    handle = glCreateShader(type);
    if (handle == 0)
      throw std::runtime_error("[Error] Impossible to create a new Shader");

    // code source assignation
    const char *shaderText(&file_content[0]);
    glShaderSource(handle, 1, (const GLchar **) &shaderText, nullptr);

    // compilation
    glCompileShader(handle);

    // compilation check
    GLint compile_status;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &compile_status);
    if (compile_status != GL_TRUE) {
      GLsizei logsize = 0;
      glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logsize);

      char *log = new char[logsize + 1];
      glGetShaderInfoLog(handle, logsize, &logsize, log);

      std::cout << "[Error] compilation error: " << filename << std::endl;
      std::cout << log << std::endl;

      exit(EXIT_FAILURE);
    } else {
      std::cout << "[Info] Shader " << filename << " compiled successfully" << std::endl;
    }
  }

  static void GetFileContents(const char *filename, std::vector<char> &buffer) {
    std::ifstream file(filename, std::ios_base::binary);
    if (file) {
      file.seekg(0, std::ios_base::end);
      std::streamsize size = file.tellg();
      if (size > 0) {
        file.seekg(0, std::ios_base::beg);
        buffer.resize(static_cast<size_t>(size));
        file.read(&buffer[0], size);
      }
      buffer.push_back('\0');
    } else {
      throw std::invalid_argument(std::string("The file ") + filename + " doesn't exist");
    }
  }

  GLuint GetHandle() const {
    return handle;
  }

  ~Shader() = default;

 private:
  GLuint handle;

  friend class ShaderProgram;
};

/**
 * A shader program is a set of shader (for instance vertex shader + pixel shader)
 */
class ShaderProgram {
 public:
  ShaderProgram(std::initializer_list<Shader> shaderList) : ShaderProgram() {
    for (auto &s : shaderList) {
      glAttachShader(handle, s.GetHandle());
    }

    GetFileContents();
  }

  /**
   * Bind the program
   */
  void Use() const {
    glUseProgram(handle);
  }

  /**
   * Unbind the program
   */
  static void Unuse() {
    glUseProgram(0);
  }

  /**
   * Get handle
   * @return
   */
  GLuint GetHandle() const {
    return handle;
  }

  /**
   * Provide attribute information
   * @param name
   * @return
   */
  GLint Attribute(const std::string &name) const {
    GLint attrib = glGetAttribLocation(handle, name.c_str());
    if (attrib == GL_INVALID_OPERATION || attrib < 0) {
      std::cout << "[Error] Attribute " << name << " doesn't exist in program" << std::endl;
    }

    return attrib;
  }

  void SetAttribute(
      const std::string &name, GLint size, GLsizei stride, GLuint offset, GLboolean normalize, GLenum type
  ) const {
    GLint loc = Attribute(name);
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, size, type, normalize, stride, reinterpret_cast<void *>(offset));
  }

  void SetAttribute(
      const std::string &name, GLint size, GLsizei stride, GLuint offset, GLboolean normalize
  ) const {
    SetAttribute(name, size, stride, offset, normalize, GL_FLOAT);
  }

  void SetAttribute(
      const std::string &name, GLint size, GLsizei stride, GLuint offset, GLenum type
  ) const {
    SetAttribute(name, size, stride, offset, false, type);
  }

  void SetAttribute(const std::string &name, GLint size, GLsizei stride, GLuint offset
  ) const {
    SetAttribute(name, size, stride, offset, false, GL_FLOAT);
  }

  // Provide uniform location
  GLint Uniform(const std::string &name) {
    auto it = uniforms.find(name);
    if (it == uniforms.end()) {
      // uniform that is not referenced
      GLint r = glGetUniformLocation(handle, name.c_str());
      if (r == GL_INVALID_OPERATION || r < 0)
        std::cout << "[Error] uniform " << name << " doesn't exist in program" << std::endl;
      // add it anyways
      uniforms[name] = r;

      return r;
    } else {
      return it->second;
    }
  }

  GLint operator[](const std::string &name) {
    return 0;
  }

  // Affect uniform
  void SetUniform(const std::string &name, float x, float y, float z) {
    glUniform3f(Uniform(name), x, y, z);
  }

  void SetUniform(const std::string &name, const mathfu::vec3 &v) {
    glUniform3fv(Uniform(name), 1, &v[0]);
  }

  void SetUniform(const std::string &name, const mathfu::vec4 &v) {
    glUniform4fv(Uniform(name), 1, &v[0]);
  }

  void SetUniform(const std::string &name, const mathfu::mat4 &m) {
    glUniformMatrix4fv(Uniform(name), 1, GL_FALSE, &m[0]);
  }

  void SetUniform(const std::string &name, const mathfu::mat3 &m) {
    glUniformMatrix3fv(Uniform(name), 1, GL_FALSE, &m[0]);
  }

  void SetUniform(const std::string &name, float val) {
    glUniform1f(Uniform(name), val);
  }

  void SetUniform(const std::string &name, int val) {
    glUniform1i(Uniform(name), val);
  }

  ~ShaderProgram() = default;

 private:
  ShaderProgram() {
    handle = glCreateProgram();
    if (!handle) {
      throw std::runtime_error("Impossible to create a new shader program");
    }
  }

  std::map<std::string, GLint> uniforms;
  std::map<std::string, GLint> attributes;

  /**
   * Opengl id
   */
  GLuint handle;

  void GetFileContents() const {
    glLinkProgram(handle);
    GLint result;
    glGetProgramiv(handle, GL_LINK_STATUS, &result);
    if (result != GL_TRUE) {
      std::cout << "[Error] linkage error" << std::endl;

      GLsizei logsize = 0;
      glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &logsize);

      char *log = new char[logsize];
      glGetProgramInfoLog(handle, logsize, &logsize, log);

      std::cout << log << std::endl;
    }
  }
};

#endif
