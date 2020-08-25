#version 330 core

out vec4 FragColor;

in vec2 frag_tex;

uniform sampler2D screenTexture;

void main()
{
	FragColor = texture(screenTexture, frag_tex);
	FragColor.rgb = pow(FragColor.rgb, vec3(1.0/2.2));
}