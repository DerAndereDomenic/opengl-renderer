#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec3 aTexture;

uniform mat4 V;
uniform mat4 P;

void main()
{
	gl_Position = P*V*vec4(aPosition, 1);
}