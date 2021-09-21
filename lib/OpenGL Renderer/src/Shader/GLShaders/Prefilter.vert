#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 V;
uniform mat4 P;

out vec3 localPos;

void main()
{
	localPos = aPos;

	mat4 rotView = mat4(mat3(V));
	vec4 clipPos = P * rotView * vec4(localPos, 1.0);

	gl_Position = clipPos.xyww;
}