#ifndef OPENGL_OBJECTS_TEXTURE_H
#define OPENGL_OBJECTS_TEXTURE_H

#include <GL/glew.h>
#include <vector>
#include <string>

enum Channels
{
	DEPTH = GL_DEPTH_COMPONENT,
	RGB = GL_RGB
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
	*	\brief Create an empty Texture
	*	\param[in] width The width of the texture
	*	\param[in] height The height of the texture
	*	\param[in] channels The type of texture (i.e. RGB or DEPTH for now)
	*	\param[in] type The data type of a channel (default: unsigned byte)
	*	\return The Texture object
	*/
	static Texture createObject(const unsigned int width,
								const unsigned int height,
								const unsigned int channels = RGB,
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
	*/
	void unbind() const;

	/**
	*	\brief The OpenGL handle of this texture
	*	\return The integer handle that opengl uses for this texture
	*/
	inline unsigned int getID(){return _ID;}
private:
	unsigned int _ID; /**<< The internal openGL handle for the texture*/
};

#endif