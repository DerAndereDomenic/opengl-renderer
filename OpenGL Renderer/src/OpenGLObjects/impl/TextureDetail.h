#ifndef OPENGL_OBJECTS_IMPL_TEXTUREDETAIL_H
#define OPENGL_OBJECTS_IMPL_TEXTUREDETAIL_H

template<typename T>
Texture
Texture::createObject(const unsigned int width,
					  const unsigned int height,
					  const T* data,
					  const unsigned int target,
					  const unsigned int internal_format,
					  const unsigned int format,
					  const unsigned int type)
{
	Texture result;
	glGenTextures(1, &result._ID);
	glBindTexture(target, result._ID);
	if (target == TEXTURE)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, type, data);

	}
	else
	{
		for (unsigned int i = 0; i < 6; ++i)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internal_format, width, height, 0, format, type, data);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	result._target = target;

	return result;
}

template<typename T>
Texture
Texture::createObject(const unsigned int width,
					  const unsigned int height,
					  const unsigned int depth,
					  const T* data,
					  const unsigned int internal_format,
					  const unsigned int format,
					  const unsigned int type)
{
	Texture result;
	glGenTextures(1, &result._ID);
	glBindTexture(GL_TEXTURE_3D, result._ID);

	glTexImage3D(GL_TEXTURE_3D, 0, internal_format, width, height, depth, 0, format, type, data);


	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	result._target = GL_TEXTURE_3D;

	return result;
}

#endif