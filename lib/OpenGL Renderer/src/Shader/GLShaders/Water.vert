#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 2) in vec3 tex;

uniform mat4 M,V,P;
uniform vec3 viewPos;

out vec4 frag_clip;
out vec3 viewDir;

void main()
{
	vec4 vertex_position = M*vec4(aPosition,1);
	frag_clip = P*V*vertex_position;
	gl_Position = frag_clip;
	viewDir = viewPos - vertex_position.xyz;
}