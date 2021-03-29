#version 330 core

layout (location=0) out vec3 gPosition;
layout (location=1) out vec3 gNormal;
layout (location=2) out vec4 gAlbedoSpec;

in vec3 frag_pos;
in vec3 frag_normal;
in vec2 frag_tex;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;

void main()
{
    gPosition = frag_pos;
    gNormal = normalize(frag_normal);
    gAlbedoSpec.rgb = texture(texture_diffuse, frag_tex).rgb;
    gAlbedoSpec.a = texture(texture_specular, frag_tex).r;
}