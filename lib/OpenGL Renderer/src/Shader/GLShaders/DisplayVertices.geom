#version 330 core

layout (triangles) in;
layout (points, max_vertices = 3) out;


uniform mat4 P;


void main()
{
	gl_Position = P * gl_in[0].gl_Position;

	EmitVertex();

	gl_Position = P * gl_in[1].gl_Position;

	EmitVertex();

	gl_Position = P * gl_in[2].gl_Position;

	EmitVertex();

	EndPrimitive();
}