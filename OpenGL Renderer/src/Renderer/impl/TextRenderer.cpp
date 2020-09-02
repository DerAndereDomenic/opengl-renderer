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
	if (FT_New_Face(_ft, path, 0, &_face))
	{
		std::cout << "ERROR::TEXTRENDERER::FREETYPE: Could not load font at: " << path << std::endl;
	}

	FT_Set_Pixel_Sizes(_face, 0, font_size);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //disable byte-alignment restriction;
}