#version 330 core

layout (points) in;
layout (points, max_vertices=1) out;

in VS_OUT 
{
	int instance;
}gs_in[];

void main()
{
    gl_Position = gl_in[0].gl_Position + vec4(vec3(gs_in[0].instance)/100,1);
    EmitVertex();
    EndPrimitive();
}