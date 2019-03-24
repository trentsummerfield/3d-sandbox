#pragma once

#include "algebra/mat4_invertable.h"
#include "algebra/vec3.h"

struct camera {
    vec3 offset;
    float pitch;
    float orbit;
    float dolly;
};

mat4_invertable world_to_camera_matrix(struct camera *);
vec3 position(struct camera *);
