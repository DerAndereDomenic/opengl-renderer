#version 330 core

layout(location = 0) out vec4 FragColor;

in vec3 frag_position;
in vec3 frag_normal;

uniform vec3 camera_position;
uniform samplerCube cubemap;

void main()
{
	 vec3 I = normalize(frag_position - camera_position);
	 vec3 R = reflect(I, normalize(frag_normal));
	 FragColor = vec4(texture(cubemap, R).rgb, 1);
}