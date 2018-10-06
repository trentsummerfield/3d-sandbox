#pragma once

#include <array>
#include <cmath>

#include "vec4.h"

class mat4
{
  private:
    std::array<float, 16> data;

  public:
    explicit mat4(std::array<float, 16> data)
      : data{ data }
    {}
    mat4(mat4 const&) = default;
    mat4(mat4&&) = default;
    ~mat4() = default;

    float* as_ptr() { return this->data.data(); }

    float const* as_const_ptr() const { return this->data.data(); }

    float operator[](std::size_t idx) const { return this->data[idx]; }

    mat4 transpose() const
    {
        return mat4{ { data[0],
                       data[4],
                       data[8],
                       data[12],
                       data[1],
                       data[5],
                       data[9],
                       data[13],
                       data[2],
                       data[6],
                       data[10],
                       data[14],
                       data[3],
                       data[7],
                       data[11],
                       data[15] } };
    }

    static mat4 identity()
    {
        return mat4{ { 1.0,
                       0.0,
                       0.0,
                       0.0,
                       0.0,
                       1.0,
                       0.0,
                       0.0,
                       0.0,
                       0.0,
                       1.0,
                       0.0,
                       0.0,
                       0.0,
                       0.0,
                       1.0 } };
    }

    static mat4 perspective(float fovy_radians,
                            float aspect,
                            float near,
                            float far)
    {
        float f = 1.f / tanf(fovy_radians / 2.f);
        float nf = near - far;
        return mat4{ { f / aspect,
                       0.0,
                       0.0,
                       0.0,
                       0.0,
                       f,
                       0.0,
                       0.0,
                       0.0,
                       0.0,
                       (far + near) / nf,
                       (2.f * far * near) / nf,
                       0.0,
                       0.0,
                       -1.0,
                       0.0 } };
    }

    static mat4 translate(vec3 v) { return translate(v.x, v.y, v.z); }

    static mat4 translate(float x, float y, float z)
    {
        return mat4{ { 1.0,
                       0.0,
                       0.0,
                       x,
                       0.0,
                       1.0,
                       0.0,
                       y,
                       0.0,
                       0.0,
                       1.0,
                       z,
                       0.0,
                       0.0,
                       0.0,
                       1.0 } };
    }

    static mat4 scale(float s)
    {
        return mat4{ { s,
                       0.0,
                       0.0,
                       0.0,
                       0.0,
                       s,
                       0.0,
                       0.0,
                       0.0,
                       0.0,
                       s,
                       0.0,
                       0.0,
                       0.0,
                       0.0,
                       1.0 } };
    }

    static mat4 rotate_around_x(float angle)
    {
        return mat4{ { 1.f,
                       0.f,
                       0.f,
                       0.f,
                       0.f,
                       cosf(angle),
                       -sinf(angle),
                       0.f,
                       0.f,
                       sinf(angle),
                       cosf(angle),
                       0.f,
                       0.f,
                       0.f,
                       0.f,
                       1.f } };
    }

    static mat4 rotate_around_y(float angle)
    {
        return mat4{ { cosf(angle),
                       0.f,
                       sinf(angle),
                       0.f,
                       0.f,
                       1.f,
                       0.f,
                       0.f,
                       -sinf(angle),
                       0.f,
                       cosf(angle),
                       0.f,
                       0.f,
                       0.f,
                       0.f,
                       1.f } };
    }

    static mat4 rotate_around_z(float angle)
    {
        return mat4{ { cosf(angle),
                       -sinf(angle),
                       0.f,
                       0.f,
                       sinf(angle),
                       cosf(angle),
                       0.f,
                       0.f,
                       0.f,
                       0.f,
                       1.f,
                       0.f,
                       0.f,
                       0.f,
                       0.f,
                       1.f } };
    }
};

inline mat4 operator*(mat4 const& a, mat4 const& b)
{
    return mat4{ {
      a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12],
      a[0] * b[1] + a[1] * b[5] + a[2] * b[9] + a[3] * b[13],
      a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14],
      a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15],

      a[4] * b[0] + a[5] * b[4] + a[6] * b[8] + a[7] * b[12],
      a[4] * b[1] + a[5] * b[5] + a[6] * b[9] + a[7] * b[13],
      a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14],
      a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15],

      a[8] * b[0] + a[9] * b[4] + a[10] * b[8] + a[11] * b[12],
      a[8] * b[1] + a[9] * b[5] + a[10] * b[9] + a[11] * b[13],
      a[8] * b[2] + a[9] * b[6] + a[10] * b[10] + a[11] * b[14],
      a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11] * b[15],

      a[12] * b[0] + a[13] * b[4] + a[14] * b[8] + a[15] * b[12],
      a[12] * b[1] + a[13] * b[5] + a[14] * b[9] + a[15] * b[13],
      a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14],
      a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15],
    } };
}

inline vec4 operator*(mat4 const& a, vec4 const& b)
{
    return vec4{
        a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3],
        a[4] * b[0] + a[5] * b[1] + a[6] * b[2] + a[7] * b[3],
        a[8] * b[0] + a[9] * b[1] + a[10] * b[2] + a[11] * b[3],
        a[12] * b[0] + a[13] * b[1] + a[14] * b[2] + a[15] * b[3],
    };
}

inline float
degrees_to_radians(float degrees)
{
    return (degrees * (float)M_PI) / 180.f;
}