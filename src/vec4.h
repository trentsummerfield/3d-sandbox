#pragma once
#include "vec3.h"
#include <stdexcept>
class vec4
{
  public:
    float x, y, z, w;

    vec4()
      : x{ 0.f }
      , y{ 0.f }
      , z{ 0.f }
      , w{ 0.f }
    {}
    explicit vec4(float e)
      : x{ e }
      , y{ e }
      , z{ e }
      , w{ e }
    {}
    vec4(float x, float y, float z, float w)
      : x{ x }
      , y{ y }
      , z{ z }
      , w{ w }
    {}

    vec4(vec4 const&) = default;
    vec4(vec4&&) = default;
    ~vec4() = default;

    vec3 xyz() const noexcept { return vec3{ x, y, z }; }

    float operator[](std::size_t idx) const
    {
        switch (idx) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            case 3:
                return w;
        }
        throw std::out_of_range("vec4::[]");
    }
};

inline vec4
operator+(vec4 const& a, vec4 const& b)
{
    return vec4{ a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
}

inline vec4
operator-(vec4 const& a, vec4 const& b)
{
    return vec4{ a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
}
