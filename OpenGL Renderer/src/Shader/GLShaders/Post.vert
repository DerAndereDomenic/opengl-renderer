#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 normal;

out vec2 frag_tex;

void main()
{
	gl_Position = vec4(aPos, 1);
	frag_tex = aTex;
}