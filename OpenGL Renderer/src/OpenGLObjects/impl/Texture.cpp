#define STB_IMAGE_IMPLEMENTATION

#include <OpenGLObjects/Texture.h>
#include <stb_image.h>
#include <iostream>

Texture 
Texture::createObject(const char* file_path)
{
	Texture result;
	glGenTextures(1, &result._ID);
	glBindTexture(GL_TEXTURE_2D, result._ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width;
	int height;
	int nr_channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(file_path, &width, &height, &nr_channels, 0);

	if (data)
	{
		if (nr_channels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else if (nr_channels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cerr << "ERROR::TEXTURE Wrong format. Number of channels: " << nr_channels << ". Only 3 or 4 are supported" << std::endl;
		}
	}
	else
	{
		std::cerr << "Failed to load texture: " << file_path << std::endl;
	}

	stbi_image_free(data);

	return result;
}

Texture 
Texture::createObject(const unsigned int width, const unsigned int height, const unsigned int channels, const unsigned int type)
{
	Texture result;
	glGenTextures(1, &result._ID);
	glBindTexture(GL_TEXTURE_2D, result._ID);
	glTexImage2D(GL_TEXTURE_2D, 0, channels, width, height, 0, channels, type, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return result;
}

void 
Texture::destroyObject(Texture& texture)
{
	glDeleteTextures(1, &texture._ID);
}

void 
Texture::bind(const unsigned int tex) const
{
	glActiveTexture(GL_TEXTURE0 + tex);
	glBindTexture(GL_TEXTURE_2D, _ID);
}

void 
Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}