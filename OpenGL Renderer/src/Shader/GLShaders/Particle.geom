#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

out vec2 texCoords;
out vec4 color;

in VS_OUT 
{
	vec4 color;
}gs_in[];

uniform mat4 V,P;

void main()
{
	vec4 position = gl_in[0].gl_Position;
	gl_Position = P * V * position + vec4(-0.01, -0.01, 0.0, 0.0);
	texCoords = vec2(0,0);
	color = gs_in[0].color;
	EmitVertex();

	gl_Position = P * V * position + vec4(0.01, -0.01, 0.0, 0.0);
	texCoords = vec2(1,0);
	color = gs_in[0].color;
	EmitVertex();

	gl_Position = P * V * position + vec4(-0.01, 0.01, 0.0, 0.0);
	texCoords = vec2(0,1);
	color = gs_in[0].color;
	EmitVertex();

	gl_Position = P * V * position + vec4(0.01, 0.01, 0.0, 0.0);
	texCoords = vec2(1,1);
	color = gs_in[0].color;
	EmitVertex();
	EndPrimitive();
}