#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec3 aTexture;
layout (location = 3) in vec3 aNormal;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec3 frag_normal;
out vec3 frag_albedo;

void main()
{
	gl_Position = P*V*M*vec4(aPosition, 1);
	frag_normal = normalize(vec3(M*vec4(aNormal, 0)));
	frag_albedo = vec3(aColor);
}