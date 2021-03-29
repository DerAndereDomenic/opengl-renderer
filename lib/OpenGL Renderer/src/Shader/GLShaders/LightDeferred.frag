#version 330 core

#define PI 3.14159

out vec4 FragColor;

in vec2 frag_tex;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

uniform vec3 viewPos;

vec3 lightPos = vec3(10,10,10);
float intensity = 500.0;

void main()
{
    vec3 fragPos = texture(gPosition, frag_tex).rgb;
    vec3 normal = texture(gNormal, frag_tex).rgb;
    vec4 albedoSpec = texture(gAlbedoSpec, frag_tex);
    vec3 albedo = albedoSpec.rgb;
    float specular = albedoSpec.a;

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 lightDir = normalize(lightPos - fragPos);
    float r = length(lightPos - fragPos);
    float NdotL = max(dot(normal, lightDir), 0.0);

    vec3 result = vec3(0);

    //LAMBERT
    vec3 brdf_lambert = albedo/PI;

    //PHONG
    vec3 halfDir = normalize(lightDir + viewDir);
    vec3 brdf_phong = vec3(specular) * pow(max(0,dot(halfDir, normal)), 128.0*0.4);
    result += (brdf_lambert + brdf_phong)*intensity/(r*r)*NdotL;

    //ambient
    result += albedo*0.1;

    FragColor = vec4(result, 1);
}