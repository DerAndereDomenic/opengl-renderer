#version 330 core
#define LIGHTS 4

#define LAMBERT 0
#define PHONG 1
#define GGX 2

#define PI 3.14159
layout(location = 0) out vec4 FragColor;

in vec3 frag_position;
in vec2 frag_tex;
in mat3 frag_TBN;
in vec4 frag_position_light_space[LIGHTS];

uniform vec3 viewPos;

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D shadow_map;
};

uniform Light lights_frag[LIGHTS];

struct MaterialMap
{
	bool useTextures;
	sampler2D diffuse_map;
	sampler2D specular_map;
	sampler2D normal_map;
	sampler2D height_map;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	int type;

	float shininess;
};

uniform MaterialMap materialmap;

/**
*	This is an intern struct to simplify light calculation
*/
struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};


float shadowCalculation(vec4 fragPositionLightSpace, sampler2D shadowMap)
{
	float bias = 0.0001;//3125;
	vec3 projCoords = fragPositionLightSpace.xyz / fragPositionLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;

	if(projCoords.x < 0 || projCoords.x > 1 || projCoords.y < 0 || projCoords.y > 1)
	{
		return 0;
	}

	float closestDepth = texture(shadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;

	return currentDepth - bias > closestDepth ? 1 : 0;
}

//-------------GGX---------------------------
vec3 fresnel_schlick(const vec3 F0, const float VdotH)
{
	return F0 + (1 - F0)*pow(max(0,1.0-VdotH), 5.0f);
}

float D_GGX(const float NdotH, const float roughness)
{
	float a2 = roughness * roughness;
	float d = (NdotH * a2 - NdotH) * NdotH + 1.0f;
	return a2/(PI*d*d);
}

float V_SmithJohnGGX(float NdotL, float NdotV, float roughness)
{
	float a2 = roughness * roughness;
	float lambdaV = NdotL*(NdotV*NdotV*(1-a2)+a2);
	float lambdaL = NdotV*(NdotL*NdotL*(1-a2)+a2);
	return 0.5/(lambdaL+lambdaV);
}

vec3 brdf_ggx(Light plight, vec3 lightDir, Material material, vec3 normal, int pass)
{
	vec3 viewDir = normalize(viewPos - frag_position); 

	vec3 H = normalize(lightDir + viewDir);
	float NdotH = max(0,dot(normal, H));
	float LdotH = max(0,dot(lightDir, H));
	float NdotV = dot(normal,viewDir);
	float NdotL = dot(normal, lightDir);
	if(NdotV <= 0 || NdotL <= 0)
	{
		return material.ambient;
	}
	float roughness = 0.4;
	float ndf = D_GGX(NdotH, roughness);

	float vis = V_SmithJohnGGX(NdotL, NdotV, roughness);

	float shadow = shadowCalculation(frag_position_light_space[pass], plight.shadow_map);

	return (1-shadow)*ndf*vis*fresnel_schlick(material.specular, LdotH);
}

//-------------------------------------------

vec3 brdf_lambert(Light plight, vec3 lightDir, Material material, vec3 normal, int pass)
{
	float shadow = shadowCalculation(frag_position_light_space[pass], plight.shadow_map);

	return (1-shadow)*material.diffuse/PI;
}

vec3 brdf_phong(Light plight, vec3 lightDir, Material material, vec3 normal, int pass)
{
	//Calculate directions
	vec3 viewDir = normalize(viewPos - frag_position);
	vec3 halfwayDir = normalize(lightDir+viewDir);

	float shadow = shadowCalculation(frag_position_light_space[pass], plight.shadow_map);

	return (1-shadow)*(material.specular * pow(max(0,dot(halfwayDir,normal)), material.shininess));
}

void main(){

	Material object_material;

	if(materialmap.useTextures)
	{
		object_material.ambient = vec3(texture(materialmap.diffuse_map, frag_tex));
		object_material.diffuse = vec3(texture(materialmap.diffuse_map, frag_tex));
		object_material.specular = vec3(texture(materialmap.specular_map, frag_tex));
		object_material.shininess = materialmap.shininess;
	}
	else
	{
		object_material.ambient = materialmap.ambient;
		object_material.diffuse = materialmap.diffuse;
		object_material.specular = materialmap.specular;
		object_material.shininess = materialmap.shininess;
	}


	vec3 normal = texture(materialmap.normal_map, frag_tex).rgb;
	vec3 norm;
	if(length(normal) == 0 || !materialmap.useTextures)
	{
		norm = frag_TBN[2];
	}
	else
	{
	    norm = normalize(normal*2.0 - 1.0);
		norm = normalize(frag_TBN * norm);
	}
	
	vec3 result = vec3(0);
	for(int i = 0; i < LIGHTS; ++i)
	{
		vec3 lightDir = normalize(lights_frag[i].position - frag_position);
		float r = length(lights_frag[i].position - frag_position);
		float NdotL = max(dot(norm,lightDir),0.0);
		switch(materialmap.type)
		{
			case LAMBERT:
				result += brdf_lambert(lights_frag[i], lightDir, object_material, norm, i)*lights_frag[i].diffuse/(r*r)*NdotL;
				break;
			case PHONG:
				result += brdf_phong(lights_frag[i], lightDir, object_material, norm, i)*lights_frag[i].specular/(r*r)*NdotL;
				result += brdf_lambert(lights_frag[i], lightDir, object_material, norm, i)*lights_frag[i].diffuse/(r*r)*NdotL;
				break;
			case GGX:
				result += brdf_ggx(lights_frag[i], lightDir, object_material, norm, i)*lights_frag[i].specular/(r*r)*NdotL;
				break;
		}
		result += object_material.ambient*lights_frag[i].ambient;
		
	}
	FragColor = vec4(result, 1.0);

}