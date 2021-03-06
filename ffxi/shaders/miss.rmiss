#version 460
#extension GL_NV_ray_tracing : require
#extension GL_EXT_scalar_block_layout : require

layout(location = 0) rayPayloadInNV HitValue
{
    vec3 albedo;
    vec3 light;
} hitValue;

struct Lights
{
    vec4 diffuse;
    vec4 specular;
    vec4 ambient;
    vec4 fog_color;
    float max_fog;
    float min_fog;
    float brightness;
    float _pad;
};

layout(std430, binding = 3, set = 1) uniform Light
{
    Lights entity;
    Lights landscape;
    vec3 diffuse_dir;
    float _pad;
    float skybox_altitudes1;
    float skybox_altitudes2;
    float skybox_altitudes3;
    float skybox_altitudes4;
    float skybox_altitudes5;
    float skybox_altitudes6;
    float skybox_altitudes7;
    float skybox_altitudes8;
    vec4 skybox_colors[8];
} light;

void main()
{
    float dot_up = dot(gl_WorldRayDirectionNV, vec3(0.f, -1.f, 0.f));
    hitValue.light = vec3(1.0);

    if (dot_up < light.skybox_altitudes2)
    {
        float value = (max(dot_up, 0.0) - light.skybox_altitudes1) / (light.skybox_altitudes2 - light.skybox_altitudes1);
        hitValue.albedo = mix(light.skybox_colors[0], light.skybox_colors[1], value).xyz;
        return;
    }
    if (dot_up < light.skybox_altitudes3)
    {
        float value = (max(dot_up, 0.0) - light.skybox_altitudes2) / (light.skybox_altitudes3 - light.skybox_altitudes2);
        hitValue.albedo = mix(light.skybox_colors[1], light.skybox_colors[2], value).xyz;
        return;
    }
    if (dot_up < light.skybox_altitudes4)
    {
        float value = (max(dot_up, 0.0) - light.skybox_altitudes3) / (light.skybox_altitudes4 - light.skybox_altitudes3);
        hitValue.albedo = mix(light.skybox_colors[2], light.skybox_colors[3], value).xyz;
        return;
    }
    if (dot_up < light.skybox_altitudes5)
    {
        float value = (max(dot_up, 0.0) - light.skybox_altitudes4) / (light.skybox_altitudes5 - light.skybox_altitudes4);
        hitValue.albedo = mix(light.skybox_colors[3], light.skybox_colors[4], value).xyz;
        return;
    }
    if (dot_up < light.skybox_altitudes6)
    {
        float value = (max(dot_up, 0.0) - light.skybox_altitudes5) / (light.skybox_altitudes6 - light.skybox_altitudes5);
        hitValue.albedo = mix(light.skybox_colors[4], light.skybox_colors[5], value).xyz;
        return;
    }
    if (dot_up < light.skybox_altitudes7)
    {
        float value = (max(dot_up, 0.0) - light.skybox_altitudes6) / (light.skybox_altitudes7 - light.skybox_altitudes6);
        hitValue.albedo = mix(light.skybox_colors[5], light.skybox_colors[6], value).xyz;
        return;
    }
    if (dot_up < light.skybox_altitudes8)
    {
        float value = (max(dot_up, 0.0) - light.skybox_altitudes7) / (light.skybox_altitudes8 - light.skybox_altitudes7);
        hitValue.albedo = mix(light.skybox_colors[6], light.skybox_colors[7], value).xyz;
        return;
    }
}