#version 330 core
layout(location = 0) out  vec4 FragColor;

in vec3 frag_tex;

uniform samplerCube skybox;

void main()
{
	FragColor = texture(skybox, frag_tex);
}