#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <memory>
#include <string>

Shader::Shader(GLuint program)
  : program{ program }
{}

Shader::Shader(Shader&& other) noexcept
  : program{ other.program }
{
    other.program = 0;
}

Shader::~Shader()
{
    glDeleteProgram(program);
}

void
Shader::use_program(mat4 const& projection_matrix, vec3 camera_position, float seconds_since_start)
{
    glUseProgram(program);
    glUniformMatrix4fv(0, 1, GL_TRUE, projection_matrix.as_const_ptr());
    glUniform3f(1, camera_position.x, camera_position.y, camera_position.z);
    glUniformMatrix4fv(2, 1, GL_TRUE, mat4::identity().as_const_ptr());
    glUniform1f(3, seconds_since_start);
}

void
Shader::set_model_matrix(mat4 const& model_matrix)
{
    glUniformMatrix4fv(2, 1, GL_TRUE, model_matrix.as_const_ptr());
}
