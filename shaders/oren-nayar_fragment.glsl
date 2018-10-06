#version 430 core

// Inspired by Daily: 1/3/15 by hughsk https://shadertoy.com/view/Xtl3W2

#define PI 3.14159265

in vec3 v_position;
in vec3 v_normal;

out vec4 outColor;

layout(location = 1) uniform vec3 camera_position;

vec3 surface = vec3(0.80, 0.29, 0.09);
vec3 cool = vec3(0.0, 0.0, 0.55) + 0.25*surface;
vec3 warm = vec3(0.3, 0.3, 0.0) + 0.25*surface;
vec3 highlight = vec3(2, 2, 2);

vec3 light1_position = vec3(0.0, 3.0, 3.0);
vec3 light1_color = vec3(0.97, 0.89, 0.97) * 0.8;

vec3 light2_position = vec3(-1.0, -1.0, 1.0);
vec3 light2_color = vec3(0.63, 0.76, 0.87) * 0.5;

vec3 light3_position = vec3(0.0, 10.0, 0.0);
vec3 light3_color = vec3(0.0, 0.37, 0.51);

vec3 lit(vec3 l, vec3 n, vec3 v)
{
    vec3 r_l = reflect(-l, n);
    float s = clamp(100.0 * dot(r_l, v) - 97.0, 0.0, 1.0);
    return mix(warm, highlight, s);	
}

vec3
material(vec3 pos, vec3 normal)
{
    return vec3(0.8);
}

float oren_nayar(vec3 light_dir, vec3 view_dir, vec3 normal, float roughness, float albedo)
{
    float LdotV = dot(light_dir, view_dir);
    float NdotL = dot(light_dir, normal);
    float NdotV = dot(normal, view_dir);

    float s = LdotV - NdotL * NdotL;
    float t = mix(1.0, max(NdotL, NdotV), step(0.0, s));

    float sigma2 = roughness * roughness;
    float A = 1.0 + sigma2 * (albedo / (sigma2 + 0.13) + 0.5 / (sigma2 + 0.33));
    float B = 0.45 * sigma2 / (sigma2 + 0.09);

    return albedo * max(0.0, NdotL) * (A + B * s / t) / PI;
}

void main()
{
    vec3 n = normalize(v_normal);
    vec3 v = normalize(camera_position - v_position);
    vec3 l1 = normalize(light1_position - v_position);
    vec3 l2 = normalize(light2_position - v_position);
    vec3 l3 = normalize(light3_position - v_position);

    vec3 light = vec3(0.05);
    light += light1_color * max(0.0, oren_nayar(l1, v, n, -30.1, 1.0));
    light += light2_color * max(0.0, oren_nayar(l2, v, n, -30.1, 1.0));
    light += light3_color * max(0.0, oren_nayar(l3, v, n, -30.1, 1.0));

    vec3 color = material(v_position, n) * light;

    outColor = vec4(color, 1.0);
}
