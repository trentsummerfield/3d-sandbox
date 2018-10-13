#version 430 core

in vec3 v_position;
in vec3 v_normal;

out vec4 outColor;

layout(location = 1) uniform vec3 camera_position;

vec3 surface = vec3(0.80, 0.29, 0.09);
vec3 cool = vec3(0.0, 0.0, 0.55) + 0.25*surface;
vec3 warm = vec3(0.3, 0.3, 0.0) + 0.25*surface;
vec3 highlight = vec3(2, 2, 2);

vec3 light_position = vec3(0.0, 2.0, 1.0);


vec3 lit(vec3 l, vec3 n, vec3 v)
{
    vec3 r_l = reflect(-l, n);
    float s = clamp(100.0 * dot(r_l, v) - 98.0, 0.0, 1.0);
    return mix(warm, highlight, s);	
}

void main()
{
    vec3 n = normalize(v_normal);
    vec3 v = normalize(camera_position - v_position);
    outColor = vec4((0.5 * cool), 1.0);

    vec3 l = normalize(light_position - v_position);
    float NdL = clamp(dot(n, l), 0.0, 1.0);
    outColor.rgb += NdL * lit(l,n,v);
}
