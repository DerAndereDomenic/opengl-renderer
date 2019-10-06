#version 330 core
layout(location = 0) out vec4 FragColor;

in vec3 frag_position;
in vec4 frag_color;
in vec2 frag_tex;
in vec3 frag_normal;

uniform bool isLight;
uniform bool useMap;
uniform vec3 viewPos;

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material material;

struct MaterialMap
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

uniform MaterialMap materialmap;

void main(){
	if(!isLight)
	{
		vec3 mat_ambient = material.ambient;
		vec3 mat_diffuse = material.diffuse;
		vec3 mat_specular = material.specular;
		float mat_shininess = material.shininess;

		vec3 norm = normalize(frag_normal);
		vec3 lightDir = normalize(light.position - frag_position);

		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = (diff*mat_diffuse)*light.diffuse;

		vec3 viewDir = normalize(viewPos - frag_position);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = (mat_specular)*spec*light.specular;

		vec3 ambient = light.ambient*mat_ambient;

		vec3 result = (ambient+diffuse+specular);

		FragColor = vec4(result, 1.0);
	}
	else
	{
		FragColor = frag_color;
	}

}