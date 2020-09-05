#version 330 core 

out vec4 FragColor;

in vec2 texCoords;
in vec3 color;

uniform sampler2D particle;

void main()
{
	FragColor = texture(particle, texCoords)*vec4(color,1);
}