#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

out vec2 texCoords;

uniform mat4 V,P;

void main()
{
	mat4 V_ = mat4(1);
	V_[3] = V[3];
	vec4 position = gl_in[0].gl_Position;
	gl_Position = P * V_ * (position + vec4(-0.01, -0.01, 0.0, 0.0));
	texCoords = vec2(0,0);
	EmitVertex();

	gl_Position = P * V_ * (position + vec4(0.01, -0.01, 0.0, 0.0));
	texCoords = vec2(1,0);
	EmitVertex();

	gl_Position = P * V_ * (position + vec4(-0.01, 0.01, 0.0, 0.0));
	texCoords = vec2(0,1);
	EmitVertex();

	gl_Position = P * V_ * (position + vec4(0.01, 0.01, 0.0, 0.0));
	texCoords = vec2(1,1);
	EmitVertex();
	EndPrimitive();
}