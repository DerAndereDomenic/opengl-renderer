#version 330 core 

out vec4 FragColor;

in vec2 texCoords;
in vec4 color;

uniform sampler2D particle;

void main()
{
	FragColor = texture(particle, texCoords)*color;
}