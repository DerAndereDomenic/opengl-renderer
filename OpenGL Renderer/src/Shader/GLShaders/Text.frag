#version 330 core 
layout(location = 0) out vec4 FragColor;

in vec2 frag_tex;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
	vec4 sampled = vec4(1.0,1.0,1.0,texture(text, frag_tex).r);
	FragColor = vec4(textColor, 1.0) * sampled;
}