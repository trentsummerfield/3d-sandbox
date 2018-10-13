#include "ShaderManager.h"

#include <fstream>
#include <iostream>
#include <sstream>

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

std::optional<GLuint>
compile_shader(std::string const& source, GLenum shader_type)
{
    auto cstr = source.c_str();
    auto shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &cstr, nullptr);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    GLint log_length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        std::string log(static_cast<size_t>(log_length), '\0');
        glGetShaderInfoLog(shader, log_length, nullptr, log.data());
        std::cerr << log << std::endl;
    }

    if (status != GL_TRUE) {
        std::cerr << "Shader compilation failed" << std::endl;
        glDeleteShader(shader);
        return {};
    }

    return shader;
}

std::optional<Shader>
load_shader_from_file(std::string const& shader_name)
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

std::optional<ShaderHandle>
ShaderManager::load_shader(std::string const& shader_name)
{
    auto shader = load_shader_from_file(shader_name);
    if (shader) {
        auto shader_ptr = std::make_shared<Shader>(std::move(shader.value()));
        ShaderHandle handle{ next_handle++ };
        shaders.emplace(handle, std::make_pair(shader_name, shader_ptr));
        return handle;
    }
    return {};
}

std::shared_ptr<Shader>
ShaderManager::get_shader(ShaderHandle handle)
{
    return shaders.at(handle).second;
}

void
ShaderManager::reload_shaders()
{
    ShaderMap map{};
    std::cout << "Reloading shaders..." << std::endl;
    for (auto& entry : shaders) {
        auto handle = entry.first;
        auto value = entry.second;
        auto shader_name = value.first;
        std::cout << "Realoading " << shader_name << std::endl;
        auto new_shader = load_shader_from_file(shader_name);
        if (new_shader) {
            auto shader_ptr =
              std::make_shared<Shader>(std::move(new_shader.value()));
            map.emplace(handle, std::make_pair(shader_name, shader_ptr));
        } else {
            map.emplace(handle, std::make_pair(shader_name, value.second));
        }
    }
    shaders = std::move(map);
}
