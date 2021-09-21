#version 330 core
#define LIGHTS 4

#define LAMBERT 0
#define PHONG 1
#define GGX 2

#define PI 3.14159
layout(location = 0) out vec4 FragColor;

//
//	VERTEX IN
//
in vec3 frag_position;
in vec2 frag_tex;
in mat3 frag_TBN;
in vec4 frag_position_light_space[LIGHTS];
in vec3 frag_viewDir;

//
//	STRUCTURES
//
struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D shadow_map;
	int cast_shadow;
};

struct MaterialMap
{
	bool useDiffuseTextures;
	bool useSpecularTextures;
	bool useHeightTextures;
	bool useNormalTextures;
	bool useMetallicTextures;
	bool useRoughnessTextures;
	bool useIrradianceTextures;
	sampler2D diffuse_map;
	sampler2D specular_map;
	sampler2D normal_map;
	sampler2D height_map;
	sampler2D metallic_map;
	sampler2D roughness_map;
	samplerCube irradiance_map;
	sampler2D LUD;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	int type;

	float shininess;
	float roughness;
	float metallic;
	float refractive_index;
};

//	This is an intern struct to simplify light calculation
struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
	float roughness;
	float metallic;
};

//
//	UNIFORMS
//
uniform Light lights_frag[LIGHTS];
uniform MaterialMap materialmap;

//
//	LIGHTING FUNCTIONS
//
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
	return F0 + (1 - F0)*pow(clamp(1.0-VdotH, 0.0f, 1.0f), 5.0f);
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
	float lambdaV = NdotL*sqrt(NdotV*NdotV*(1-a2)+a2);
	float lambdaL = NdotV*sqrt(NdotL*NdotL*(1-a2)+a2);
	return 0.5/(lambdaL+lambdaV);
}

vec3 brdf_ggx(Light plight, vec3 lightDir, vec3 viewDir, Material material, vec3 F0, vec3 normal, int pass)
{
	vec3 H = normalize(lightDir + viewDir);
	float NdotH = max(0,dot(normal, H));
	float LdotH = max(0,dot(lightDir, H));
	float NdotV = dot(normal,viewDir);
	float NdotL = dot(normal, lightDir);
	if(NdotV <= 0 || NdotL <= 0)
	{
		return material.ambient;
	}
	float ndf = D_GGX(NdotH, material.roughness);

	float vis = V_SmithJohnGGX(NdotL, NdotV, material.roughness);

	float shadow = plight.cast_shadow == 1 ? shadowCalculation(frag_position_light_space[pass], plight.shadow_map) : 0;
	
	vec3 F = fresnel_schlick(F0 , LdotH);

	vec3 kD = vec3(1) - F;
	kD *= 1.0 - material.metallic;

	return (1-shadow)*(ndf*vis*F + kD * material.diffuse / PI);
}

//-------------------------------------------

vec3 brdf_lambert(Light plight, vec3 lightDir, Material material, vec3 normal, int pass)
{
	float shadow = plight.cast_shadow == 1 ? shadowCalculation(frag_position_light_space[pass], plight.shadow_map) : 0;

	return (1-shadow)*material.diffuse/PI;
}

vec3 brdf_phong(Light plight, vec3 lightDir, vec3 viewDir, Material material, vec3 normal, int pass)
{
	//Calculate directions
	vec3 halfwayDir = normalize(lightDir+viewDir);

	float shadow = plight.cast_shadow == 1 ? shadowCalculation(frag_position_light_space[pass], plight.shadow_map) : 0;

	return (1-shadow)*(material.specular * pow(max(0,dot(halfwayDir,normal)), material.shininess));
}

void main(){
	Material object_material;

	if(materialmap.useDiffuseTextures)
	{
		object_material.ambient = vec3(texture(materialmap.diffuse_map, frag_tex))/10;
		object_material.diffuse = vec3(texture(materialmap.diffuse_map, frag_tex).rgb);
	}
	else
	{
		object_material.ambient = materialmap.ambient;
		object_material.diffuse = materialmap.diffuse;
	}

	if(materialmap.useSpecularTextures)
	{
		object_material.specular = vec3(texture(materialmap.specular_map, frag_tex));
	}
	else
	{
		object_material.specular = materialmap.specular;
	}

	if(materialmap.useMetallicTextures)
	{
		object_material.metallic = texture(materialmap.metallic_map, frag_tex).r;
	}
	else
	{
		object_material.metallic = materialmap.metallic;
	}

	object_material.shininess = materialmap.shininess;

	if(materialmap.useRoughnessTextures)
	{
		object_material.roughness = texture(materialmap.roughness_map, frag_tex).r;
	}
	else
	{
		object_material.roughness = materialmap.roughness;
	}


	vec3 normal = texture(materialmap.normal_map, frag_tex).rgb;
	vec3 norm;
	if(!materialmap.useNormalTextures)
	{
		norm = frag_TBN[2];
	}
	else
	{
	    norm = normalize(normal*2.0 - 1.0);
		norm = normalize(frag_TBN * norm);
	}
	
	vec3 result = vec3(0);
	vec3 viewDir = normalize(frag_viewDir);

	vec3 F0 = vec3(0.04);
	F0 = mix(F0, object_material.diffuse, object_material.metallic);

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
				result += brdf_phong(lights_frag[i], lightDir, viewDir, object_material, norm, i)*lights_frag[i].specular/(r*r)*NdotL;
				result += brdf_lambert(lights_frag[i], lightDir, object_material, norm, i)*lights_frag[i].diffuse/(r*r)*NdotL;
				break;
			case GGX:
				
				result += brdf_ggx(lights_frag[i], lightDir, viewDir, object_material, F0, norm, i)*lights_frag[i].specular/(r*r)*NdotL;
				break;
		}
		
	}

	if(materialmap.useIrradianceTextures)
	{
		vec3 kS = fresnel_schlick(F0, max(0,dot(norm, viewDir)));
		vec3 kD = 1.0 - kS;
		kD *= 1.0 - object_material.metallic;
		vec3 irradiance = texture(materialmap.irradiance_map, norm).rgb;
		vec3 diffuse = irradiance * object_material.diffuse;
		object_material.ambient = (kD * diffuse);
	}

	result += object_material.ambient;	

	FragColor = vec4(result, 1.0);

}