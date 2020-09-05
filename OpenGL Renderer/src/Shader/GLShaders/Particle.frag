#version 330 core 

out vec4 FragColor;

in vec2 texCoords;
in float timeAlive;

uniform sampler2D particle;

void main()
{
	FragColor = texture(particle, texCoords)*vec4(vec3(1),timeAlive);
}