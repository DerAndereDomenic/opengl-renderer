#ifndef OPENGL_OBJECTS_RENDERBUFFER_H
#define OPENGL_OBJECTS_RENDERBUFFER_H

#include <cstdint>

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
	static RenderBuffer createObject(uint32_t width, uint32_t height);

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
	*	\brief Unbind the buffer (bind default)
	*	\note: Does the same as unbind but isn't tied to an object
	*/
	static void bindDefault();

	/**
	*	\brief The opengl handle of the rbo
	*	\return The frame buffer ID
	*/
	inline uint32_t getID() { return _ID; }
private:
	uint32_t _ID; /**<< The internal OpenGL handle of the rbo*/
};

#endif