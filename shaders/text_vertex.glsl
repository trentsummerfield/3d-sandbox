#version 430 core

layout(location = 0) in vec3 position;

layout(location = 0) uniform mat4 projection;
layout(location = 2) uniform mat4 model;

void main()
{
    vec4 world_position = model * vec4(position.xy, 0.0, 1.0);
    gl_Position = projection * world_position;
}
