#version 330 core

out vec4 FragColor;

in vec2 texCoords;

const float PI = 3.14159265359;

float radical_inverse_VdC(uint bits) 
{
    bits = (bits << 16u) | (bits >> 16u);
    bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
    bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
    bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
    bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
    return float(bits) * 2.3283064365386963e-10; // / 0x100000000
}
// ----------------------------------------------------------------------------
vec2 hammersley(uint i, uint N)
{
    return vec2(float(i)/float(N), radical_inverse_VdC(i));
}  

vec3 importance_sample_GGX(vec2 xi, vec3 N, float roughness)
{
    float a = roughness * roughness;

    float phi = 2.0 * PI * xi.x;
    float cosTheta = sqrt((1.0 - xi.y) / (1.0 + (a*a - 1.0) * xi.y));
    float sinTheta = sqrt(1.0 - cosTheta * cosTheta);

    vec3 H;
    H.x = cos(phi) * sinTheta;
    H.y = sin(phi) * sinTheta;
    H.z = cosTheta;

    vec3 up = abs(N.z) < 0.999 ? vec3(0,0,1) : vec3(1,0,0);
    vec3 tangent = normalize(cross(up,N));
    vec3 bitangent = cross(N, tangent);

    vec3 sampleVec = tangent * H.x + bitangent * H.y + N*H.z;

    return normalize(sampleVec);
}

float V_SmithJohnGGX(float NdotL, float NdotV, float roughness)
{
	float a2 = roughness * roughness;
	float lambdaV = NdotL*sqrt(NdotV*NdotV*(1-a2)+a2);
	float lambdaL = NdotV*sqrt(NdotL*NdotL*(1-a2)+a2);
	return 0.5/(lambdaL+lambdaV);
}

vec2 integrateBRDF(float NdotV, float roughness)
{
    vec3 V;
    V.x = sqrt(1.0 - NdotV * NdotV);
    V.y = 0.0;
    V.z = NdotV;

    float A = 0.0;
    float B = 0.0;

    vec3 N = vec3(0, 0, 1);

    const uint SAMPLE_COUNT = 1024u;
    for(uint i = 0u; i < SAMPLE_COUNT; ++i)
    {
        vec2 xi = hammersley(i, SAMPLE_COUNT);
        vec3 H = importance_sample_GGX(xi, N, roughness);
        vec3 L = normalize(2.0 * dot(V,H) * H - V);

        float NdotL = max(L.z, 0.0);
        float NdotH = max(H.z, 0.0);
        float VdotH = max(dot(V,H), 0.0);

        if(NdotL > 0.0)
        {
            float G = V_SmithJohnGGX(NdotL, NdotV, roughness);
            float G_vis = (G * VdotH) / (NdotH * NdotV);
            float Fc = pow(1.0 - VdotH, 5.0);
            
            A += (1.0 - Fc) * G_vis;
            B += Fc * G_vis;
        }
    }

    A /= float(SAMPLE_COUNT);
    B /= float(SAMPLE_COUNT);

    return vec2(A,B);
}

void main()
{
	FragColor = vec4(integrateBRDF(texCoords.x, texCoords.y), 0, 1);
}