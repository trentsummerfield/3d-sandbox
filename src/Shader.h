#pragma once

#include <optional>

#include <GL/glew.h>

#include "algebra/mat4.h"

class Shader
{
  private:
    GLuint program;

  public:
    explicit Shader(GLuint program);
    Shader(Shader&) = delete;
    Shader(Shader&&) noexcept;
    ~Shader();

    void use_program(mat4 const& projection_matrix, vec3 camera_position, float seconds_since_start);
    void set_model_matrix(mat4 const& model_matrix);
};
