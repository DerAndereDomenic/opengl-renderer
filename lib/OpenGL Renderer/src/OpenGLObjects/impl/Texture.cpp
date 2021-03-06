#include <OpenGLObjects/Texture.h>
#include <stb_image.h>
#include <iostream>
#include <DLogger/Logger.h>

Texture::Texture(const std::string& file_path, const bool& hdr)
{
	glGenTextures(1, &_ID);
	glBindTexture(GL_TEXTURE_2D, _ID);

	int32_t width;
	int32_t height;
	int32_t nr_channels;
	stbi_set_flip_vertically_on_load(true);

	void* data;

	uint32_t format, internal_format, type;

	if(!hdr)
	{
		data = (uint8_t*)stbi_load(file_path.c_str(), &width, &height, &nr_channels, 0);
	}
	else 
	{
		data = (float*)stbi_loadf(file_path.c_str(), &width, &height, &nr_channels, 0);
	}
	

	if (data)
	{
		if (nr_channels == 4)
		{
			if(!hdr)
			{
				format = GL_RGBA;
				internal_format = GL_RGBA;
				type = GL_UNSIGNED_BYTE;
			}
			else
			{
				format = GL_RGBA;
				internal_format = GL_RGBA16F;
				type = GL_FLOAT;
			}
		}
		else if (nr_channels == 3)
		{
			if(!hdr)
			{
				format = GL_RGB;
				internal_format = GL_RGB;
				type = GL_UNSIGNED_BYTE;
			}
			else
			{
				format = GL_RGB;
				internal_format = GL_RGB16F;
				type = GL_FLOAT;
			}
		}
		else if (nr_channels == 1)
		{
			if(!hdr)
			{
				format = GL_RED;
				internal_format = GL_RED;
				type = GL_UNSIGNED_BYTE;
			}
			else
			{
				format = GL_RED;
				internal_format = GL_R16F;
				type = GL_FLOAT;
			}
		}
		else
		{
			LOGGER::ERROR("ERROR::TEXTURE Wrong format. Number of channels: " + std::to_string(nr_channels) + ". Only 1, 3 or 4 are supported\n");
		}
		glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, type, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		LOGGER::ERROR("Failed to load texture: " + file_path + "\n");
	}

	stbi_image_free(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	_target = TEXTURE;
	_width = width;
	_height = height;
}

Texture::Texture(const std::string& file_path, const std::vector<std::string>& faces)
{
	glGenTextures(1, &_ID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _ID);

	int32_t width, height, nr_channels;
	stbi_set_flip_vertically_on_load(true);
	for (uint32_t i = 0; i < faces.size(); ++i)
	{
		std::string path = (file_path + faces[i]);
		uint8_t* data = stbi_load(path.c_str(), &width, &height, &nr_channels, 0);
		if (data)
		{
			uint32_t channels;
			if (nr_channels == 3)
			{
				channels = GL_RGB;
			}
			else if (nr_channels == 4)
			{
				channels = GL_RGBA;
			}
			else
			{
				LOGGER::ERROR("ERROR::TEXTURE Wrong format. Number of channels: " + std::to_string(nr_channels) + ". Only 3 or 4 are supported\n");
			}

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, channels, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			LOGGER::ERROR("Failed to load texture: " + file_path + "\n");
		}

		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	_target = CUBEMAP;
	_width = width;
	_height = height;
}
 
Texture::~Texture()
{
	glDeleteTextures(1, &_ID);
	_ID = 0;
}

void
Texture::generateMipmap() const
{
	glGenerateMipmap(_target);
}

void 
Texture::bind(const uint32_t& tex) const
{
	glActiveTexture(GL_TEXTURE0 + tex);
	glBindTexture(_target, _ID);
}

void 
Texture::unbind(const uint32_t& tex) const
{
	glActiveTexture(GL_TEXTURE0 + tex);
	glBindTexture(_target, 0);
}

void
Texture::bindDefault(const uint32_t& tex)
{
	glActiveTexture(GL_TEXTURE0 + tex);
	glBindTexture(GL_TEXTURE_2D, 0);
}