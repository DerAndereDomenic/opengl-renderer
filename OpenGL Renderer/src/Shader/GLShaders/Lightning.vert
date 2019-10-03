#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 tex;
layout (location = 3) in vec3 normal;

out vec3 frag_position;
out vec4 frag_color;
out vec3 frag_normal;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main()
{
	gl_Position = P*V*M*position;
	frag_position = vec3(M*position);
	frag_color = color;
	frag_normal = normal;
}
