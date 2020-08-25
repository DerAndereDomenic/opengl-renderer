#version 330 core

out vec4 FragColor;

in vec2 frag_tex;

uniform sampler2D screenTexture;

void main()
{
	float exposure = 1.5;
	vec3 hdrColor = texture(screenTexture, frag_tex).rgb;

	vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);

	mapped = pow(mapped, vec3(1.0/2.2));

	FragColor = vec4(mapped,1.0);
}