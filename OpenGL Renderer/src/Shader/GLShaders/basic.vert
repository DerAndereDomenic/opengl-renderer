#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

out vec4 frag_color;

uniform vec4 u_color;
uniform int u_set;

void main()
{
	gl_Position = position;
	if(u_set == 0)
	{
		frag_color = u_color;
	}
	else
	{
		frag_color = color;
	}
	
}
