#version 330 core 

layout (location = 0) in vec3 aPosition;

out vec3 frag_pos_model;
out vec3 view_dir_model;

uniform mat4 M, V, P;
uniform vec3 viewPos;

void main()
{
	vec4 viewPos_model = inverse(M)*vec4(viewPos,1);

	frag_pos_model = aPosition + vec3(0.5);
	gl_Position = P * V * M * vec4(frag_pos_model, 1);
	view_dir_model = normalize(frag_pos_model - vec3(viewPos_model));
}