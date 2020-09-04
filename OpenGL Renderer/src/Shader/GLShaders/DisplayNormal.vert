#version 330 core 

layout (location = 0) in vec3 aPosition;
layout (location = 3) in vec3 aNormal;

out VS_OUT 
{
	vec3 normal;
} vs_out;

uniform mat4 M;
uniform mat4 V;

void main()
{
	gl_Position = V * M * vec4(aPosition, 1.0);
	mat3 normalMatrix = mat3(transpose(inverse(V * M)));
	vs_out.normal = normalize(vec3(vec4(normalMatrix * aNormal, 0.0)));
}