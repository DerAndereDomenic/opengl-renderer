#version 330 core

layout (location = 0) out vec4 colorLeft;

in vec3 frag_normal;

void main()
{
	vec3 ambient = vec3(0.1,0.1,0.1);
	vec3 albedo = vec3(0.8,0.8,0.8);
	vec3 light_dir = normalize(vec3(0.8,1,0.5));
	vec3 light_radiance = vec3(1,1,1);

	vec3 brdf = albedo/3.14159;

	vec3 radiance = brdf*light_radiance*max(0,dot(light_dir,frag_normal));

	colorLeft = vec4(ambient + radiance,1);
}