#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec3 aTex;
layout (location = 3) in vec3 aNormal;
layout (location = 4) in vec3 aTangent;

uniform mat4 M,V,P;

out vec3 frag_pos;
out vec3 frag_normal;
out vec2 frag_tex;

void main()
{
    vec3 world_pos = vec3(M*vec4(aPosition,1));
    gl_Position = P * V * vec4(world_pos,1);

    frag_pos = world_pos;
    frag_tex = aTex.xy;
    frag_normal = M*aNormal;
}