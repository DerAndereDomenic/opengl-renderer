#include <Renderer/TextRenderer.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <Shader/ShaderManager.h>

TextRenderer 
TextRenderer::createObject(const uint32_t& width, const uint32_t& height)
{
	TextRenderer result;

	if (FT_Init_FreeType(&result._ft))
	{
		std::cout << "ERROR::TEXTRENDERER::FREETYPE: Could not initialize FreeType Library" << std::endl;
	}

	VertexBufferLayout layout;
	layout.add(GL_FLOAT, 2);
	layout.add(GL_FLOAT, 2);

	float vertices[4*6] =
	{
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,

		0.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 0.0f
	};

	result._vbo = VertexBuffer::createObject(vertices, 6 * 4);
	result._vao = VertexArray::createObject();
	result._vao.addBuffer(result._vbo, layout);

	result._projection = glm::ortho(0.0f, (float)width, 0.0f, (float)height);

	ShaderManager::instance()->addShader("Text");

	return result;
}

void 
TextRenderer::destroyObject(TextRenderer& object)
{
	if (object._loaded)
	{
		for (uint32_t i = 0; i < object._characters.size(); ++i)
		{
			Character character = object._characters[i];
			Texture::destroyObject(character.texture);
		}
		object._characters.clear();
		object._loaded = false;
	}
	FT_Done_Face(object._face);
	FT_Done_FreeType(object._ft);
	VertexBuffer::destroyObject(object._vbo);
	VertexArray::destroyObject(object._vao);
}

void 
TextRenderer::render(const std::string& text, float x, float y, const float& scale, const glm::vec3& color)
{
	Shader text_shader = ShaderManager::instance()->getShader("Text");
	text_shader.bind();
	text_shader.setVec3("textColor", color);
	text_shader.setMat4("projection", _projection);

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); ++c)
	{
		Character ch = _characters[*c];

		float xpos = x + ch.bearing.x * scale;
		float ypos = y - (ch.size.y - ch.bearing.y) * scale;

		float w = ch.size.x * scale;
		float h = ch.size.y * scale;

		glm::mat4 model = glm::scale(glm::translate(glm::mat4(1), glm::vec3(xpos, ypos, 0)), glm::vec3(w, h, 10));

		text_shader.setMat4("model", model);
		ch.texture.bind();
		_vao.render();

		x += (ch.advance >> 6) * scale;
	}
}

void 
TextRenderer::loadFont(const char* path, const uint32_t& number_char, const uint32_t& font_size)
{
	if (FT_New_Face(_ft, path, 0, &_face))
	{
		std::cout << "ERROR::TEXTRENDERER::FREETYPE: Could not load font at: " << path << std::endl;
	}

	FT_Set_Pixel_Sizes(_face, 0, font_size);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //disable byte-alignment restriction;

	for (uint8_t c = 0; c < number_char; ++c)
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
	_loaded = true;
}

void 
TextRenderer::loadCharacter(const uint8_t& c)
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