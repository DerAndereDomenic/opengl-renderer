#version 330 core

layout (location=0) out vec4 FragColor;

in vec4 frag_clip;
in vec3 viewDir;

uniform sampler2D reflection;
uniform sampler2D refraction;

void main()
{
	vec2 ndc = (frag_clip.xy/frag_clip.w)/2.0+0.5;
	vec2 refraction_coords = ndc;
	vec2 reflection_coords = vec2(ndc.x, -ndc.y);

	vec4 reflection_color = texture(reflection, reflection_coords);
	vec4 refraction_color = texture(refraction, refraction_coords);

	FragColor = mix(reflection_color, refraction_color, 0.5);
}