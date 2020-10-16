#version 330 core

layout (location = 0) in vec3 position;
layout (location = 3) in vec3 normal;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform vec3 view_position;

out vec3 frag_position;
out vec3 frag_normal;

void main()
{
	frag_normal = mat3(M)*normal;
	frag_position = vec3(M*vec4(position,1));
	gl_Position = P * V * M * vec4(position,1);
}
