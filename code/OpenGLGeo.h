#pragma once
#include <memory>
#include <vector>

#include "GL/glew.h"
#include "mat4.h"
#include "vec3.h"

class OpenGLGeo
{
  private:
    GLuint vao, vbo, nbo, ebo;
    GLsizei index_count;
    vec3 center;
    vec3 dimensions;

  public:
    OpenGLGeo();
    OpenGLGeo(std::vector<float> vertices,
              std::vector<float> normals,
              std::vector<uint32_t> indices);
    OpenGLGeo(OpenGLGeo&) = delete;
    OpenGLGeo(OpenGLGeo&&) noexcept;
    ~OpenGLGeo();

    void draw() const;
    mat4 unit_matrix() const;
};
