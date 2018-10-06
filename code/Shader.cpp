#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <memory>
#include <string>

Shader::Shader(GLuint program)
  : program(program)
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
Shader::use_program(mat4 const& projection_matrix, vec3 camera_position)
{
    glUseProgram(program);
    glUniformMatrix4fv(0, 1, GL_TRUE, projection_matrix.as_const_ptr());
    glUniform3f(1, camera_position.x, camera_position.y, camera_position.z);
    glUniformMatrix4fv(2, 1, GL_TRUE, mat4::identity().as_const_ptr());
}

void
Shader::set_model_matrix(mat4 const& model_matrix)
{
    glUniformMatrix4fv(2, 1, GL_TRUE, model_matrix.as_const_ptr());
}

std::optional<GLuint>
compile_shader(std::string const& source, GLenum shader_type)
{
    auto cstr = source.c_str();
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &cstr, nullptr);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    GLint log_length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        std::string log(static_cast<size_t>(log_length), '\0');
        glGetShaderInfoLog(shader, log_length, nullptr, log.data());
        std::cout << log << std::endl;
    }

    if (status != GL_TRUE) {
        std::cout << "Shader compilation failed" << std::endl;
        glDeleteShader(shader);
        return {};
    }

    return shader;
}

std::string
file_to_string(std::string const& filename)
{
    std::stringstream str;
    std::ifstream file{ filename };
    if (file.is_open()) {
        str << file.rdbuf();
    } else {
        std::cerr << "Could not open " << filename << std::endl;
    }
    return str.str();
}

std::optional<Shader>
load_shader(std::string const& shader_name)
{
    auto vertex_source =
      file_to_string("shaders/" + shader_name + "_vertex.glsl");
    if (vertex_source.empty()) {
        return {};
    }
    auto fragment_source =
      file_to_string("shaders/" + shader_name + "_fragment.glsl");
    if (fragment_source.empty()) {
        return {};
    }

    auto vertex_shader = compile_shader(vertex_source, GL_VERTEX_SHADER);
    auto fragment_shader = compile_shader(fragment_source, GL_FRAGMENT_SHADER);

    if (!vertex_shader || !fragment_shader) {
        return {};
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex_shader.value());
    glAttachShader(shaderProgram, fragment_shader.value());
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);

    glDeleteShader(vertex_shader.value());
    glDeleteShader(fragment_shader.value());

    return std::make_optional<Shader>(shaderProgram);
}
