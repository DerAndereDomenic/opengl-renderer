#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

out vec2 texCoords;

void main()
{
	vec4 position = gl_in[0].gl_Position;
	gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0);
	texCoords = vec2(0,0);
	EmitVertex();

	gl_Position = position + vec4(0.2, -0.2, 0.0, 0.0);
	texCoords = vec2(1,0);
	EmitVertex();

	gl_Position = position + vec4(-0.2, 0.2, 0.0, 0.0);
	texCoords = vec2(0,1);
	EmitVertex();

	gl_Position = position + vec4(0.2, 0.2, 0.0, 0.0);
	texCoords = vec2(1,1);
	EmitVertex();
	EndPrimitive();
}