#include "OpenGLGeo.h"

#include <algorithm>
#include <iostream>

OpenGLGeo::OpenGLGeo(std::vector<float> vertices,
                     std::vector<float> normals,
                     std::vector<uint32_t> indices)
  : index_count(indices.size())
{
    vec3 max{ std::numeric_limits<float>::lowest() };
    vec3 min{ std::numeric_limits<float>::max() };
    for (int i = 0; i < vertices.size() / 3; i++) {
        float x = vertices[i];
        float y = vertices[i + 1];
        float z = vertices[i + 2];

        min.x = std::min(min.x, x);
        max.x = std::max(max.x, x);

        min.y = std::min(min.y, y);
        max.y = std::max(max.y, y);

        min.z = std::min(min.z, z);
        max.z = std::max(max.z, z);
    }

    center = (max + min) / 2.f;
    dimensions = max - min;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 vertices.size() * sizeof(vertices[0]),
                 vertices.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    if (!normals.empty()) {
        glGenBuffers(1, &nbo);
        glBindBuffer(GL_ARRAY_BUFFER, nbo);
        glBufferData(GL_ARRAY_BUFFER,
                     normals.size() * sizeof(normals[0]),
                     normals.data(),
                     GL_STATIC_DRAW);
    }

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indices.size() * sizeof(indices[0]),
                 indices.data(),
                 GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

OpenGLGeo::OpenGLGeo(OpenGLGeo&& other) noexcept
  : vao(other.vao)
  , vbo(other.vbo)
  , nbo(other.nbo)
  , ebo(other.ebo)
  , center(std::move(other.center))
  , dimensions(std::move(other.dimensions))
  , index_count(other.index_count)
{
    other.vao = 0;
    other.vbo = 0;
    other.nbo = 0;
    other.ebo = 0;
    other.index_count = 0;
    other.center = vec3{ 0.f };
    other.dimensions = vec3{ 0.f };
}

OpenGLGeo::~OpenGLGeo()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &nbo);
    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vao);
}

void
OpenGLGeo::draw() const
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

mat4
OpenGLGeo::unit_matrix() const
{
    float scale = 1.f / std::max({ dimensions.x, dimensions.y, dimensions.z });
    return mat4::scale(scale) * mat4::translate(-center);
}
