#include "camera.h"
#include "algebra/vec4.h"

mat4_invertable
world_to_camera_matrix(struct camera *camera)
{
    return (mat4_invertable::translate(camera->offset) *
            mat4_invertable::rotate_around_y(camera->orbit) *
            mat4_invertable::rotate_around_x(camera->pitch) *
            mat4_invertable::translate(0.f, 0.f, camera->dolly))
      .invert();
}

vec3
position(struct camera *camera)
{
    return (world_to_camera_matrix(camera).inverse_ref() * vec4(0.f, 0.f, 0.f, 1.f))
      .xyz();
}
