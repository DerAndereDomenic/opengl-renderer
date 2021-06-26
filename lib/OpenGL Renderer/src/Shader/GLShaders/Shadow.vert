#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec3 tex;
layout (location = 3) in vec3 normal;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

struct MaterialMap
{
	bool useHeightTextures;
	sampler2D height_map;
};

uniform MaterialMap materialmap;

void main()
{
	vec3 frag_position = (M*vec4(position,1)).xyz;
	vec3 N = normalize(vec3(M*vec4(normal, 0)));

	if(materialmap.useHeightTextures)
	{
		float displacement = texture(materialmap.height_map, tex.xy).r;
		frag_position += 10* displacement * N;
	}

	gl_Position = P * V * vec4(frag_position,1);
}