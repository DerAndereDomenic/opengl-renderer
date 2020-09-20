#version 330 core 

layout (location = 0) in vec3 aPosition;
layout (location = 2) in vec2 aTex;

out vec2 frag_tex;

void main()
{
	gl_Position = vec4(aPosition, 1);
	frag_tex = aTex;
}