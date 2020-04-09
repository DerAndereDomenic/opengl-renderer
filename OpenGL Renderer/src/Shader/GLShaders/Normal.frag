#version 330 core
layout(location = 0) out vec4 FragColor;

in vec3 frag_position;
in vec2 frag_tex;
in mat3 frag_TBN;
in vec4 frag_position_light_space;

uniform vec3 viewPos;
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

vec3 calcPointLight(Light light, Material material, vec3 normal)
{
	//Calculate directions
	vec3 lightDir = normalize(light.position - frag_position);
	vec3 viewDir = normalize(viewPos - frag_position);
	vec3 halfwayDir = normalize(lightDir+viewDir);

	//Calculate diffuse part
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = (diff*material.diffuse)*light.diffuse;

	//Calculate specular part
	float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
	vec3 specular = (material.specular)*spec*light.specular;

	//Calculate ambient part
	vec3 ambient = light.ambient*material.ambient;

	//Calculate shadow
	float shadow = shadowCalculation(frag_position_light_space);

	//Combine light
	vec3 result = (ambient+ (1-shadow)*(diffuse+specular));

	return result;
}

void main(){

	Material object_material;

	if(useMap)
	{
		object_material.ambient = vec3(texture(materialmap.diffuse, frag_tex));
		object_material.diffuse = vec3(texture(materialmap.diffuse, frag_tex));
		object_material.specular = vec3(texture(materialmap.specular, frag_tex));
		object_material.shininess = materialmap.shininess;
	}
	else
	{
		object_material = material;
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

	vec3 result = calcPointLight(light, object_material, norm);

	FragColor = vec4(result, 1.0);

}