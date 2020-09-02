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
	if (object._loaded)
	{
		for (unsigned int i = 0; i < object._characters.size(); ++i)
		{
			Character character = object._characters[i];
			Texture::destroyObject(character.texture);
		}
		object._characters.clear();
		object._loaded = false;
	}
	else
	{
		FT_Done_Face(object._face);
		FT_Done_FreeType(object._ft);
	}
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

	for (unsigned char c = 0; c < number_char; ++c)
	{
		//Load character glyph
		if (FT_Load_Char(_face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::TEXTRENDERER::FREETYPE: Could not load Glyph: " << c << std::endl;
		}

		Character character;
		character.texture = Texture::createObject(_face->glyph->bitmap.width,
												  _face->glyph->bitmap.rows,
												  _face->glyph->bitmap.buffer,
												  TEXTURE,
												  GL_RED,
												  GL_RED);

		character.size = glm::ivec2(_face->glyph->bitmap.width, _face->glyph->bitmap.rows);
		character.bearing = glm::ivec2(_face->glyph->bitmap_left, _face->glyph->bitmap_top);
		character.advance = _face->glyph->advance.x;

		_characters.insert(std::pair<char, Character>(c, character));
	}

	FT_Done_Face(_face);
	FT_Done_FreeType(_ft);
	_loaded = true;
}