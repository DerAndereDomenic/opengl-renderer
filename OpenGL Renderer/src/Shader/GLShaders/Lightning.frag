#version 330 core
layout(location = 0) out vec4 FragColor;

in vec4 frag_color;

uniform sampler2D sprite;

void main(){
	FragColor = frag_color;
}