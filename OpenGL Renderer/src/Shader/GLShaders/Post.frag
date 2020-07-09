#version 330 core

out vec4 FragColor;

in vec2 frag_tex;

uniform sampler2D screenTexture;
uniform sampler2D lightTexture;

void main()
{
	vec2 offset = 2.0 / textureSize(lightTexture, 0);

	vec2 offsets[9] = vec2[](
        vec2(-offset.s,  offset.t), // top-left
        vec2( 0.0f,    offset.t), // top-center
        vec2( offset.s,  offset.t), // top-right
        vec2(-offset.s,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset.s,  0.0f),   // center-right
        vec2(-offset.s, -offset.t), // bottom-left
        vec2( 0.0f,   -offset.t), // bottom-center
        vec2( offset.s, -offset.t)  // bottom-right    
    );

	float kernel[9] = float[](
		1, 2, 1,
		2, 4, 2,
		1, 2, 1
	);

	vec3 sampleTex[9];
	for(int i = 0; i < 9;++i)
	{
		sampleTex[i] = vec3(texture(lightTexture, frag_tex.st + offsets[i]));
	}

	vec3 col = vec3(0.0f);
	for(int i = 0; i < 9;++i)
	{
		col += kernel[i]*sampleTex[i];
	}
	
	FragColor = texture(screenTexture,frag_tex);
	//FragColor = vec4(1.0/16.0*col,1) + texture(screenTexture, frag_tex);
	//FragColor.rgb = pow(FragColor.rgb, vec3(1.0/2.2));
}