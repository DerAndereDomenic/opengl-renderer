#version 330 core

out vec4 FragColor;

in vec2 frag_tex;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

uniform vec3 viewPos;

vec3 lightPos = vec3(10,10,10);

void main()
{
    vec3 fragPos = texture(gPosition, frag_tex).rgb;
    vec3 normal = texture(gNormal, frag_tex).rgb;
    vec4 albedoSpec = texture(gAlbedoSpec, frag_tex);
    vec3 albedo = albedoSpec.rgb;
    float specular = albedoSpec.a;

    vec3 ambient = albedo * 0.1;
    vec3 viewDir = normalize(viewPos - fragPos);

    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 lighting = ambient;
    lighting += max(dot(normal, lightDir), 0) * albedo;

    FragColor = vec4(lighting, 1);
}