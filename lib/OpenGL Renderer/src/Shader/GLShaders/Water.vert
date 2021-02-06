#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 2) in vec3 tex;

uniform mat4 M,V,P;

out vec2 tex_coords;

void main()
{
	gl_Position = P*V*M*vec4(aPosition,1);
	tex_coords = tex.xy;
}