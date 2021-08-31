#ifndef JUST_SOME_GRAPHICS_SRC_APPLICATION_HPP
#define JUST_SOME_GRAPHICS_SRC_APPLICATION_HPP

#include <cmath>
#include <memory>

#include <mathfu/matrix.h>
#include <mathfu/glsl_mappings.h>
#include <mathfu/matrix.h>
#include <mathfu/glsl_mappings.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <GL/glew.h>

#include "src/core/application_core.hpp"
#include "src/core/shader.hpp"
#include "src/core/entity.hpp"
#include "src/core/components/creative_camera.hpp"
#include "src/core/components/mesh.hpp"
#include "src/core/gl_error.hpp"
#include "src/core/entity.hpp"
#include "src/core/components/mesh.hpp"
#include "src/core/util/primitive.hpp"
#include "src/core/util/shapes.hpp"
#include "src/core/util/mappings.hpp"
#include "src/core/image.hpp"
#include "src/embed_shader.hpp"

class Application : public ApplicationCore {
 public:
  Application() : ApplicationCore() {
    vertex_shader = Shader::FromSource(shader_vert, GL_VERTEX_SHADER);
    fragment_shader = Shader::FromSource(shader_frag, GL_FRAGMENT_SHADER);
    shader_program = new ShaderProgram({vertex_shader, fragment_shader});

    //auto p = Cube();
    auto p = Sphere();
    mesh = Mesh::FromPrimitive(p);
    entity.transform_.SetPosition(mathfu::vec3(0, 0, -15));
    entity.AddComponent(&mesh); // TODO mesh component should be in another entity..
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

    glFrontFace(GL_CW);

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

    //GLuint texture = Image::LoadBMP("textures/1024.bmp");
    auto d = SDL_LoadBMP("textures/1024.bmp");
    glEnable(GL_TEXTURE_2D);

    GLuint textures;
    glGenTextures(1, &textures);
    glBindTexture(GL_TEXTURE_2D, textures);

    //glTexImage2D(GL_TEXTURE_2D, 0, 3, d->w, d->h, 0, GL_BGRA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, d->w, d->h, 0, GL_BGR, GL_UNSIGNED_BYTE, d->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // map vbo to shader attributes
    shader_program->SetAttribute("vPosition", 3, sizeof(Vertex), 0);
    shader_program->SetAttribute("vNormal", 3, sizeof(Vertex), offsetof(Vertex, normal));
    shader_program->SetAttribute("vTexCoord", 4, sizeof(Vertex), offsetof(Vertex, tex_coord));

    // bind the ibo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // vao end
    glBindVertexArray(0);

  }

  ~Application() =
  default;
 protected:
  void Loop()
  override {
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

    model = mathfu::mat4::Identity();

    //mathfu::mat4 normal = (view * model).Inverse().Transpose();

    // clear
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_program->Use();

    // Send uniforms
    shader_program->SetUniform("iTime", GetTime());
    shader_program->SetUniform("mainCameraPos", entity.transform_.GetPosition());
    shader_program->SetUniform("mProjection", projection);
    shader_program->SetUniform("mView", view);
    shader_program->SetUniform("mModel", model);
    //shader_program->SetUniform("mNormal", normal);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glDrawElements(GL_TRIANGLES, mesh.GetVertices().size() * 3, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);

    ShaderProgram::Unuse();

    //SDL_RenderPresent(renderer);
    SDL_GL_SwapWindow(window); // Update the window
  }

  void Start()
  override {
    ApplicationCore::Start();
  }

  void End()
  override {
    delete vertex_shader;
    delete fragment_shader;
    delete shader_program;

    ApplicationCore::End();
  }

 private:
  Shader *vertex_shader;
  Shader *fragment_shader;
  ShaderProgram *shader_program;

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
