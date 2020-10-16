#version 330 core
layout (location = 0) in vec3 position;

out vec3 frag_tex;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main()
{
	frag_tex = position;
	gl_Position = P * V * M * vec4(position, 1);
}