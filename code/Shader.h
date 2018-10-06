#pragma once

#include <optional>

#include <GL/glew.h>

#include "mat4.h"

class Shader
{
  private:
    GLuint program;

  public:
    explicit Shader(GLuint program);
    Shader(Shader&&) noexcept;
    ~Shader();

    Shader(Shader&) = delete;

    void use_program(mat4 const& projection_matrix, vec3 camera_position);

    void set_model_matrix(mat4 const& model_matrix);
};

std::optional<Shader>
load_shader(std::string const& shader_name);
