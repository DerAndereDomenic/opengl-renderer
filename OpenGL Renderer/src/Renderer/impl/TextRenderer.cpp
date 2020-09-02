#include <Renderer/TextRenderer.h>
#include <iostream>

TextRenderer 
TextRenderer::createObject()
{
	TextRenderer result;

	if (FT_Init_FreeType(&result._ft))
	{
		std::cout << "ERROR::TEXTRENDERER::FREETYPE: Could not initialize FreeType Library" << std::endl;
	}

	return result;
}

void 
TextRenderer::destroyObject(TextRenderer& object)
{

}

void 
TextRenderer::loadFont(const char* path, const unsigned int number_char, const unsigned int font_size)
{

}