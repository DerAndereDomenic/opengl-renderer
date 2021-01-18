#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aTex;

out vec2 frag_tex;

void main()
{
	gl_Position = vec4(aPos, 1);

	frag_tex = vec2(2*aTex.x, aTex.y);
}