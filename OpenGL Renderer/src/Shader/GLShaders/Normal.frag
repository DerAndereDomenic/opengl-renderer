#version 330 core
layout(location = 0) out vec4 FragColor;

in vec3 frag_position;
in vec2 frag_tex;
in mat3 frag_TBN;
in vec4 frag_position_light_space;

uniform vec3 viewPos;
uniform vec4 lightcolor;
uniform bool useMap;

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
	sampler2D normal_map;
	sampler2D height_map;
	float shininess;
};

uniform MaterialMap materialmap;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material material;

uniform sampler2D shadowMap;

float shadowCalculation(vec4 fragPositionLightSpace)
{
	float bias = 0.00001;//3125;
	vec3 projCoords = fragPositionLightSpace.xyz / fragPositionLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;

	float closestDepth = texture(shadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;

	return currentDepth - bias > closestDepth ? 1.0 : 0.0;
}

void main(){

	vec3 mat_ambient;
	vec3 mat_diffuse;
	vec3 mat_specular;
	float mat_shininess;

	if(useMap)
	{
		mat_ambient = vec3(texture(materialmap.diffuse, frag_tex));
		mat_diffuse = vec3(texture(materialmap.diffuse, frag_tex));
		mat_specular = vec3(texture(materialmap.specular, frag_tex));
		mat_shininess = materialmap.shininess;
	}
	else
	{
		mat_ambient = material.ambient;
		mat_diffuse = material.diffuse;
		mat_specular = material.specular;
		mat_shininess = material.shininess;
	}


	vec3 normal = texture(materialmap.normal_map, frag_tex).rgb;
	vec3 norm;
	if(normal == 0)
	{
		norm = frag_TBN[2];
	}
	else
	{
	    norm = normalize(normal*2.0 - 1.0);
		norm = normalize(frag_TBN * norm);
	}

	vec3 lightDir = normalize(light.position - frag_position);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff*mat_diffuse)*light.diffuse;

	vec3 viewDir = normalize(viewPos - frag_position);
	//vec3 reflectDir = reflect(-lightDir, norm);
	vec3 halfwayDir = normalize(lightDir+viewDir);
	float spec = pow(max(dot(norm, halfwayDir), 0.0), materialmap.shininess);
	vec3 specular = (mat_specular)*spec*light.specular;

	vec3 ambient = light.ambient*mat_ambient;

	float shadow = shadowCalculation(frag_position_light_space);
	vec3 result = (ambient+ (1-shadow)*(diffuse+specular));

	FragColor = lightcolor*vec4(result, 1.0);

}