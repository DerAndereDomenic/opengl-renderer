#version 330 core

layout (location=0) out vec4 FragColor;

in vec2 tex_coords;

uniform sampler2D reflection;
uniform sampler2D refraction;

void main()
{
	vec4 reflection_color = texture(reflection, tex_coords);
	vec4 refraction_color = texture(refraction, tex_coords);

	FragColor = mix(reflection_color, refraction_color, 0.5);
}