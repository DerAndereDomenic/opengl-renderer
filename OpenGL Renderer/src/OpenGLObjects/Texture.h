#ifndef OPENGL_OBJECTS_TEXTURE_H
#define OPENGL_OBJECTS_TEXTURE_H


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
	*	\brief Create an empty Texture
	*	\param[in] width The width of the texture
	*	\param[in] height The height of the texture
	*	\return The Texture object
	*/
	static Texture createObject(const unsigned int width, unsigned int height);

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
private:
	unsigned int _ID; /**<< The internal openGL handle for the texture*/
};

#endif