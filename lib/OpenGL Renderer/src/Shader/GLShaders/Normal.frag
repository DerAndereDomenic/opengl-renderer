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
	bool useIBLTextures;
	sampler2D diffuse_map;
	sampler2D specular_map;
	sampler2D normal_map;
	sampler2D height_map;
	sampler2D metallic_map;
	sampler2D roughness_map;
	samplerCube irradiance_map;
	samplerCube prefilter_map;
	sampler2D LUT;

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

vec3 fresnel_schlick_roughness(const vec3 F0, const float VdotH, float roughness)
{
	return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(clamp(1.0 - VdotH, 0.0, 1.0), 5.0);
}

/*float D_GGX(const float NdotH, const float roughness)
{
	float a2 = roughness * roughness;
	float d = (NdotH * a2 - NdotH) * NdotH + 1.0f;
	return a2/(PI*d*d);
}*/

/*float V_SmithJohnGGX(float NdotL, float NdotV, float roughness)
{
	float a2 = roughness * roughness;
	float lambdaV = NdotL*sqrt(NdotV*NdotV*(1-a2)+a2);
	float lambdaL = NdotV*sqrt(NdotL*NdotL*(1-a2)+a2);
	return 0.5/(lambdaL+lambdaV);
}*/

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
	float a = roughness * roughness;
	float a2 = a * a;
	float NdotH = max(dot(N,H), 0.0);
	float NdotH2 = NdotH * NdotH;

	float nom = a2;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = PI * denom * denom;

	return nom/denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
	float r = (roughness + 1.0);
	float k = (r*r)/8.0;

	float nom = NdotV;
	float denom = NdotV * (1.0 - k) + k;

	return nom/denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
	float NdotV = max(dot(N,V), 0.0);
	float NdotL = max(dot(N,L), 0.0);
	float ggx2 = GeometrySchlickGGX(NdotV, roughness);
	float ggx1 = GeometrySchlickGGX(NdotL, roughness);

	return ggx1 * ggx2;
}

vec3 brdf_ggx(Light plight, vec3 lightDir, vec3 viewDir, Material material, vec3 F0, vec3 normal, int pass)
{
	/*vec3 H = normalize(lightDir + viewDir);
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
	kD *= 1.0 - material.metallic;*/

	vec3 H = normalize(lightDir + viewDir);

	float NDF = DistributionGGX(normal, H, material.roughness);
	float G = GeometrySmith(normal, viewDir, lightDir, material.roughness);
	vec3 F = fresnel_schlick(F0, max(dot(H,viewDir), 0.0));

	vec3 numerator = NDF * G * F;
	float denominator = 4.0 * max(dot(normal,viewDir), 0.0) * max(dot(normal,lightDir), 0.0) + 0.0001;
	vec3 specular = numerator/denominator;

	vec3 kS = F;
	vec3 kD = vec3(1.0) - kS;
	kD *= 1.0 - material.metallic;

	float shadow = plight.cast_shadow == 1 ? shadowCalculation(frag_position_light_space[pass], plight.shadow_map) : 0;
	return (1-shadow)*(specular + kD * material.diffuse / PI);
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
	vec3 R = reflect(-viewDir, norm);

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

	if(materialmap.useIBLTextures)
	{
		vec3 F = fresnel_schlick_roughness(F0, max(dot(norm,viewDir), 0), object_material.roughness);

		vec3 kS = F;
		vec3 kD = 1.0 - kS;
		kD *= 1.0 - object_material.metallic;

		vec3 irradiance = texture(materialmap.irradiance_map, norm).rgb;
		vec3 diffuse = irradiance * object_material.diffuse;

		const float MAX_REFLECTION_LOD = 4.0;
		vec3 prefilteredColor = textureLod(materialmap.prefilter_map, R, object_material.roughness * MAX_REFLECTION_LOD).rgb;
		vec2 brdf = textureLod(materialmap.LUT, vec2(max(dot(norm,viewDir), 0.0), object_material.roughness), 0).rg;
		vec3 specular = prefilteredColor * (F * brdf.x + brdf.y);

		object_material.ambient = (kD * diffuse + specular);
	}

	result += object_material.ambient;

	FragColor = vec4(result, 1.0);

}