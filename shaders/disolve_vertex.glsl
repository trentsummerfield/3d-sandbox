#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

layout(location = 0) uniform mat4 projection;
layout(location = 2) uniform mat4 model;

out vec3 v_position;
out vec3 v_normal;

void main()
{
    vec4 world_position = vec4(position, 1.0);
    v_position = world_position.xyz;
    v_normal = (vec4(normalize(normal), 0.0)).xyz;
    gl_Position = projection * world_position;
}
