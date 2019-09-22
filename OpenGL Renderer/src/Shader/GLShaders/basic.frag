#version 330 core
layout(location = 0) out vec4 FragColor;

in vec4 frag_color;
in vec2 frag_tex;
flat in int frag_set;

uniform sampler2D sprite;

void main(){
	if(frag_set == 0)
	{
		FragColor = texture(sprite, frag_tex);
	}
	else
	{
		FragColor = frag_color;
	}
}