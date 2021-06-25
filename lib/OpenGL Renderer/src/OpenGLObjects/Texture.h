#ifndef __OPENGLRENDERER_OPENGL_OBJECTS_TEXTURE_H
#define __OPENGLRENDERER_OPENGL_OBJECTS_TEXTURE_H

#include <glad/glad.h>
#include <vector>
#include <string>
#include <memory>

enum Channels
{
	DEPTH = GL_DEPTH_COMPONENT,
	RGB = GL_RGB,
	RGBA = GL_RGBA
};

enum Targets
{
	TEXTURE = GL_TEXTURE_2D,
	CUBEMAP = GL_TEXTURE_CUBE_MAP
};

class Texture
{
public:
	/**
	*	\brief Creates an empty texture
	*/
	Texture() = default;

	/**
	*	\brief Creates a Texture and fills it with data from file_path
	*	\param[in] file_path Path to the texture data
	*/
	Texture(const std::string& file_path);

	/**
	*	\brief Creates a Cubemap texture
	*	\param[in] file_path The path to the cube textures
	*	\param[in] faces The names of each face texture
	*	\return The Cubemap object
	*	\note The order should be: right, left, top, bottom, front, back
	*/
	Texture(const std::string&, const std::vector<std::string>& faces);

	/**
	*	\brief Create an empty Texture
	*	\tparam T The type of data
	*	\param[in] width The width of the texture
	*	\param[in] height The height of the texture
	*	\param[in] data The data stored in the texture (default = NULL)
	*	\param[in] target The texture target (TEXTURE or CUBEMAP, default = TEXTURE)
	*	\param[in] internal_format The type of texture (i.e. RGB or DEPTH for now)
	*	\param[in] format The format of the pixel data
	*	\param[in] type The data type of a channel (default: unsigned byte)
	*	\return The Texture object
	*/
	template<typename T>
	static std::shared_ptr<Texture>
	createTexture(const uint32_t& width,
				  const uint32_t& height,
				  const T* data = NULL,
				  const uint32_t& target = TEXTURE,
				  const uint32_t& internal_format = RGB,
				  const uint32_t& format = RGB,
				  const uint32_t& type = GL_UNSIGNED_BYTE);

	/**
	*	\brief Create an empty 3D Texture
	*	\tparam T The type of data
	*	\param[in] width The width of the texture
	*	\param[in] height The height of the texture
	*	\param[in] depth The depth of the texture
	*	\param[in] data The data stored in the texture (default = NULL)
	*	\param[in] internal_format The type of texture (i.e. RGB or DEPTH for now)
	*	\param[in] format The format of the pixel data
	*	\param[in] type The data type of a channel (default: unsigned byte)
	*	\return The Texture object
	*/
	template<typename T>
	static std::shared_ptr<Texture>
	createTexture(const uint32_t& width,
				  const uint32_t& height,
				  const uint32_t& depth,
				  const T* data = NULL,
				  const uint32_t& internal_format = RGB,
				  const uint32_t& format = RGB,
				  const uint32_t& type = GL_UNSIGNED_BYTE);

	/**
	*	\brief Destroys the Texture object
	*/
	~Texture();

	/**
	*	\brief Binds the texture to the given texture index
	*	\param[in] tex The texture index (default = 0)
	*/
	void bind(const uint32_t& tex = 0) const;

	/**
	*	\brief Unbinds the texture (bind 0)
	*	\param[in] tex The texture index (default = 0)
	*/
	void unbind(const uint32_t& tex = 0) const;

	/**
	*	\brief Unbind the buffer (bind default)
	*	\param[in] tex The texture index (default = 0)
	*	\note: Does the same as unbind but isn't tied to an object
	*/
	static void bindDefault(const uint32_t& = 0);

	/**
	*	\brief The OpenGL handle of this texture
	*	\return The integer handle that opengl uses for this texture
	*/
	inline uint32_t getID() const {return _ID;}

	/**
	*	\brief The width of the texture
	*	\return The width 
	*/
	inline uint32_t getWidth() const {return _width;}

	/**
	*	\brief The height of the texture
	*	\return The height 
	*/
	inline uint32_t getHeight() const {return _height;}

	/**
	*	\brief The depth of the texture
	*	\return The depth 
	*/
	inline uint32_t getDepth() const {return _depth;}
private:
	uint32_t _ID = 0; 					/**<< The internal openGL handle for the texture*/
	uint32_t _target = GL_TEXTURE_2D; 	/**<< The texture target*/
	uint32_t _width = 0;				/**<< The width of the texture*/
	uint32_t _height = 0;				/**<< The height of the texture*/
	uint32_t _depth = 0;				/**<< The depth of the texture*/
};

#include "impl/TextureDetail.h"

#endif