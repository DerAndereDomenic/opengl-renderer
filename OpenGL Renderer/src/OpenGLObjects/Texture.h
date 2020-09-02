#ifndef OPENGL_OBJECTS_TEXTURE_H
#define OPENGL_OBJECTS_TEXTURE_H

#include <GL/glew.h>
#include <vector>
#include <string>

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
	*	\return The Texture object
	*/
	static Texture createObject(const char* file_path);

	/**
	*	\brief Creates a Cubemap texture
	*	\param[in] file_path The path to the cube textures
	*	\param[in] faces The names of each face texture
	*	\return The Cubemap object
	*	\note The order should be: right, left, top, bottom, front, back
	*/
	static Texture createObject(const char* file_path, std::vector<std::string> faces);

	/**
	*	\brief Creates a texture and stores the given float data inside it
	*	\param[in] data The data to be stored inside the texture
	*	\param[in] width The width of the texture
	*	\param[in] height The height of the texture
	*/
	static Texture createObject(float* data, unsigned int width, unsigned int height);

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
	static Texture createObject(const unsigned int width,
								const unsigned int height,
								const T* data = NULL,
								const unsigned int target = TEXTURE,
								const unsigned int internal_format = RGB,
								const unsigned int format = RGB,
								const unsigned int type = GL_UNSIGNED_BYTE);

	/**
	*	\brief Destroys the Texture object
	*	\param[in] texture The texture to be destroyed;
	*/
	static void destroyObject(Texture& texture);

	/**
	*	\brief Binds the texture to the given texture index
	*	\param[in] tex The texture index (default = 0)
	*/
	void bind(const unsigned int tex = 0) const;

	/**
	*	\brief Unbinds the texture (bind 0)
	*	\param[in] tex The texture index (default = 0)
	*/
	void unbind(const unsigned int tex = 0) const;

	/**
	*	\brief The OpenGL handle of this texture
	*	\return The integer handle that opengl uses for this texture
	*/
	inline unsigned int getID(){return _ID;}
private:
	unsigned int _ID = 0; /**<< The internal openGL handle for the texture*/
	unsigned int _target = GL_TEXTURE_2D; /**<< The texture target*/
};

#include "impl/TextureDetail.h"

#endif