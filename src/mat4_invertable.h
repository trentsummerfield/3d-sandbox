#pragma once

#include "mat4.h"
#include "vec3.h"

class mat4_invertable
{
  private:
    mat4 forward;
    mat4 inverse;

  public:
    mat4_invertable(mat4 forward, mat4 inverse)
      : forward{ forward }
      , inverse{ inverse }
    {}
    mat4_invertable(mat4_invertable const&) = default;
    mat4_invertable(mat4_invertable&&) = default;
    ~mat4_invertable() = default;

    const mat4& forward_ref() const { return this->forward; }

    const mat4& inverse_ref() const { return this->inverse; }

    mat4_invertable invert() const
    {
        return mat4_invertable{ this->inverse, this->forward };
    }

    static mat4_invertable identity()
    {
        return mat4_invertable{ mat4::identity(), mat4::identity() };
    }

    static mat4_invertable translate(vec3 v)
    {
        return translate(v.x, v.y, v.z);
    }

    static mat4_invertable translate(float x, float y, float z)
    {
        auto forward = mat4{ { 1.0,
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
        auto inverse = mat4{ { 1.0,
                               0.0,
                               0.0,
                               -x,
                               0.0,
                               1.0,
                               0.0,
                               -y,
                               0.0,
                               0.0,
                               1.0,
                               -z,
                               0.0,
                               0.0,
                               0.0,
                               1.0 } };
        return mat4_invertable{ forward, inverse };
    }

    static mat4_invertable rotate_around_x(float angle)
    {
        auto m = mat4::rotate_around_x(angle);
        auto inverse = m.transpose();
        return mat4_invertable{ m, inverse };
    }

    static mat4_invertable rotate_around_y(float angle)
    {
        auto m = mat4::rotate_around_y(angle);
        auto inverse = m.transpose();
        return mat4_invertable{ m, inverse };
    }

    static mat4_invertable rotate_around_z(float angle)
    {
        auto m = mat4::rotate_around_z(angle);
        auto inverse = m.transpose();
        return mat4_invertable{ m, inverse };
    }

    mat4_invertable operator*(mat4_invertable const& rhs) const
    {
        return mat4_invertable{ this->forward * rhs.forward,
                                rhs.inverse * this->inverse };
    }
};
