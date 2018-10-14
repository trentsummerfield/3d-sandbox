#include "Camera.h"
#include "algebra/vec4.h"

mat4_invertable
Camera::world_to_camera_matrix() const
{
    return (mat4_invertable::translate(offset) *
            mat4_invertable::rotate_around_y(orbit) *
            mat4_invertable::rotate_around_x(pitch) *
            mat4_invertable::translate(0.f, 0.f, dolly))
      .invert();
}

vec3
Camera::position() const
{
    return (world_to_camera_matrix().inverse_ref() * vec4(0.f, 0.f, 0.f, 1.f))
      .xyz();
}
