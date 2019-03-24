#pragma once

struct vec3 {
    float x;
    float y;
    float z;
};

struct vec3 vec3_add(struct vec3 a, struct vec3 b);
struct vec3 vec3_sub(struct vec3 a, struct vec3 b);
struct vec3 vec3_scale(struct vec3 a, float b);
