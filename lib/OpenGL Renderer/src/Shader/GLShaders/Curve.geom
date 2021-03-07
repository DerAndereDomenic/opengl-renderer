#version 330 core

layout (points) in;
layout (line_strip, max_vertices=2) out;

in VS_OUT 
{
	int instance;
    vec3 points[4];
}gs_in[];

vec3 lagrange(float u)
{
    float t[4]; //knots
    t[0] = 0.0;
    t[1] = 1.0/3.0;
    t[2] = 2.0/3.0;
    t[3] = 1.0;
    float L0 = ((u-t[1])*(u-t[2])*(u-t[3]))/((t[0]-t[1])*(t[0]-t[2])*(t[0]-t[3]));
    float L1 = ((u-t[0])*(u-t[2])*(u-t[3]))/((t[1]-t[0])*(t[1]-t[2])*(t[1]-t[3]));
    float L2 = ((u-t[0])*(u-t[1])*(u-t[3]))/((t[2]-t[0])*(t[2]-t[1])*(t[2]-t[3]));
    float L3 = ((u-t[0])*(u-t[1])*(u-t[2]))/((t[3]-t[0])*(t[3]-t[1])*(t[3]-t[2]));

    return L0*gs_in[0].points[0]+L1*gs_in[0].points[1]+L2*gs_in[0].points[2]+L3*gs_in[0].points[3];
}

vec3 bezier(float u)
{
    float B0 = (1.-u)*(1.-u)*(1.-u);
    float B1 = 3.*u*(1.-u)*(1.-u);
    float B2 = 3.*u*u*(1.-u);
    float B3 = u*u*u;

    return B0*gs_in[0].points[0]+B1*gs_in[0].points[1]+B2*gs_in[0].points[2]+B3*gs_in[0].points[3];
}

uniform int discretization;
uniform int render_bezier;

void main()
{
    if(render_bezier == 1)
    {
        gl_Position = vec4(bezier(gs_in[0].instance/float(discretization)),1);
        EmitVertex();
        gl_Position = vec4(bezier((gs_in[0].instance+1)/float(discretization)),1);
        EmitVertex();
        EndPrimitive();
    }
    else
    {
        gl_Position = vec4(lagrange(gs_in[0].instance/float(discretization)),1);
        EmitVertex();
        gl_Position = vec4(lagrange((gs_in[0].instance+1)/float(discretization)),1);
        EmitVertex();
        EndPrimitive();
    }
    
}