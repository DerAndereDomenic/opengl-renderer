#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 tex;

out vec2 texCoords;

void main()
{
	texCoords = tex.xy;
	gl_Position = vec4(aPos, 1.0);
}