#version 330 core
layout(location = 0) out vec4 FragColor;

in vec3 frag_position;
in vec4 frag_color;
in vec3 frag_normal;

uniform sampler2D sprite;
uniform vec4 lightcolor;
uniform int isLight;
uniform vec3 lightPos;

float ambientStrength = 0.1;

void main(){
	if(isLight == 0)
	{

		vec3 norm = normalize(frag_normal);
		vec3 lightDir = normalize(lightPos - frag_position);

		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff*vec3(lightcolor);

		vec3 ambient = vec3(ambientStrength * lightcolor);
		vec3 result = (ambient+diffuse)*vec3(frag_color);

		FragColor = vec4(result, 1.0);
	}
	else
	{
		FragColor = frag_color;
	}

}