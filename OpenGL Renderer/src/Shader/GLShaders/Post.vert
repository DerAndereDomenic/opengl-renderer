#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec2 aTex;

out vec2 frag_tex;

void main()
{
	gl_Position = aPos;
	frag_tex = aTex;
}