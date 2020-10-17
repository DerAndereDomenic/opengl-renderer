#version 330 core 
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 tex;

out vec2 frag_tex;

uniform mat4 projection;
uniform mat4 model;

void main()
{
	gl_Position = projection * model * vec4(position,0.1,1);
	frag_tex = tex;
}