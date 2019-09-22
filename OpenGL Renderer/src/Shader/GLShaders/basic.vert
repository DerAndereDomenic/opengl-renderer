#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 tex;

out vec4 frag_color;
out vec2 frag_tex;
flat out int frag_set;

uniform vec4 u_color;
uniform int u_set;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP*position;
	if(u_set == 0)
	{
		frag_color = u_color;
		frag_tex = tex;
		frag_set = u_set;
	}
	else
	{
		frag_color = color;
		frag_set = u_set;
	}
	
}
