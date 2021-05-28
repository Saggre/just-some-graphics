#ifndef JUST_SOME_GRAPHICS_SRC_APPLICATION_HPP
#define JUST_SOME_GRAPHICS_SRC_APPLICATION_HPP

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <mathfu/matrix.h>
#include <mathfu/glsl_mappings.h>
#include <cmath>
#include <mathfu/matrix.h>
#include <mathfu/glsl_mappings.h>
#include <src/core/components/creative_camera.hpp>

#include "src/core/application_core.hpp"
#include "src/core/shader.hpp"
#include "src/core/entity.hpp"
#include "src/core/components/mesh.hpp"
#include "src/core/gl_error.hpp"
#include "src/core/entity.hpp"
#include "src/core/components/mesh.hpp"
#include "src/core/util/primitive.hpp"
#include "src/core/util/mappings.hpp"
#include "src/core/image.hpp"
#include "src/core/util/print.hpp"

#define SHADER_DIR "../shader/"

class Application : public ApplicationCore {
 public:
  Application() : ApplicationCore(),
                  vertex_shader(SHADER_DIR "shader.vert", GL_VERTEX_SHADER),
                  fragment_shader(SHADER_DIR "shader.frag", GL_FRAGMENT_SHADER),
                  shader_program({vertex_shader, fragment_shader}) {
    // Test
    auto p = Primitive::Cube();
    mesh = Mesh::FromPrimitive(p);
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

    auto sz = sizeof(Vertex);
    auto data = vertices.data();

    // Vertex buffer
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Index buffer
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Vao
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // bind vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // map vbo to shader attributes
    shader_program.SetAttribute("position", 3, sizeof(Vertex), 0);
    shader_program.SetAttribute("normal", 3, sizeof(Vertex), offsetof(Vertex, normal));
    shader_program.SetAttribute("texCoord", 4, sizeof(Vertex), offsetof(Vertex, tex_coord));

    // bind the ibo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // vao end
    glBindVertexArray(0);

    // TODO load image
  }

  ~Application() = default;
 protected:
  void Loop() override {
    ApplicationCore::Loop();

    // TODO move
    entity.Update();

    auto d = entity.transform_.GetPosition();

    projection = mathfu::mat4::Perspective(
        M_PI * 0.25,
        GetWindowRatio(), 0.1f, 1000.f,
        1
    );

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

    //Print::pos(entity.transform_.GetPosition());

    model = mathfu::mat4::Identity();

    // clear
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_program.Use();

    // send uniforms
    shader_program.SetUniform("projection", projection);
    shader_program.SetUniform("view", view);
    shader_program.SetUniform("model", model);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glDrawElements(GL_TRIANGLE_STRIP, mesh.GetVertices().size() * 3, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);

    ShaderProgram::Unuse();

    //SDL_RenderPresent(renderer);
    SDL_GL_SwapWindow(window); // Update the window
  }

  void Start() override {
    ApplicationCore::Start();
  }

 private:
  float time = 0.f;

  Shader vertex_shader;
  Shader fragment_shader;
  ShaderProgram shader_program;

  mathfu::mat4 projection = mathfu::mat4::Identity();
  mathfu::mat4 view = mathfu::mat4::Identity();
  mathfu::mat4 model = mathfu::mat4::Identity();

  GLuint vao, vbo, ibo;

  // Test
  Entity entity;
  Mesh mesh;
  CreativeCamera creative_camera;
};

#endif
