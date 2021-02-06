#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 2) in vec3 tex;

uniform mat4 M,V,P;

out vec4 frag_clip;

void main()
{
	frag_clip = P*V*M*vec4(aPosition,1);
	gl_Position = frag_clip;
}