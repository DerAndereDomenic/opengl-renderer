#version 330 core

out vec4 FragColor;

in vec2 frag_tex;

uniform sampler2D leftEye;
uniform sampler2D rightEye;

void main()
{
	float u = frag_tex.x;
	float v = frag_tex.y;
	if(u <= 1.0)
	{
		FragColor = texture(leftEye, frag_tex);
	}
	else
	{
		FragColor = texture(rightEye, vec2(u-1,v));
	}
}