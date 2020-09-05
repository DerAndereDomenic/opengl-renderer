#version 330 core 

layout (location = 0) in vec3 aPosition;
layout (location = 1) in float aTimeAlive;

out VS_OUT 
{
	out float timeAlive;
} vs_out;

void main()
{
	gl_Position = vec4(aPosition,1);
	vs_out.timeAlive = aTimeAlive;
}