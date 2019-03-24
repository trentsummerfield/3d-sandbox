#include "algebra/vec3.h"

struct vec3
vec3_add(struct vec3 a, struct vec3 b)
{
    struct vec3 result = {a.x + b.x, a.y + b.y, a.z + b.z};
    return result;
}

struct vec3
vec3_sub(struct vec3 a, struct vec3 b)
{
    struct vec3 result = {a.x - b.x, a.y - b.y, a.z - b.z};
    return result;
}

struct vec3
vec3_scale(struct vec3 a, float b)
{
    struct vec3 result = {a.x * b, a.y * b, a.z * b};
    return result;
}
