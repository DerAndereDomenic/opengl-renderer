#version 330 core

out vec4 FragColor;

in vec2 frag_tex;

uniform sampler2D screenTexture;

void main()
{
	/*const float offset = 1.0f/100.0f;

	vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );

	float kernel[9] = float[](
		1.0f/9.0f, 1.0f/9.0f, 1.0f/9.0f,
		1.0f/9.0f, 1.0f/9.0f, 1.0f/9.0f,
		1.0f/9.0f, 1.0f/9.0f, 1.0f/9.0f
	);

	vec3 sampleTex[9];
	for(int i = 0; i < 9;++i)
	{
		sampleTex[i] = vec3(texture(screenTexture, frag_tex.st + offsets[i]));
	}

	vec3 col = vec3(0.0f);
	for(int i = 0; i < 9;++i)
	{
		col += kernel[i]*sampleTex[i];
	}*/

	FragColor = texture(screenTexture, frag_tex);
}