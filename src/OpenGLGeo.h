#pragma once
#include <memory>
#include <vector>

#include "GL/glew.h"
#include "algebra/mat4.h"
#include "algebra/vec3.h"

class OpenGLGeo
{
  private:
    GLuint vao{ 0 };
    GLuint vbo{ 0 };
    GLuint nbo{ 0 };
    GLuint ebo{ 0 };
    vec3 center{ 0.0 };
    vec3 dimensions{ 0.0 };

    GLsizei index_count;

  public:
    OpenGLGeo(std::vector<float> vertices,
              std::vector<float> normals,
              std::vector<uint32_t> indices);
    OpenGLGeo(OpenGLGeo&) = delete;
    OpenGLGeo(OpenGLGeo&&) noexcept;
    ~OpenGLGeo();

    void draw() const;
    mat4 unit_matrix() const;
};
