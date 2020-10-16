#version 330 core
layout (location = 0) out vec4 FragColor;

in vec3 frag_pos;

uniform samplerCube cubemap;

void main()
{
	FragColor = texture(cubemap, frag_pos);
}