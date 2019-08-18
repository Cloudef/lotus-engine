#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2DArray shadowSampler;
layout(binding = 2) uniform sampler2D texSampler;

layout(binding = 3) uniform UBO
{
    vec4 cascade_splits;
    mat4 cascade_view_proj[4];
    mat4 inverse_view;
    vec3 light_dir;
} ubo;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragPos;
layout(location = 3) in vec3 normal;

layout(location = 0) out vec4 outPosition;
layout(location = 1) out vec4 outNormal;
layout(location = 2) out vec4 outAlbedo;

void main() {
    outPosition = vec4(fragPos, 1.0);
    outNormal = vec4(normal, 1.0);
    outAlbedo = texture(texSampler, fragTexCoord);
    outAlbedo.rgb *= fragColor;
    if (outAlbedo.a > 0)
        outAlbedo.a = 1;
    else
        discard;
}

