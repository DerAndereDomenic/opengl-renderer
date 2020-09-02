#ifndef RENDERER_TEXTRENDERER_H
#define RENDERER_TEXTRENDERER_H

#include <OpenGLObjects/Texture.h>
#include <glm/glm.hpp>
#include <map>

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

		static TextRenderer createObject(const char* path);

		static void destroyObject(TextRenderer& object);

		void loadFont(const unsigned int number_char, const unsigned int font_size);
	private:
		std::map<char, Character> _characters;
};

#endif