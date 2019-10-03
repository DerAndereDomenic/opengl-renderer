#version 330 core
layout(location = 0) out vec4 FragColor;

in vec3 frag_position;
in vec4 frag_color;
in vec3 frag_normal;

uniform sampler2D sprite;
uniform vec4 lightcolor;
uniform int isLight;
uniform vec3 viewPos;
uniform vec3 lightPos;

float ambientStrength = 0.1;
float specularStrength = 0.8;

void main(){
	if(isLight == 0)
	{

		vec3 norm = normalize(frag_normal);
		vec3 lightDir = normalize(lightPos - frag_position);

		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff*vec3(lightcolor);

		vec3 viewDir = normalize(viewPos - frag_position);
		vec3 reflectDir = reflect(-lightDir, norm);

		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		vec3 specular = specularStrength*spec*vec3(lightcolor);

		vec3 ambient = vec3(ambientStrength * lightcolor);
		vec3 result = (ambient+diffuse+specular)*vec3(frag_color);

		FragColor = vec4(result, 1.0);
	}
	else
	{
		FragColor = frag_color;
	}

}