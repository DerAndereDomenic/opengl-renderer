#ifndef RENDERER_TEXTRENDERER_H
#define RENDERER_TEXTRENDERER_H

#include <OpenGLObjects/Texture.h>
#include <glm/glm.hpp>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

struct Character
{
	Texture texture;		/**<< The texture of the glyph*/
	glm::ivec2 size;		/**<< Size of the glyph*/
	glm::ivec2 bearing;		/**<< Offset from baseline to left/top of the glyph*/
	unsigned int advance;	/**<< Offset to advance to next glyth*/
};

class TextRenderer
{
	public:
		TextRenderer() = default;

		static TextRenderer createObject();

		static void destroyObject(TextRenderer& object);

		void loadFont(const char* path, const unsigned int number_char, const unsigned int font_size);
	private:
		FT_Library _ft;
		FT_Face _face;
		std::map<char, Character> _characters;
		bool _loaded = false;
};

#endif