#version 330 core 

layout (location = 0) out vec4 FragColor;

in vec2 frag_tex;

uniform sampler3D volume;
uniform float w;

void main()
{
	float density = texture(volume, vec3(frag_tex, w)).r;
	FragColor = vec4(vec3(density), 1);
}