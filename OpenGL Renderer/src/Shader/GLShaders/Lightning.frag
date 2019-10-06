#version 330 core
layout(location = 0) out vec4 FragColor;

in vec3 frag_position;
in vec4 frag_color;
in vec2 frag_tex;
in vec3 frag_normal;

uniform bool isLight;
uniform vec3 viewPos;

struct Light{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material material;

void main(){
	if(!isLight)
	{

		vec3 norm = normalize(frag_normal);
		vec3 lightDir = normalize(light.position - frag_position);

		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = (diff*material.diffuse)*light.diffuse;

		vec3 viewDir = normalize(viewPos - frag_position);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = (material.specular)*spec*light.specular;

		vec3 ambient = light.ambient*material.ambient;

		vec3 result = (ambient+diffuse+specular);

		FragColor = vec4(result, 1.0);
	}
	else
	{
		FragColor = frag_color;
	}

}