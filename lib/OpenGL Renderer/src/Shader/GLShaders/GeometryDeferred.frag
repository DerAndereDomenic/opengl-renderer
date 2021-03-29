#version 330 core

layout (location=0) out vec4 gPosition;
layout (location=1) out vec4 gNormal;
layout (location=2) out vec4 gAlbedoSpec;

in vec3 frag_pos;
in vec3 frag_normal;
in vec2 frag_tex;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;

void main()
{
    gPosition = vec4(frag_pos,1);
    gNormal = vec4(normalize(frag_normal),1);
    gAlbedoSpec.rgb = texture(texture_diffuse, frag_tex).rgb;
    gAlbedoSpec.a = texture(texture_specular, frag_tex).r;
}