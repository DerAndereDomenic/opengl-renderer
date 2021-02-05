#version 330 core
#define LIGHTS 4
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 tex;
layout (location = 3) in vec3 normal;
layout (location = 4) in vec3 tangent;

//
//	VERTEX OUT
//
out vec3 frag_position;
out vec2 frag_tex;
out mat3 frag_TBN;
out vec4 frag_position_light_space[LIGHTS];

//
//	STRUCTURES
//
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
	float roughness;
	float refractive_index;
};

struct Light
{
	mat4 lightSpaceMatrix;
};

//
//	UNIFORMS
//
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform MaterialMap materialmap;
uniform Light lights_vert[LIGHTS];
uniform vec4 plane;

void main()
{
	frag_position = vec3(M*vec4(position,1));
	frag_tex = tex.xy;

	gl_ClipDistance[0] = dot(vec3(plane), frag_position) -plane.w;

	//Calculate TBN Matrix
	vec3 T = normalize(vec3(M*vec4(tangent, 0)));
	vec3 B = normalize(cross(normal, T));
	vec3 N = normalize(vec3(M*vec4(normal, 0)));
	mat3 TBN = mat3(T, B, N);

	//Displacement
	if(materialmap.useTextures)
	{
		float stretchfactor = 10.0;
		float displacement = texture(materialmap.height_map, tex.xy).r;
		frag_position += stretchfactor * displacement * N;
	}

	gl_Position = P*V*vec4(frag_position, 1);

	for(int i = 0; i < LIGHTS; ++i)
	{
		frag_position_light_space[i] = lights_vert[i].lightSpaceMatrix * vec4(frag_position, 1);
	}


	frag_TBN = TBN;
}
