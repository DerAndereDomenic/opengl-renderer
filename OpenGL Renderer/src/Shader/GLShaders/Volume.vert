#version 330 core 

layout (location = 0) in vec3 aPosition;

out vec3 frag_pos_model;
out vec3 light_dir_model;
flat out vec3 viewPos_model;

uniform mat4 M, V, P;
uniform vec3 viewPos;

void main()
{
	mat4 invM = inverse(M);
	viewPos_model = vec3(invM*vec4(viewPos,1));

	frag_pos_model = aPosition + vec3(0.5);
	gl_Position = P * V * M * vec4(frag_pos_model, 1);
}