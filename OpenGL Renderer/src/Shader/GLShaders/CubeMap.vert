#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform vec3 center_position;

out vec3 frag_pos;

void main()
{
	gl_Position = P * V * M * vec4(position, 1);
	frag_pos = vec3(M*(vec4(position-center_position ,1)));
}