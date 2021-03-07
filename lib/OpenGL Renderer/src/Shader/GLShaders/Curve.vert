#version 330 core

out VS_OUT
{
    out int instance;
}vs_out;

void main()
{
    gl_Position = vec4(0,0,0,1);
    vs_out.instance = gl_InstanceID;
}