#ifndef __OPENGLRENDERER_OPENGL_OBJECTS_IMPL_TEXTUREDETAIL_H
#define __OPENGLRENDERER_OPENGL_OBJECTS_IMPL_TEXTUREDETAIL_H

template<typename T>
std::shared_ptr<Texture>
Texture::createTexture(const uint32_t& width,
					   const uint32_t& height,
					   const T* data,
					   const uint32_t& target,
					   const uint32_t& internal_format,
					   const uint32_t& format,
					   const uint32_t& type)
{
	std::shared_ptr<Texture> result = std::make_shared<Texture>();
	glGenTextures(1, &(result->_ID));
	glBindTexture(target, result->_ID);
	if (target == TEXTURE)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, type, data);

	}
	else
	{
		for (uint32_t i = 0; i < 6; ++i)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internal_format, width, height, 0, format, type, data);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(target);

	result->_target = target;
	result->_width = width;
	result->_height = height;

	return result;
}

template<typename T>
std::shared_ptr<Texture>
Texture::createTexture(const uint32_t& width,
					   const uint32_t& height,
					   const uint32_t& depth,
					   const T* data,
					   const uint32_t& internal_format,
					   const uint32_t& format,
					   const uint32_t& type)
{
	std::shared_ptr<Texture> result = std::make_shared<Texture>();
	glGenTextures(1, &(result->_ID));
	glBindTexture(GL_TEXTURE_3D, result->_ID);

	glTexImage3D(GL_TEXTURE_3D, 0, internal_format, width, height, depth, 0, format, type, data);


	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	result->_target = GL_TEXTURE_3D;
		  
	result->_width = width;
	result->_height = height;
	result->_depth = depth;

	return result;
}

#endif