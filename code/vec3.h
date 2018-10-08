#pragma once
class vec3
{
  public:
    float x, y, z;

    vec3()
      : x{ 0.f }
      , y{ 0.f }
      , z{ 0.f }
    {}
    explicit vec3(float e)
      : x{ e }
      , y{ e }
      , z{ e }
    {}
    vec3(float x, float y, float z)
      : x{ x }
      , y{ y }
      , z{ z }
    {}

    vec3(vec3 const&) = default;
    vec3(vec3&&) noexcept = default;
    ~vec3() = default;

    void operator=(vec3 const& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }

    void operator+=(vec3 const& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
    }
};

inline vec3
operator+(vec3 const& a, vec3 const& b)
{
    return vec3{ a.x + b.x, a.y + b.y, a.z + b.z };
}

inline vec3
operator-(vec3 const& a, vec3 const& b)
{
    return vec3{ a.x - b.x, a.y - b.y, a.z - b.z };
}

inline vec3
operator/(vec3 const& a, float d)
{
    return vec3{ a.x / d, a.y / d, a.z / d };
}

inline vec3
operator-(vec3 const& a)
{
    return vec3{ -a.x, -a.y, -a.z };
}
