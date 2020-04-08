#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 tex;
layout (location = 3) in vec3 normal;
layout (location = 4) in vec3 tangent;

out vec3 frag_position;
out vec2 frag_tex;
out mat3 frag_TBN;
out vec4 frag_position_light_space;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat4 lightSpaceMatrix;

struct MaterialMap
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D normal_map;
	sampler2D height_map;
	float shininess;
};

uniform MaterialMap materialmap;

void main()
{
	frag_position = vec3(M*vec4(position,1));
	frag_tex = tex;

	//Calculate TBN Matrix
	vec3 T = normalize(vec3(M*vec4(tangent, 0)));
	vec3 B = normalize(cross(normal, T));
	vec3 N = normalize(vec3(M*vec4(normal, 0)));
	mat3 TBN = mat3(T, B, N);

	//Displacement
	float stretchfactor = 0.1;
	float displacement = texture(materialmap.height_map, tex).r;
	frag_position += stretchfactor * displacement * N;

	gl_Position = P*V*vec4(frag_position, 1);

	frag_position_light_space = lightSpaceMatrix * vec4(frag_position, 1);

	frag_TBN = TBN;
}
