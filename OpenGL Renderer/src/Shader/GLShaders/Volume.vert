#version 330 core 

layout (location = 0) in vec3 aPosition;
layout (location = 2) in vec3 aTex;

out vec2 frag_tex;
out vec3 frag_pos;

uniform mat4 M, V, P;

void main()
{
	frag_pos =  vec3(V * M * vec4(aPosition, 1));
	frag_tex = aTex.xy;
	gl_Position = P * vec4(frag_pos, 1);
}