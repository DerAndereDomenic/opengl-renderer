#version 330 core 

layout (location = 0) out vec4 FragColor;

in vec3 frag_pos_model;
in vec3 view_dir_model;

uniform sampler3D volume;
uniform float w;

float step_size = 0.01f;

bool insideCube(vec3 ray_pos)
{
	return ray_pos.x >= 0 && ray_pos.x <= 1 && ray_pos.y >= 0 && ray_pos.y <= 1 && ray_pos.z >= 0 && ray_pos.z <= 1;
}

void main()
{
	float density = 0;

	vec3 ray_pos = frag_pos_model;

	while(insideCube(ray_pos))
	{
		density += texture(volume, ray_pos).r;
		ray_pos += step_size*view_dir_model;
	}

	FragColor = vec4(vec3(exp(-density)),density);
}