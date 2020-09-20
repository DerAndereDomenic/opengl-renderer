#version 330 core 

layout (location = 0) out vec4 FragColor;

in vec3 frag_pos_model;
flat in vec3 viewPos_model;

uniform sampler3D volume;

float step_size = 0.01f;

bool insideCube(vec3 ray_pos)
{
	return ray_pos.x >= 0 && ray_pos.x <= 1 && ray_pos.y >= 0 && ray_pos.y <= 1 && ray_pos.z >= 0 && ray_pos.z <= 1;
}

float collectDensity(vec3 ray_orig, vec3 ray_dir, float step_size)
{
	float density = 0;
	while(insideCube(ray_orig))
	{
		density += texture(volume, ray_orig).r;
		ray_orig += step_size*ray_dir;
	}

	return density;
}

void main()
{
	vec3 ray_pos = frag_pos_model;

	vec3 view_dir_model = normalize(frag_pos_model - viewPos_model);

	float density = collectDensity(ray_pos, view_dir_model, step_size);

	FragColor = vec4(vec3(exp(-density)),min(density,1));
}