#version 330 core

layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

uniform mat4 P;

void main()
{
	gl_Position = P * gl_in[0].gl_Position;
	EmitVertex();
	gl_Position = P * gl_in[1].gl_Position;
	EmitVertex();

	gl_Position = P * gl_in[1].gl_Position;
	EmitVertex();
	gl_Position = P * gl_in[2].gl_Position;
	EmitVertex();

	gl_Position = P * gl_in[2].gl_Position;
	EmitVertex();
	gl_Position = P * gl_in[0].gl_Position;
	EmitVertex();

	EndPrimitive();
}