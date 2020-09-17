#ifndef OPENGL_OBJECTS_RENDERBUFFER_H
#define OPENGL_OBJECTS_RENDERBUFFER_H

/**
*	\brief A class to model a render buffer object
*/
class RenderBuffer
{
public:
	/**
	*	\brief Create an empty render buffer object
	*/
	RenderBuffer() = default;

	/**
	*	\brief Create a render buffer object
	*	\param[in] width The width of the buffer
	*	\param[in] height The height of the buffer
	*	\return The object
	*/
	static RenderBuffer createObject(unsigned int width, unsigned int height);

	/**
	*	\brief Destroy a render buffer object
	*	\param[in] rbo The object to be destroyed
	*/
	static void destroyObject(RenderBuffer& rbo);

	/**
	*	\brief Binds the render buffer
	*/
	void bind() const;

	/**
	*	\brief Unbinds the render buffer (bind 0)
	*/
	void unbind() const;

	/**
	*	\brief The opengl handle of the rbo
	*	\return The frame buffer ID
	*/
	inline unsigned int getID() { return _ID; }
private:
	unsigned int _ID; /**<< The internal OpenGL handle of the rbo*/
};

#endif