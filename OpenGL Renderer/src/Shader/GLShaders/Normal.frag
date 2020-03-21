#version 330 core
layout(location = 0) out vec4 FragColor;

in vec3 frag_position;
in vec2 frag_tex;

uniform vec3 viewPos;

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;

struct MaterialMap
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

uniform MaterialMap materialmap;

void main(){

	vec3 mat_ambient = vec3(texture(materialmap.diffuse, frag_tex));
	vec3 mat_diffuse = vec3(texture(materialmap.diffuse, frag_tex));
	vec3 mat_specular = vec3(texture(materialmap.diffuse, frag_tex));
	float mat_shininess = materialmap.shininess;

	vec3 normal = texture(materialmap.specular, frag_tex).rgb;
	vec3 norm = -normalize(normal*2.0 - 1.0);
	vec3 lightDir = normalize(light.position - frag_position);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff*mat_diffuse)*light.diffuse;

	vec3 viewDir = normalize(viewPos - frag_position);
	//vec3 reflectDir = reflect(-lightDir, norm);
	vec3 halfwayDir = normalize(lightDir+viewDir);
	float spec = pow(max(dot(norm, halfwayDir), 0.0), materialmap.shininess);
	vec3 specular = (mat_specular)*spec*light.specular;

	vec3 ambient = light.ambient*mat_ambient;

	vec3 result = (ambient+diffuse+specular);

	FragColor = vec4(result, 1.0);

}