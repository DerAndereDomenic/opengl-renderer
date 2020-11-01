#version 330 core

layout (location = 0) out vec4 colorLeft;
layout (location = 1) out vec4 colorRight;

void main()
{
	colorLeft = vec4(1,0,1,1);
	colorRight = vec4(1,1,0,1);
}