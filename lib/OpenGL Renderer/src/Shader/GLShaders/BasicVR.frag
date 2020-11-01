#version 330 core

layout (location = 0) out vec4 colorLeft;

in vec3 frag_normal;
in vec3 frag_albedo;

void main()
{
	vec3 ambient = frag_albedo/10.0;
	vec3 light_dir = normalize(vec3(0.8,1,0.5));
	vec3 light_radiance = vec3(1,1,1);

	vec3 brdf = vec3(frag_albedo)/3.14159;

	vec3 radiance = brdf*light_radiance*max(0,dot(light_dir,frag_normal));

	colorLeft = vec4(ambient + radiance,1);
}