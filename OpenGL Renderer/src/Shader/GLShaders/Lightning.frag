#version 330 core
layout(location = 0) out vec4 FragColor;

in vec4 frag_color;

uniform sampler2D sprite;
uniform vec4 lightcolor;
uniform int isLight;

float ambientStrength = 0.1;

void main(){
	if(isLight == 0)
	{
		vec3 ambient = vec3(ambientStrength * lightcolor);
		vec3 result = ambient*vec3(frag_color);

		FragColor = vec4(result, 1.0);
	}
	else
	{
		FragColor = frag_color;
	}

}