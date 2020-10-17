#ifndef __OPENGLRENDERER_RENDERER_TEXTRENDERER_H
#define __OPENGLRENDERER_RENDERER_TEXTRENDERER_H

#include <OpenGLObjects/VertexArray.h>
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
	uint32_t advance;	/**<< Offset to advance to next glyth*/
};

class TextRenderer
{
	public:
		/**
		*	\brief Creates an empty Text Renderer
		*/
		TextRenderer() = default;

		/**
		*	\brief Create a TextRenderer Object
		*	\param[in] width The width of the window
		*	\param[in] height The height of the window
		*	\return The TextRenderer Object
		*	\note At this point the FT library and all vertex buffers are initialized
		*/
		static TextRenderer createObject(const uint32_t& width, const uint32_t& height);

		/**
		*	\brief Destroys the TextRenderer
		*	\param[in] object The object to be destroyed
		*	\note: This unloads the FT library if not already done by loadFont
		*/
		static void destroyObject(TextRenderer& object);

		/**
		*	\brief Loads the given font into an internal format where the textures for the glyphs are created
		*	\param[in] path Path to the font
		*	\param[in] font_size The size of the font
		*	\note: This unloads the FT library components at the end
		*/
		void loadFont(const char* path, const uint32_t& font_size);

		/**
		*	\brief Renders the text to the screen
		*	\param[in] text The text to be rendered
		*	\param[in] x The x position where the text should start
		*	\param[in] y The y position of the text
		*	\param[in] scale A scaling factor for the text
		*	\param[in] color The color of the text
		*/
		void render(const std::string& text, float x, float y, const float& scale, const glm::vec3& color);
	private:

		/**
		*	\brief Loads a character from the loaded font
		*	\param[in] c The character to load 
		*/
		void loadCharacter(const uint8_t& c);

		FT_Library _ft;							/**<< The internal FreeType library object*/
		FT_Face _face;							/**<< The internal FreeType face object*/
		std::map<char, Character> _characters;	/**<< The internal character structure, storing textures, etc.*/
		VertexArray _vao;						/**<< The vao to render the text*/
		VertexBuffer _vbo;						/**<< The vbo to render the text*/
		glm::mat4 _projection;					/**<< The orthographic projection to render the text*/
};

#endif